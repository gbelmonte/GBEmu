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
	bool lcdOn = (lcdRegister & BIT7) > 0;

	UpdateLCDMode();

	if (lcdOn) {
		cycleCounter -= cycles;
		
		if (cycleCounter <= 0) {
			BYTE line = this->memory->readByte(0xFF44);
			cycleCounter = 456;

			if (line == 144) {
				this->memory->requestInterrupt(Interrupt::VBlank);
			}
			else if((line > 144) && (line <= 153)) {
				//in V-Blank
			}
			else {
				DrawLine();
				DrawSprites();
			}

			line++;
			if (line > 153) {
				this->memory->updateLYRegister(0);
			}
			else {
				this->memory->updateLYRegister(line);
			}
		}
	}
}

void GPU::UpdateLCDMode() {
	BYTE lcdRegister = this->memory->readByte(0xFF40);
	BYTE lcdStatus = this->memory->readByte(0xFF41);
	BYTE line = this->memory->readByte(0xFF44);

	bool lcdOn = (lcdRegister & BIT7) > 0;

	BYTE mode = 0x00;
	if (!lcdOn) {
		mode = 0x01;
		this->memory->updateLYRegister(0);
	}
	else {

		if (cycleCounter > 376) {
			mode = 0x02;
		}
		else if (cycleCounter > 206) {
			mode = 0x03;
		}
		else {
			mode = 0x00;
		}

		if (line >= 144) {
			mode = 0x01;
		}
	}

	BYTE previousMode = lcdStatus & (BIT1 | BIT0);
	if (previousMode != mode) {

		bool interruptEnabled = false;
		switch (mode) {
			case 0x00: 	interruptEnabled = ((lcdStatus & BIT3) > 0);
						break;
			case 0x01:	interruptEnabled = ((lcdStatus & BIT4) > 0);
						break;
			case 0x02:	interruptEnabled = ((lcdStatus & BIT5) > 0);
						break;
			case 0x03:	interruptEnabled = false;
						break;
		}

		if (interruptEnabled) {
			this->memory->requestInterrupt(Interrupt::LCDC);
		}
	}

	BYTE LYCompareValue = this->memory->readByte(0xFF45);

	BYTE coincidentFlag = 0x00;
	if (LYCompareValue == line) {
		BYTE previousCoincident = lcdStatus & BIT2;
		bool interruptEnabled = (lcdStatus & BIT6) > 0;
		if (previousCoincident == 0 && interruptEnabled) {
			this->memory->requestInterrupt(Interrupt::LCDC);
		}
		coincidentFlag = BIT2;
	}

	lcdStatus &= ~(BIT2 | BIT1 | BIT0); 
	lcdStatus |= (coincidentFlag | mode);
	this->memory->writeByte(0xFF41, lcdStatus);
}

void GPU::DrawLine() {
	BYTE lcdRegister = this->memory->readByte(0xFF40);
	BYTE ScrollX = this->memory->readByte(0xFF43);
	BYTE Scrolly = this->memory->readByte(0xFF42);
	BYTE WindowYPos = this->memory->readByte(0xFF4A);
	BYTE WindowXPos = this->memory->readByte(0xFF4B);

	BYTE yPixel = this->memory->readByte(0xFF44);
	BYTE yPixelRow = Scrolly + yPixel;
	WORD yTileRow = ((BYTE)(yPixelRow/8)) * 32;
	// BYTE yWindowPixelRow = yPixel - WindowYPos;
	// BYTE yWindowTileRow = (yWindowPixelRow/8) * 32;

	// bool windowOn = ((lcdRegister & BIT5) > 0) ? true : false;

	// if (windowOn && yPixel >= WindowYPos) {
	// 	yTileRow = yWindowTileRow;
	// }	

	for (int xPixel = 0; xPixel < 160; xPixel++) {

		BYTE xPixelColumn = ScrollX + xPixel;
		WORD xTileColumn = ((BYTE)xPixelColumn)/8;
		// BYTE xWindowPixelColumn = xPixel - WindowXPos;
		// WORD xWindowTileColumn = xWindowPixelColumn/8;

		// if (windowOn && (yPixel >= WindowYPos) && (xPixel >= WindowXPos)) {
		// 	xTileColumn = xWindowTileColumn;
		// 	xPixelColumn = xWindowPixelColumn;
		// }

		// WORD windowTileMapAddress = ((lcdRegister & BIT6) > 0) ? 0x9C00 : 0x9800;
		// WORD windowTileMap = windowTileMapAddress + yWindowTileRow + xWindowTileColumn;
		WORD backgroundTileMapAddress = ((lcdRegister & BIT3) > 0) ? 0x9C00 : 0x9800;
		WORD backgroundTileMap = backgroundTileMapAddress + yTileRow + xTileColumn;

		// BYTE row = 0;
		// if (windowOn && (yPixel >= WindowYPos) && (xPixel >= WindowXPos)) {
		// 	backgroundTileMap = windowTileMap;
		// 	row = yWindowPixelRow % 8;
		// 	xPixelColumn = xWindowPixelColumn;
		// }
		// else {
		// 	row = yPixelRow % 8;
		// }
		BYTE row = yPixelRow % 8;
		BYTE tileNumber = this->memory->readByte(backgroundTileMap);
		SIGNED_BYTE signedTileNumber = (SIGNED_BYTE)this->memory->readByte(backgroundTileMap);

		row = row * 2; //each pixel row is represented by 2 bytes

		WORD tileAddress = 0;
		if ((lcdRegister & BIT4) > 0) {
			tileAddress = 0x8000 + (tileNumber*16) + row;
		}
		else {
			tileAddress = 0x8800 + ((signedTileNumber + 128) * 16) + row;
		} 

		BYTE tileDataRow = this->memory->readByte(tileAddress);
		BYTE tileDataRow2 = this->memory->readByte(tileAddress + 1);
			
		BYTE color = getPixelColor(tileDataRow, tileDataRow2, xPixelColumn % 8, 0xFF47);
		this->screen[xPixel][yPixel] = color;
	}
}

void GPU::DrawSprites() {

	BYTE lcdRegister = this->memory->readByte(0xFF40);
	if (lcdRegister & BIT1 > 0) {

		BYTE spriteSize = lcdRegister & BIT2;
		int ySize = 8;
		if (spriteSize > 0) {
			ySize = 16;
		}
		int yLine = (int)this->memory->readByte(0xFF44);

		for (int i = 0; i < 40; i++) {
			WORD spriteAddress = 0xFE00 + (i*4);

			int yPosition = (int)this->memory->readByte(spriteAddress) - 16;

			if ((yLine >= yPosition) && (yLine < (yPosition+ySize))) {
				int xPosition = (int)this->memory->readByte(spriteAddress + 1) - 8;
				
				if (xPosition >= -7 && xPosition <= 153) {
					
					BYTE patternNumber = this->memory->readByte(spriteAddress + 2);
					if (ySize == 16) {
						patternNumber &= ~(BIT0);
					}
					
					BYTE spriteFlags = this->memory->readByte(spriteAddress + 3);

					BYTE paletteFlag = GetBit(spriteFlags, 4);
					WORD paletteAddress = (paletteFlag == 1) ? 0xFF49 : 0xFF48;

					BYTE priorityOverBG = GetBit(spriteFlags, 7);
					BYTE yFlip = GetBit(spriteFlags, 6);
					BYTE xFlip = GetBit(spriteFlags, 5);

					//0x8000: start of sprite pattern table
					BYTE row = (yLine - yPosition);
					if (yFlip > 0) {
						row = ySize - row;
					}
					row = row * 2;

					WORD tileDataAddress = 0x8000 + (16*patternNumber) + row;
					BYTE tileDataRow = this->memory->readByte(tileDataAddress);
					BYTE tileDataRow2 = this->memory->readByte(tileDataAddress + 1);
					for (int x = xPosition; x < (xPosition + 8); x++) {
						if (x >= 0 && x < 160) {
							int pixelXBit = x - xPosition;
							if (xFlip > 0) {
								pixelXBit = 7 - pixelXBit;
							}
							
							pixelXBit -= 7;
							pixelXBit *= -1;

							BYTE colorValue = GetBit(tileDataRow2, pixelXBit);
							colorValue = (colorValue << 1) | GetBit(tileDataRow, pixelXBit);

							BYTE color = getPixelColor(paletteAddress, colorValue);

							BYTE pixelValue = this->screen[x][yLine];
							if (colorValue == 0) {

							} else if (priorityOverBG == 0 || ((priorityOverBG == 1) && (pixelValue == 0))) {
								this->screen[x][yLine] = color;
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

BYTE GPU::GetBit(BYTE value, int bitPos) {
	
	BYTE mask;
	switch (bitPos) {
		case 0: mask = BIT0; break;
		case 1: mask = BIT1; break;
		case 2: mask = BIT2; break;
		case 3: mask = BIT3; break;
		case 4: mask = BIT4; break;
		case 5: mask = BIT5; break;
		case 6: mask = BIT6; break;
		case 7: mask = BIT7; break;
	}

	value = value & mask;
	value = value >> bitPos;

	return value;
}