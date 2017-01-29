#include "memory.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

Memory::Memory(){
	//Init memory
	this->Rom[0xFF05] = 0x00;
	this->Rom[0xFF06] = 0x00;
	this->Rom[0xFF07] = 0x00;
	this->Rom[0xFF10] = 0x80;
	this->Rom[0xFF11] = 0xBF;
	this->Rom[0xFF12] = 0xF3;
	this->Rom[0xFF14] = 0xBF;
	this->Rom[0xFF16] = 0x3F;
	this->Rom[0xFF17] = 0x00;
	this->Rom[0xFF19] = 0xBF;
	this->Rom[0xFF1A] = 0x7F;
	this->Rom[0xFF1B] = 0xFF;
	this->Rom[0xFF1C] = 0x9F;
	this->Rom[0xFF1E] = 0xBF;
	this->Rom[0xFF20] = 0xFF;
	this->Rom[0xFF21] = 0x00;
	this->Rom[0xFF22] = 0x00;
	this->Rom[0xFF23] = 0xBF;
	this->Rom[0xFF24] = 0x77;
	this->Rom[0xFF25] = 0xF3;
	this->Rom[0xFF26] = 0xF1;
	this->Rom[0xFF40] = 0x91;
	this->Rom[0xFF42] = 0x00;
	this->Rom[0xFF43] = 0x00;
	this->Rom[0xFF45] = 0x00;
	this->Rom[0xFF47] = 0xFC;
	this->Rom[0xFF48] = 0xFF;
	this->Rom[0xFF49] = 0xFF;
	this->Rom[0xFF4A] = 0x00;
	this->Rom[0xFF4B] = 0x00;
	this->Rom[0xFFFF] = 0x00;

	this->type = CartridgeType::Rom;
	this->RomBank = 1;
	this->RamBank = 0;
	this->RamEnabled = false;
	this->RomMode = true;
}

BYTE Memory::readByte(WORD address) {
	BYTE retVal = 0;

	//Read Rom Bank
	if(address >= 0x4000 && address < 0x8000){
		//cout << hex << "ROM bank: " << (int)this->RomBank << endl;
		WORD romAddress = address - 0x4000;
		retVal = this->Cartridge[romAddress + (this->RomBank * 0x4000)];
		//cout << hex << "address: " << (int)address << " RomBank: " << (int)this->RomBank << " Value: " << (int)retVal << endl;
	}
	//Read Ram Bank
	else if (address >= 0xA000 && address < 0xC000) {
		WORD ramAddress = address = 0xA000;
		retVal = this->Ram[ramAddress + (this->RamBank * 0x2000)];
		//cout << hex << "RAM HIT: address: " << (int)address << " RamBank: " << (int)this->RamBank << " Value: " << (int)retVal << endl;
	}
	else if (address == 0xFF00) {
		retVal = this->Rom[address];
		retVal |= 0x0F;
	}
	else {
		retVal = this->Rom[address];
	}

	return retVal;
}

WORD Memory::readWord(WORD address) {
	WORD value = 0;
	value = readByte(address+1);
	value = value << 8;
	value = value | readByte(address);

	return value;
}

void Memory::writeByte(WORD address, BYTE value) {

	if (this->type == CartridgeType::Rom_MBC1) {
		//Turn Ram off/on
		if(address >= 0x0 && address <= 0x1FFF) {
			BYTE lowerNibble = value & 0x0F;
			if (lowerNibble == 0x0A) {
				this->RamEnabled = true;
			}
			else {
				this->RamEnabled = false;
			}
		}
		//Change ROM Bank Number
		if(address >= 0x2000 && address <= 0x3FFF) {
			BYTE bank = value & 0x1F;
			this->RomBank &= 0xE0;
			this->RomBank |= bank;
			if (this->RomBank == 0x00 || this->RomBank == 0x20 || this->RomBank == 0x40 || this->RomBank == 0x60) {
				this->RomBank++;
			}
		}
		//Change RAM Bank Number
		if(address >= 0x4000 && address <= 0x5FFF) {
			if (this->RomMode) {
				//cout << hex << "value:" << (int)value << "bank: " << (int)this->RomBank << endl;
				this->RomBank &= 0x1F;
				BYTE bank = value & 0xE0;
				this->RomBank |= bank;

				if (this->RomBank == 0x00 || this->RomBank == 0x20 || this->RomBank == 0x40 || this->RomBank == 0x60) {
					this->RomBank++;
				}
			}
			else {
				this->RamBank = value & 0x03;
			}
		}
		//Change ROM/RAM Mode
		if(address >= 0x6000 && address <= 0x7FFF) {
			BYTE mode = value & 0x01;
			//0x00 = Rom Banking Mode (up to 8kByte Ram, 2MByte Rom) default
			//0x01 = Ram Banking Mode (up to 32kByte Ram, 512kByte Rom)
			if (mode == 0) {
				this->RomMode = true;
				this->RamBank = 0;
			}
			else {
				this->RomMode = false;
			}
		}
	}

	if(address < 0x8000) {
		//Attempting to write to unwriteable memory
	}
	//Write to ram bank
	else if ((address >= 0xA000) && (address < 0xC000)) {
		if (this->RamEnabled) {
			WORD ramAddress = address - 0xA000;
			this->Ram[ramAddress + (RamBank*0x2000)] = value;
		}
	}
	else if (address >= 0xE000 && address < 0xFE00) {
		//Attempting to write to ECHO ram, so write to both Work ram
		this->Rom[address] = value;
		this->Rom[address - 0x2000] = value;
	}
	else if ((address >= 0xFEA0)  && (address < 0xFEFF)){
		//Attempting to write to unwriteable memory
	}
	else if (address == 0xFF04) {
		//Divider register resets when getting written to
		this->Rom[address] = 0;
	}
	else if (address == 0xFF46) {
		WORD dmaAddress = value << 8;
		for (int i = 0; i < 0xA0; i++) {
			BYTE dmaValue = readByte(dmaAddress + i);
			this->Rom[0xFE00 + i] = dmaValue;
		}
	}
	else {
		this->Rom[address] = value;
	}
}

void Memory::incrementDividerRegister() {
	this->Rom[0xFF04]++;
}

bool Memory::LoadCartridge(char* path){
	size_t result;
	cout << path << endl;
	FILE * pFile = fopen(path, "rb");
	if (pFile == NULL) {
		return false;
	}
	result = fread(this->Cartridge, 1, 200000, pFile);

	// pFile = fopen("DrMario.gb", "rb");
	// BYTE game[0x200000];

	// result = fread(game, 1, 200000, pFile);
	// memcpy(Cartridge + 0x100, game + 0x100, (200000 - 0x100) * sizeof(BYTE));
	//Copy cartridge to rom bank 0
	memcpy(this->Rom, this->Cartridge, 0x4000 * sizeof(BYTE));

	switch (this->Cartridge[0x147]) {
		case 0: this->type = CartridgeType::Rom; cout<<"ROM"; break;
		case 1: this->type = CartridgeType::Rom_MBC1; cout<<"ROM+MBC1"; break;
		default: cout << "Catridge type not implemented: " << this->Cartridge[0x147] << endl;
	}

	return true;
}