#include "CPU.hpp"


CPU::CPU(){
	//Init Registers
	this->SP.reg = 0xFFFE;
	this->PC.reg = 0x100;

	this->AF.reg = 0x01B0;
	this->BC.reg = 0x0013;
	this->DE.reg = 0x00D8;
	this->HL.reg = 0x014D;

	//Init Memory
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
}

CPU::~CPU(){

}

bool CPU::LoadCartridge(){
	size_t result;

	FILE * pFile = fopen("DrMario.gb", "rb");
	if (pFile == NULL) {
		cout << "Could not find file";
		return false;
	}

	result = fread(this->Cartridge, 1, 200000, pFile);

	return true;
}

BYTE CPU::Fetch(){
	BYTE opcode = this->Cartridge[this->PC.reg];
	this->PC.reg = this->PC.reg + 1;
	return opcode;
}

