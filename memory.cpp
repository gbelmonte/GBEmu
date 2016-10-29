#include "memory.hpp"

Memory::Memory(){
	//Init memory
	this->Rom[0xFF05 - 0x8000] = 0x00;
	this->Rom[0xFF06 - 0x8000] = 0x00;
	this->Rom[0xFF07 - 0x8000] = 0x00;
	this->Rom[0xFF10 - 0x8000] = 0x80;
	this->Rom[0xFF11 - 0x8000] = 0xBF;
	this->Rom[0xFF12 - 0x8000] = 0xF3;
	this->Rom[0xFF14 - 0x8000] = 0xBF;
	this->Rom[0xFF16 - 0x8000] = 0x3F;
	this->Rom[0xFF17 - 0x8000] = 0x00;
	this->Rom[0xFF19 - 0x8000] = 0xBF;
	this->Rom[0xFF1A - 0x8000] = 0x7F;
	this->Rom[0xFF1B - 0x8000] = 0xFF;
	this->Rom[0xFF1C - 0x8000] = 0x9F;
	this->Rom[0xFF1E - 0x8000] = 0xBF;
	this->Rom[0xFF20 - 0x8000] = 0xFF;
	this->Rom[0xFF21 - 0x8000] = 0x00;
	this->Rom[0xFF22 - 0x8000] = 0x00;
	this->Rom[0xFF23 - 0x8000] = 0xBF;
	this->Rom[0xFF24 - 0x8000] = 0x77;
	this->Rom[0xFF25 - 0x8000] = 0xF3;
	this->Rom[0xFF26 - 0x8000] = 0xF1;
	this->Rom[0xFF40 - 0x8000] = 0x91;
	this->Rom[0xFF42 - 0x8000] = 0x00;
	this->Rom[0xFF43 - 0x8000] = 0x00;
	this->Rom[0xFF45 - 0x8000] = 0x00;
	this->Rom[0xFF47 - 0x8000] = 0xFC;
	this->Rom[0xFF48 - 0x8000] = 0xFF;
	this->Rom[0xFF49 - 0x8000] = 0xFF;
	this->Rom[0xFF4A - 0x8000] = 0x00;
	this->Rom[0xFF4B - 0x8000] = 0x00;
	this->Rom[0xFFFF - 0x8000] = 0x00;
}

BYTE Memory::readByte(WORD address) {
	BYTE retVal = 0;

	if(address < 0x8000){
		retVal = this->Cartridge[address];
	}
	else{
		WORD romAddress = address - 0x8000;
		retVal = this->Rom[romAddress];
	}
}

WORD Memory::readWord(WORD address) {
	WORD value = 0;
	value = readByte(address+1);
	value = value << 8;
	value = value | readByte(address);

	return value;
}

void Memory::writeByte(WORD address, BYTE value) {

	if(address < 0x8000) {
		//Attempting to write to unwriteable memory
	}
	else if (address >= 0xE000 && address < 0xFE00) {
		//Attempting to write to ECHO ram, so write to both Work ram
		WORD romAddress = address - 0x8000;
		this->Rom[romAddress] = value;
		this->Rom[romAddress - 0x2000] = value;
	}
	else if (address >= 0xFE00) {
		//Attempting to write to unwriteable memory
	}
	else {
		WORD romAddress = address - 0x8000;
		this->Rom[romAddress] = value;
	}
}

void Memory::writeWord(WORD address, WORD value) {
	//Not implemented
}

bool Memory::LoadCartridge(){
	size_t result;

	FILE * pFile = fopen("DMG_ROM.bin", "rb");
	if (pFile == NULL) {
		return false;
	}

	result = fread(this->Cartridge, 1, 200000, pFile);

	return true;
}