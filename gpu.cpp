#include "gpu.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

GPU::GPU(Memory *memory) {

	this->memory = memory;

	this->cycleCounter = 456;
	window = NULL;  
	renderer = NULL;
	for (int x = 0; x < 160; x++) {
		for (int y = 0; y < 144; y++) {
			screen[x][y] = 0;
		}
	}

	//Initialize SDL 
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) { 
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
	}
	else {
		window = SDL_CreateWindow( "GBEmu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ); 
		
		if( window == NULL) { 
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl; 
		}
		else { 
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			//Fill the surface white 
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				for (int y = 0; y < SCREEN_HEIGHT; y++) {
					SDL_RenderDrawPoint(renderer, x, y);
				}
			}

			SDL_RenderPresent(renderer);
		}
	}
}

GPU::~GPU() {
	//Destroy window 
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window ); 
	 
	//Quit SDL subsystems 
	SDL_Quit();
}

void GPU::RenderScreen() {
	
	for (int y = 0; y < 144; y++) {
		for(int x = 0; x < 160; x++) {

			switch(screen[x][y]) {
				case 0:	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); break;
				case 1:	SDL_SetRenderDrawColor(renderer, 0xD3, 0xD3, 0xD3, 0xFF); break;
				case 2:	SDL_SetRenderDrawColor(renderer, 0xA9, 0xA9, 0xA9, 0xFF); break;
				case 3:	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); break;
			}
			
			SDL_RenderDrawPoint(renderer, x, y);				
		}
	}

	SDL_RenderPresent(renderer);
}

void GPU::UpdateScreen(int cycles) {

	//read lcd control register
	BYTE lcdRegister = this->memory->readByte(0xFF40);
	scanline = this->memory->readByte(0xFF44);

	lcdEnabled = (lcdRegister & BIT7) > 0;
	backgroundEnabled = (lcdRegister & BIT0) > 0;
	windowEnabled = ((lcdRegister & BIT5) > 0) && backgroundEnabled;
	spriteEnabled = (lcdRegister & BIT1) > 0;
	spriteSize16 = (lcdRegister & BIT2) > 0;
	backgroundTileMapAddress  = ((lcdRegister & BIT3) > 0) ? 0x9C00 : 0x9800;
	windowTileMapAddress = ((lcdRegister & BIT6) > 0) ? 0x9C00 : 0x9800;
	tileDataSelect = (lcdRegister & BIT4) > 0;

	drawLine = false;
	vblank = false;
	mode = UpdateLCDMode();

	if (lcdEnabled) {
		cycleCounter -= cycles;
		

		if (drawLine) {
			DrawLine();
			DrawSprites();
		}

		if (vblank) {
			this->memory->requestInterrupt(Interrupt::VBlank);
		}

		if (cycleCounter <= 0) {
			cycleCounter += 456;

			scanline++;
			if (scanline > 153) {
				this->memory->updateLYRegister(0);
			}
			else {
				this->memory->updateLYRegister(scanline);
			}
		}
	}
}

LCDMode GPU::UpdateLCDMode() {
	BYTE lcdStatus = this->memory->readByte(0xFF41);

	LCDMode mode = LCDMode::HorizontalBlank;
	if (!lcdEnabled) {
		mode = LCDMode::VerticalBlank;
		this->memory->updateLYRegister(0);
	}
	else {

		if (cycleCounter > 376) {
			mode = LCDMode::OAM;
		}
		else if (cycleCounter > 204) {
			mode = LCDMode::VRAM;
		}
		else {
			mode = LCDMode::HorizontalBlank;
		}

		if (scanline >= 144) {
			mode = LCDMode::VerticalBlank;
		}
	}

	LCDMode previousMode = (LCDMode)(lcdStatus & (BIT1 | BIT0));
	if (previousMode != mode) {

		bool interruptEnabled = false;
		switch (mode) {
			case LCDMode::HorizontalBlank: 	interruptEnabled = ((lcdStatus & BIT3) > 0);								
											break;
			case LCDMode::VerticalBlank:	interruptEnabled = ((lcdStatus & BIT4) > 0);
											vblank = true;
											break;
			case LCDMode::OAM:				interruptEnabled = ((lcdStatus & BIT5) > 0);
											break;
			case LCDMode::VRAM:				interruptEnabled = false;
											drawLine = true;
											break;
		}

		if (interruptEnabled) {
			this->memory->requestInterrupt(Interrupt::LCDC);
		}
	}

	BYTE LYCompareValue = this->memory->readByte(0xFF45);

	BYTE coincidentFlag = 0x00;
	if (LYCompareValue == scanline) {

		BYTE previousCoincident = lcdStatus & BIT2;
		bool interruptEnabled = (lcdStatus & BIT6) > 0;

		if (previousCoincident == 0 && interruptEnabled) {
			this->memory->requestInterrupt(Interrupt::LCDC);
		}

		coincidentFlag = BIT2;
	}

	lcdStatus &= ~(BIT2 | BIT1 | BIT0); 
	lcdStatus |= (coincidentFlag | (BYTE)mode);
	this->memory->writeByte(0xFF41, lcdStatus);

	return mode;
}

void GPU::DrawLine() {


	BYTE ScrollX = this->memory->readByte(0xFF43);
	BYTE Scrolly = this->memory->readByte(0xFF42);
	BYTE WindowYPos = this->memory->readByte(0xFF4A);
	BYTE WindowXPos = this->memory->readByte(0xFF4B);

	BYTE yPixelRow = Scrolly + scanline;
	WORD yTileRow = ((BYTE)(yPixelRow/8)) * 32;

	for (int x = 0; x < 160; x++) {

		BYTE xColumn = ScrollX + x;
		WORD xTileColumn = xColumn/8;

		WORD backgroundTileMap = backgroundTileMapAddress + yTileRow + xTileColumn;

		BYTE row = yPixelRow % 8;
		row = row * 2; //each pixel row is represented by 2 bytes

		WORD tileAddress = 0;
		if (tileDataSelect) {
			BYTE tileNumber = this->memory->readByte(backgroundTileMap);
			tileAddress = 0x8000 + (tileNumber*16) + row;
		}
		else {
			SIGNED_BYTE signedTileNumber = (SIGNED_BYTE)this->memory->readByte(backgroundTileMap);
			tileAddress = 0x8800 + ((signedTileNumber + 128) * 16) + row;
		} 

		BYTE tileDataRow = this->memory->readByte(tileAddress);
		BYTE tileDataRow2 = this->memory->readByte(tileAddress + 1);
			
		BYTE color = getPixelColor(tileDataRow, tileDataRow2, (xColumn % 8), 0xFF47);
		this->screen[x][scanline] = color;
	}
}

void GPU::DrawSprites() {

	BYTE lcdRegister = this->memory->readByte(0xFF40);
	if (spriteEnabled) {

		int ySize = spriteSize16 ? 16 : 8;

		for (int i = 0; i < 40; i++) {
			WORD spriteAddress = 0xFE00 + (i*4);

			int yPosition = (int)this->memory->readByte(spriteAddress) - 16;
			int xPosition = (int)this->memory->readByte(spriteAddress + 1) - 8;

			if ((scanline >= yPosition) && (scanline < (yPosition+ySize))) {
				if (xPosition >= -7 && xPosition <= 153) {
					
					BYTE patternNumber = this->memory->readByte(spriteAddress + 2);
					if (ySize == 16) {
						patternNumber &= ~(BIT0);
					}
					
					BYTE spriteFlags = this->memory->readByte(spriteAddress + 3);

					WORD paletteAddress = IsBitSet(spriteFlags, BIT4) ? 0xFF49 : 0xFF48;
					bool flipXAxis = IsBitSet(spriteFlags, BIT5);
					bool flipYAxis = IsBitSet(spriteFlags, BIT6);
					bool priorityOverBG = IsBitSet(spriteFlags, BIT7);

					BYTE row = (scanline - yPosition);
					if (flipYAxis) {
						row = ySize - row;
					}
					row = row * 2;

					WORD tileDataAddress = 0x8000 + (16*patternNumber) + row;
					BYTE tileDataRow = this->memory->readByte(tileDataAddress);
					BYTE tileDataRow2 = this->memory->readByte(tileDataAddress + 1);
					for (int x = xPosition; x < (xPosition + 8); x++) {
						if (x >= 0 && x < 160) {
							int pixelXBit = x - xPosition;
							if (flipXAxis) {
								pixelXBit = 7 - pixelXBit;
							}
							
							pixelXBit -= 7;
							pixelXBit *= -1;

							BYTE colorValue = GetBit(tileDataRow2, pixelXBit);
							colorValue = (colorValue << 1) | GetBit(tileDataRow, pixelXBit);

							BYTE color = getPixelColor(paletteAddress, colorValue);

							BYTE pixelValue = this->screen[x][scanline];
							if (colorValue == 0) {

							} else if (!priorityOverBG || (priorityOverBG && (pixelValue == 0))) {
								this->screen[x][scanline] = color;
							}
						}
					}
				}			 
			}
		}
	}

}

BYTE GPU::getPixelColor(BYTE tileDataRow, BYTE tileDataRow2, int bitPosition, WORD paletteAddress) {

	bitPosition -= 7;
	bitPosition *= -1;

	BYTE colorValue = GetBit(tileDataRow2, bitPosition);
	colorValue = (colorValue << 1) | GetBit(tileDataRow, bitPosition);

	BYTE colorPalette = this->memory->readByte(paletteAddress);

	BYTE color = 0;
	switch(colorValue){
		case 0: color = (colorPalette & (BIT1 | BIT0)); break;
		case 1:	color = ((colorPalette & (BIT3 | BIT2)) >> 2); break;
		case 2:	color = ((colorPalette & (BIT5 | BIT4)) >> 4); break;
		case 3: color = ((colorPalette & (BIT7 | BIT6)) >> 6); break;
	}

	return color;
}

BYTE GPU::getPixelColor(WORD paletteAddress, BYTE colorValue) {
	BYTE colorPalette = this->memory->readByte(paletteAddress);

	BYTE color = 0;
	switch(colorValue){
		case 0: color = (colorPalette & (BIT1 | BIT0)); break;
		case 1:	color = ((colorPalette & (BIT3 | BIT2)) >> 2); break;
		case 2:	color = ((colorPalette & (BIT5 | BIT4)) >> 4); break;
		case 3: color = ((colorPalette & (BIT7 | BIT6)) >> 6); break;
	}

	return color;
}