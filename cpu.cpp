#include "cpu.hpp"
#include "instructions.cpp"
#include "cb_instructions.cpp"

CPU::CPU(){

	this->debug = false;
	
	//Init Registers
	this->SP.reg = 0xFFFE;
	this->PC.reg = 0x100;
	//this->PC.reg = 0x00;

	this->AF.reg = 0x01B0;
	this->BC.reg = 0x0013;
	this->DE.reg = 0x00D8;
	this->HL.reg = 0x014D;

	this->interruptEnabled = false;
	this->halt = false;
	this->quit = false;
	this->cycleCounter = 456;
	this->dividerCounter = 0;
	this->timerCounter = 0;
	this->timerFrequency = 1024;

	initInstructions();
	initCBInstructions();
}

CPU::~CPU(){
	SDL_RemoveTimer(this->timerID);
}

void CPU::LoadCartridge(char* path){
	if (!this->memory.LoadCartridge(path)) {
		cout << "Cartridge load failed";
	}
}

Uint32 CPU::ExecuteFrame(Uint32 interval, void *param) {
	CPU* cpu = (CPU*) param;

	cpu->cyclesThisFrame = 0;
	while (cpu->cyclesThisFrame < 69905) {

		//Fetch
		BYTE opcode = cpu->Fetch();
		Logger::LogOpcode(opcode);

		//DecodeExecute
		int cycles = cpu->DecodeExecute(opcode);

		cpu->UpdateScreen(cycles);
		cpu->UpdateTimers(cycles);

		cpu->CheckInput();	
		cpu->HandleInterrupt();

		cpu->cyclesThisFrame += cycles;
	}

	cpu->gpu.UpdateScreen();

	return interval;
}

void CPU::Run() {

	this->timerID = SDL_AddTimer(16, ExecuteFrame, this);

	while(this->IsOn()) {

	}
}

BYTE CPU::Fetch(){
	BYTE opcode = this->memory.readByte(this->PC.reg);
	if (this->PC.reg > 0xc000 && debug) {
		string hello;
		cin >> hello;
	}
	//cout << hex << "AF: " << this->AF.reg << " BC: " << this->BC.reg << " DE: " << this->DE.reg << " HL: " << this->HL.reg << " SP: " << this->SP.reg << " Z: " << (int)getFlag(Flag::z) << " C: " << (int)getFlag(Flag::c) << " H: " << (int)getFlag(Flag::h) << " n " << (int)getFlag(Flag::n) << endl;
	Logger::LogPC(this->PC.reg);

	if (halt == false) {
		this->PC.reg = this->PC.reg + 1;
	}
	else {
		opcode = 0x00;
	}
	
	return opcode;
}

int CPU::DecodeExecute(BYTE opcode){
	string input;
	int cycles = 0;
	
	if (opcode == 0xcb){
		opcode = Fetch();
		if (instructions_cb[opcode] != NULL) {
			cycles = (this->*instructions_cb[opcode])();
		}
		else {
			cout << hex << "CB Opcode: cb " << (int)opcode << " is not implemented yet.";
			cin >> input;
		}
	}
	else {
		if (instructions[opcode] != NULL){
			cycles = (this->*instructions[opcode])();
		}
		else {
			cout << hex << "Opcode: " << (int)opcode << " is not implemented yet.";
			cin >> input;
		}
	}

	return cycles;
}

void CPU::UpdateScreen(int cycles) {
	//read lcd control register
	BYTE lcdRegister = this->memory.readByte(0xFF40);
	
	if ((lcdRegister & BIT7) > 0) {
		cycleCounter -= cycles;
		
		if (cycleCounter <= 0) {
			BYTE line = this->memory.readByte(0xFF44);
			cycleCounter = 456;

			if (line == 144) {
				requestInterrupt(Interrupt::VBlank);
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
				this->memory.writeByte(0xFF44, 0);
			}
			else {
				this->memory.writeByte(0xFF44, line);
			}
		}
	}
}

void CPU::DrawLine() {
	BYTE lcdRegister = this->memory.readByte(0xFF40);
	BYTE ScrollX = this->memory.readByte(0xFF43);
	BYTE Scrolly = this->memory.readByte(0xFF42);
	BYTE WindowYPos = this->memory.readByte(0xFF4A);
	BYTE WindowXPos = this->memory.readByte(0xFF4B);

	BYTE yPixel = this->memory.readByte(0xFF44);
	BYTE yPixelRow = Scrolly + yPixel;
	WORD yTileRow = (yPixelRow/8) * 32;
	// BYTE yWindowPixelRow = yPixel - WindowYPos;
	// BYTE yWindowTileRow = (yWindowPixelRow/8) * 32;

	// bool windowOn = ((lcdRegister & BIT5) > 0) ? true : false;

	// if (windowOn && yPixel >= WindowYPos) {
	// 	yTileRow = yWindowTileRow;
	// }	

	for (int xPixel = 0; xPixel < 160; xPixel++) {

		BYTE xPixelColumn = ScrollX + xPixel;
		WORD xTileColumn = xPixelColumn/8;
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
		BYTE tileNumber = this->memory.readByte(backgroundTileMap);
		SIGNED_BYTE signedTileNumber = (SIGNED_BYTE)this->memory.readByte(backgroundTileMap);

		row = row * 2; //each pixel row is represented by 2 bytes

		SIGNED_WORD tileAddress = 0;
		if ((lcdRegister & BIT4) > 0) {
			tileAddress = 0x8000 + (tileNumber*16) + row;
		}
		else {
			tileAddress = 0x8800 + ((signedTileNumber + 128) * 16) + row;
		} 

		BYTE tileDataRow = this->memory.readByte(tileAddress);
		BYTE tileDataRow2 = this->memory.readByte(tileAddress + 1);
			
		BYTE color = getPixelColor(tileDataRow, tileDataRow2, xPixelColumn % 8, 0xFF47);
		this->gpu.screen[xPixel][yPixel] = color;
	}
}

void CPU::DrawSprites() {

	BYTE lcdRegister = this->memory.readByte(0xFF40);
	if (lcdRegister & BIT1 > 0) {

		BYTE spriteSize = lcdRegister & BIT2;
		int ySize = 8;
		if (spriteSize > 0) {
			ySize = 16;
		}
		int yLine = (int)this->memory.readByte(0xFF44);

		for (int i = 0; i < 40; i++) {
			WORD spriteAddress = 0xFE00 + (i*4);

			int yPosition = (int)this->memory.readByte(spriteAddress) - 16;

			if ((yLine >= yPosition) && (yLine < (yPosition+ySize))) {
				int xPosition = (int)this->memory.readByte(spriteAddress + 1) - 8;
				
				if (xPosition >= -7 && xPosition <= 153) {
					
					BYTE patternNumber = this->memory.readByte(spriteAddress + 2);
					if (ySize == 16) {
						patternNumber &= ~(BIT0);
					}
					
					BYTE spriteFlags = this->memory.readByte(spriteAddress + 3);

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
					BYTE tileDataRow = this->memory.readByte(tileDataAddress);
					BYTE tileDataRow2 = this->memory.readByte(tileDataAddress + 1);
					for (int x = xPosition; x < (xPosition + 8); x++) {
						if (x >= 0 && x <= 160) {
							int pixelXBit = x - xPosition;
							if (xFlip > 0) {
								pixelXBit = 7 - pixelXBit;
							}
							
							pixelXBit -= 7;
							pixelXBit *= -1;

							BYTE colorValue = GetBit(tileDataRow2, pixelXBit);
							colorValue = (colorValue << 1) | GetBit(tileDataRow, pixelXBit);

							BYTE color = getPixelColor(paletteAddress, colorValue);

							BYTE pixelValue = this->gpu.screen[x][yLine];
							if (colorValue == 0) {

							} else if (priorityOverBG == 0 || ((priorityOverBG == 1) && (pixelValue == 0))) {
								this->gpu.screen[x][yLine] = color;
							}
						}
					}
				}			 
			}
		}
	}

}

BYTE CPU::getPixelColor(BYTE tileDataRow, BYTE tileDataRow2, int bitPosition, WORD paletteAddress) {

	bitPosition -= 7;
	bitPosition *= -1;

	BYTE colorValue = GetBit(tileDataRow2, bitPosition);
	colorValue = (colorValue << 1) | GetBit(tileDataRow, bitPosition);

	BYTE colorPalette = this->memory.readByte(paletteAddress);

	BYTE color = 0;
	switch(colorValue){
		case 0: color = (colorPalette & (BIT1 | BIT0)); break;
		case 1:	color = ((colorPalette & (BIT3 | BIT2)) >> 2); break;
		case 2:	color = ((colorPalette & (BIT5 | BIT4)) >> 4); break;
		case 3: color = ((colorPalette & (BIT7 | BIT6)) >> 6); break;
	}

	return color;
}

BYTE CPU::getPixelColor(WORD paletteAddress, BYTE colorValue) {
	BYTE colorPalette = this->memory.readByte(paletteAddress);

	BYTE color = 0;
	switch(colorValue){
		case 0: color = (colorPalette & (BIT1 | BIT0)); break;
		case 1:	color = ((colorPalette & (BIT3 | BIT2)) >> 2); break;
		case 2:	color = ((colorPalette & (BIT5 | BIT4)) >> 4); break;
		case 3: color = ((colorPalette & (BIT7 | BIT6)) >> 6); break;
	}

	return color;
}

bool CPU::CheckInput(){
	bool keyPressed = false;
	SDL_Event e;
	while( SDL_PollEvent(&e) != 0) {
		
		if(e.type == SDL_QUIT) {
			this->quit = true;
		}

		if(e.type == SDL_KEYDOWN) {
			
			switch (e.key.keysym.sym) {
				case SDLK_RETURN: 	if(GetBit(this->memory.joypad, 7) == 1) {
										keyPressed = true; 
										this->memory.joypad &= (~BIT7);
									}
									break;
				case SDLK_RSHIFT: 	if(GetBit(this->memory.joypad, 6) == 1) {
										keyPressed = true; 
										this->memory.joypad &= (~BIT6); 
									}
									break;
				case SDLK_x: 		if(GetBit(this->memory.joypad, 5) == 1) {
										keyPressed = true; 
										this->memory.joypad &= (~BIT5); 
									}
									break;
				case SDLK_z: 		if(GetBit(this->memory.joypad, 4) == 1) {
										keyPressed = true; 
										this->memory.joypad &= (~BIT4); 
									}
									break;
				case SDLK_DOWN: 	if(GetBit(this->memory.joypad, 3) == 1) {
										keyPressed = true; 
										this->memory.joypad &= (~BIT3); 
									}
									break;
				case SDLK_UP: 		if(GetBit(this->memory.joypad, 2) == 1) {
										keyPressed = true; 
										this->memory.joypad &= (~BIT2); 
									}
									break;
				case SDLK_LEFT: 	if(GetBit(this->memory.joypad, 1) == 1) {
										keyPressed = true; 
										this->memory.joypad &= (~BIT1); 
									}
									break;
				case SDLK_RIGHT: 	if(GetBit(this->memory.joypad, 0) == 1) {
										keyPressed = true; 
										this->memory.joypad &= (~BIT0); 
									}
									break;
			}
		}
		else if (e.type == SDL_KEYUP) {

			switch (e.key.keysym.sym) {
				case SDLK_RETURN: 	this->memory.joypad |= BIT7; break;
				case SDLK_RSHIFT: 	this->memory.joypad |= BIT6; break;
				case SDLK_x: 		this->memory.joypad |= BIT5; break;
				case SDLK_z: 		this->memory.joypad |= BIT4; break;
				case SDLK_DOWN: 	this->memory.joypad |= BIT3; break;
				case SDLK_UP: 		this->memory.joypad |= BIT2; break;
				case SDLK_LEFT: 	this->memory.joypad |= BIT1; break;
				case SDLK_RIGHT: 	this->memory.joypad |= BIT0; break;
			}
		}
	}

	if (keyPressed) {
		requestInterrupt(Interrupt::Transition);
	}
}

bool CPU::IsOn() {
	return !(this->quit);
}

void CPU::UpdateTimers(int cycles) {

	updateDividerTimer(cycles);
	updateTimerFrequency();

	bool isTimerEnabled = (this->memory.readByte(0xFF07) & BIT2) > 0;
	if (isTimerEnabled) {
		this->timerCounter += cycles;

		while (this->timerCounter >= timerFrequency) {
			this->timerCounter -= timerFrequency;

			BYTE timer = this->memory.readByte(0xFF05);
			if (timer == 255) {
				BYTE resetTimerValue = this->memory.readByte(0xFF06);
				//cout << hex << "reset timer value: " << (int) resetTimerValue << endl;
				this->memory.writeByte(0xFF05, resetTimerValue);
				requestInterrupt(Interrupt::TimerOverflow);
			}
			else {
				timer += 1;
				//cout << hex << "Timer value: " << (int) timer << "   TimerCounter value: " << (int) this->timerCounter << endl;
				this->memory.writeByte(0xFF05, timer);
			}
		}
	}
}

void CPU::HandleInterrupt() {
	BYTE interruptFlag = this->memory.readByte(0xFF0F);
	BYTE iEnabled = this->memory.readByte(0xFFFF);

	if (interruptEnabled) {

		if (interruptFlag > 0x00) {
			Interrupt i = getInterrupt(interruptFlag, iEnabled);

			if (i != Interrupt::None) {
				this->interruptEnabled = false;

				interruptFlag &= ~(i);
				this->memory.writeByte(0xFF0F, interruptFlag);
				
				PushReg(this->PC.reg);

				switch(i) {
					case Interrupt::VBlank: this->PC.reg = 0x40; break;
					case Interrupt::LCDC: this->PC.reg = 0x48; break;
					case Interrupt::TimerOverflow: 
						halt = false; 
						this->PC.reg = 0x50; 
						break;
					case Interrupt::SerialTransfer: this->PC.reg = 0x58; break;
					case Interrupt::Transition: this->PC.reg = 0x60; break;
					default: break;
				}
			}
		}
	}
	else {
		if (halt == true) {
			if ((interruptFlag & iEnabled) > 0) {
				halt = false;
			}
		}
	}
}

void CPU::updateDividerTimer(int cycles) {
	dividerCounter += cycles;
	if (dividerCounter >= 255) {
		this->memory.incrementDividerRegister();
		dividerCounter = 0;
	}
}

void CPU::updateTimerFrequency() {
	BYTE frequency = this->memory.readByte(0xFF07);
	BYTE frequencyMask = (BIT1 | BIT0);
	frequency = frequency & frequencyMask;

	int newFrequency = timerFrequency;
	switch(frequency) {
		case 0: newFrequency = 1024; break;
		case 1:	newFrequency = 16; break;
		case 2:	newFrequency = 64; break;
		case 3:	newFrequency = 256; break;
	}

	if (newFrequency != timerFrequency) {
		timerFrequency = newFrequency;
		this->timerCounter = 0;
	}
}

void CPU::UpdateCPUCycles(int cycles) {
	this->UpdateScreen(cycles);
	this->UpdateTimers(cycles);
	this->cyclesThisFrame += cycles;
}


Interrupt CPU::getInterrupt(BYTE interruptFlag, BYTE enabled) {
	Interrupt retVal = Interrupt::None;

	interruptFlag = interruptFlag & enabled;

	if ((interruptFlag & Interrupt::VBlank) > 0) {
		retVal = Interrupt::VBlank;
	}
	else if ((interruptFlag & Interrupt::LCDC) > 0) {
		retVal = Interrupt::LCDC;
	}
	else if ((interruptFlag & Interrupt::TimerOverflow) > 0) {
		retVal = Interrupt::TimerOverflow;
	}
	else if ((interruptFlag & Interrupt::SerialTransfer) > 0) {
		retVal = Interrupt::SerialTransfer;
	}
	else if ((interruptFlag & Interrupt::Transition) > 0) {
		retVal = Interrupt::Transition;
	}

	return retVal;
}

void CPU::requestInterrupt(Interrupt interrupt) {
	BYTE interruptFlag = this->memory.readByte(0xFF0F);
	interruptFlag |= (BYTE)interrupt;
	this->memory.writeByte(0xFF0F, interruptFlag);
}

BYTE CPU::getFlag(Flag flag) {
	BYTE retVal = 0x00;

	switch(flag) {
		case Flag::z:
			retVal = (this->AF.lo & BIT7) >> 7;
			break;
		case Flag::n:
			retVal = (this->AF.lo & BIT6) >> 6;
			break;
		case Flag::h:
			retVal = (this->AF.lo & BIT5) >> 5;
			break;
		case Flag::c:
			retVal = (this->AF.lo & BIT4) >> 4;
			break;
		default: break;
	}

	return retVal;
}

void CPU::setFlag(Flag flag) {
	if (flag == Flag::z) {
		this->AF.lo = this->AF.lo | BIT7;
	}
	else if (flag == Flag::n) {
		this->AF.lo = this->AF.lo | BIT6;
	}
	else if (flag == Flag::h) {
		this->AF.lo = this->AF.lo | BIT5;
	}
	else if (flag == Flag::c) {
		this->AF.lo = this->AF.lo | BIT4;
	}
}

void CPU::resetFlag(Flag flag) {
	if (flag == Flag::z) {
		this->AF.lo = this->AF.lo & (~BIT7);
	}
	else if (flag == Flag::n) {
		this->AF.lo = this->AF.lo & (~BIT6);
	}
	else if (flag == Flag::h) {
		this->AF.lo = this->AF.lo & (~BIT5);
	}
	else if (flag == Flag::c) {
		this->AF.lo = this->AF.lo & (~BIT4);
	}
}

void CPU::PushReg(WORD value) {
	BYTE lo = value & 0x00FF;
	BYTE hi = value >> 8;
	PushByte(hi);
	PushByte(lo);
}

WORD CPU::PopReg() {
	BYTE lo = PopByte();
	BYTE hi = PopByte();
	WORD retVal = hi;
	retVal = retVal << 8;
	retVal = retVal | lo;
	return retVal;
}

void CPU::PushByte(BYTE value) {
	this->SP.reg--;
	this->memory.writeByte(this->SP.reg, value);
}

BYTE CPU::PopByte() {
	BYTE retVal = this->memory.readByte(this->SP.reg);
	this->SP.reg++; 
	return retVal;
}

BYTE CPU::Add(BYTE operand1, BYTE operand2, bool addCarryFlag) {
	BYTE carry = (addCarryFlag) ? getFlag(Flag::c) : 0;
	bool setHalfCarry = (((operand1 & 0x0F) + (operand2 & 0x0F) + (carry & 0x0F)) > 0x0F);
	BYTE sum = operand1 + operand2 + carry;

	if (sum == 0) {
		setFlag(Flag::z);
	}
	else {
		resetFlag(Flag::z);
	}

	resetFlag(Flag::n);

	if (setHalfCarry) {
		setFlag(Flag::h);
	}
	else {
		resetFlag(Flag::h);
	}

	if (sum < (operand1 + carry)) {
		setFlag(Flag::c);
	}
	else {
		resetFlag(Flag::c);
	}
	
	return sum;
}

WORD CPU::Add16Bit(WORD operand1, WORD operand2) {
	bool setHalfCarry = ((operand1 & 0x0FFF) + (operand2 & 0x0FFF) > 0x0FFF);
	WORD sum = operand1 + operand2;

	resetFlag(Flag::n);

	if (setHalfCarry) {
		setFlag(Flag::h);
	}
	else {
		resetFlag(Flag::h);
	}

	if (sum < operand1) {
		setFlag(Flag::c);
	}
	else {
		resetFlag(Flag::c);
	}
	
	return sum;
}

WORD CPU::Add16BitSigned(WORD operand1, SIGNED_BYTE operand2) {
	bool setHalfCarry = ((operand1 & 0x000F) + (operand2 & 0x000F) & 0x00F0);
	bool setCarry = ((operand1 & 0x00FF) + (operand2 & 0x00FF) & 0x0F00);

	WORD sum = operand1 + operand2;

	resetFlag(Flag::z);
	resetFlag(Flag::n);

	if (setHalfCarry) {
		setFlag(Flag::h);
	}
	else {
		resetFlag(Flag::h);
	}

	if (setCarry) {
		setFlag(Flag::c);
	}
	else {
		resetFlag(Flag::c);
	}
	
	return sum;
}

BYTE CPU::Subtract(BYTE from, BYTE sub, bool subCarryFlag) {
	BYTE carry = (subCarryFlag) ? getFlag(Flag::c) : 0;
	bool setHalfCarry = ((int)(from & 0x0F) - (int)((sub) & 0x0F) - (int)(carry) < 0x00);

	BYTE total = from - sub - carry;

	if (total > (from - carry)) {
		setFlag(Flag::c);
	}
	else {
		resetFlag(Flag::c);
	}

	if (total == 0) {
		setFlag(Flag::z);
	}
	else {
		resetFlag(Flag::z);
	}

	setFlag(Flag::n);

	if (setHalfCarry) {
		setFlag(Flag::h);
	}
	else {
		resetFlag(Flag::h);
	}
	
	return total;
}

BYTE CPU::XOR(BYTE operand1, BYTE operand2) {
	BYTE retVal = operand1 ^ operand2;
	if (retVal == 0) {
		setFlag(Flag::z);
	}
	else {
		resetFlag(Flag::z);
	}

	resetFlag(Flag::n);
	resetFlag(Flag::c);
	resetFlag(Flag::h);

	return retVal;
}

BYTE CPU::AND(BYTE operand1, BYTE operand2) {
	BYTE retVal = operand1 & operand2;
	if (retVal == 0) {
		setFlag(Flag::z);
	}
	else {
		resetFlag(Flag::z);
	}

	resetFlag(Flag::n);
	resetFlag(Flag::c);
	setFlag(Flag::h);

	return retVal;
}

BYTE CPU::OR(BYTE operand1, BYTE operand2) {
	BYTE retVal = operand1 | operand2;
	if (retVal == 0) {
		setFlag(Flag::z);
	}
	else {
		resetFlag(Flag::z);
	}

	resetFlag(Flag::n);
	resetFlag(Flag::c);
	resetFlag(Flag::h);

	return retVal;
}

void CPU::Compare(BYTE value) {
	bool setHalfCarry = ((int)(this->AF.hi & 0x0F) - (int)(value & 0x0F) < 0x00);
	BYTE diff = this->AF.hi - value;

	if (diff == 0) {
		setFlag(Flag::z);
	}
	else {
		resetFlag(Flag::z);
	}

	setFlag(Flag::n);

	if (setHalfCarry){
		setFlag(Flag::h);
	}
	else {
		resetFlag(Flag::h);
	}

	if (this->AF.hi < value) {
		setFlag(Flag::c);
	}
	else {
		resetFlag(Flag::c);
	}
}

BYTE CPU::RegInc(BYTE value) {
	bool setHalfCarry = ((value & 0x0F) + (1 & 0x0F) > 0x0F);
	value++;

	if (value == 0) {
		setFlag(Flag::z);
	}
	else {
		resetFlag(Flag::z);
	}

	resetFlag(Flag::n);
	if (setHalfCarry){
		setFlag(Flag::h);
	}
	else {
		resetFlag(Flag::h);
	}

	return value;
}

BYTE CPU::RegDec(BYTE value) {
	bool setHalfCarry = (((int)(value & 0x0F) - (int)(1 & 0x0F)) < 0x00);
	value--;

	if (value == 0) {
		setFlag(Flag::z);
	}
	else {
		resetFlag(Flag::z);
	}

	setFlag(Flag::n);

	if (setHalfCarry){
		setFlag(Flag::h);
	}
	else {
		resetFlag(Flag::h);
	}

	return value;
}

void CPU::TestBit(BYTE byte, BYTE mask) {
	byte = byte & mask;
//	cout << hex << (int)byte << endl;
	if (byte != 0) {
		resetFlag(Flag::z);
	}
	else {
		setFlag(Flag::z);
	}

	resetFlag(Flag::n);
	setFlag(Flag::h);
}

BYTE CPU::GetBit(BYTE value, int bitPos) {
	
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

BYTE CPU::SetBit(BYTE byte, BYTE bitMask, BYTE value) {
	BYTE retVal = byte;
	if (value > 0) {
		retVal |= bitMask;
	}
	else {
		retVal &= (~bitMask);
	}

	return retVal;
}

BYTE CPU::SWAP(BYTE value) {
	BYTE lower = value & 0x0F;
	BYTE higher = (value >> 4) & 0x0F;

	BYTE retVal = lower << 4;
	retVal = retVal | higher;

	if (retVal == 0) {
		setFlag(Flag::z);
	}
	else {
		resetFlag(Flag::z);
	}

	resetFlag(Flag::n);
	resetFlag(Flag::h);
	resetFlag(Flag::c);

	return retVal;
}

BYTE CPU::Rotate(BYTE value, Direction direction, bool fromC) {
	BYTE carry = 0;

	if (direction == Direction::right) {
		carry = value & BIT0;
		value = value >> 1;
		BYTE sevenBit = (fromC) ? getFlag(Flag::c) : carry;
		value = value | (sevenBit << 7);
	}
	else {
		carry = (value & BIT7) >> 7;
		value = value << 1;
		BYTE zeroBit = (fromC) ? getFlag(Flag::c) : carry; 
		value = value | zeroBit;
	}

	if (carry == 1) {
		setFlag(Flag::c);
	}
	else {
		resetFlag(Flag::c);
	}

	if (value == 0) {
		setFlag(Flag::z);
	}
	else {
		resetFlag(Flag::z);
	}

	resetFlag(Flag::n);
	resetFlag(Flag::h);

	return value;
}

BYTE CPU::Shift(BYTE value, Direction direction, bool resetSB) {
	BYTE carry = 0;

	if (direction == Direction::right) {
		carry = value & BIT0;
		BYTE bit7 = (value & BIT7);
		value = value >> 1;
		value |= (resetSB) ? 0: bit7;
	}
	else {
		carry = (value & BIT7) >> 7;
		BYTE bit0 = (value & BIT0);
		value = value << 1;
		value |= (resetSB) ? 0: bit0;
	}

	if (carry == 1) {
		setFlag(Flag::c);
	}
	else {
		resetFlag(Flag::c);
	}

	if (value == 0) {
		setFlag(Flag::z);
	}
	else {
		resetFlag(Flag::z);
	}

	resetFlag(Flag::n);
	resetFlag(Flag::h);

	return value;
}