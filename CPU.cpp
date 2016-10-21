#include "CPU.hpp"


CPU::CPU(){
	//Init Registers
	this->SP.reg = 0xFFFE;
	//this->PC.reg = 0x100;
	this->PC.reg = 0x00;

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

	//Init instructions
	for (int i = 0; i < (sizeof((instructions))/sizeof((instructions[0]))); i++ ){
		instructions[i] = NULL;
	}

	instructions[0x06] = &CPU::LD_B_n;
	instructions[0x0E] = &CPU::LD_C_n;
	instructions[0x16] = &CPU::LD_D_n;
	instructions[0x1E] = &CPU::LD_E_n;
	instructions[0x26] = &CPU::LD_H_n;
	instructions[0x2E] = &CPU::LD_L_n;

	//Load Dec
	instructions[0x32] = &CPU::LDD_HL_A;

	//16 bit load immediate
	instructions[0x31] = &CPU::LD_SP_nn;
	instructions[0x21] = &CPU::LD_HL_nn;

	//XORs
	instructions[0xAF] = &CPU::XOR_A;
}

CPU::~CPU(){

}

bool CPU::LoadCartridge(){
	size_t result;

	FILE * pFile = fopen("DMG_ROM.bin", "rb");
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

void CPU::DecodeExecute(BYTE opcode){
	if (instructions[opcode] != NULL){
		(this->*instructions[opcode])();
	}
	else{
		cout << hex << "Opcode: " << (int)opcode << " is not implemented yet.";
	}
}

//helpers
void CPU::loadByte(BYTE * dest, BYTE * src){
	(*dest) = *src;
}

void CPU::loadByte(BYTE * dest, BYTE imm){
	(*dest) = imm;
}

WORD CPU::readWord(int location){
	WORD value = 0;
	value = this->Cartridge[location+1];
	value = value << 8;
	value = value | this->Cartridge[location];

	return value;
}

//instructions

int CPU::LD_B_n(){
	BYTE immediate = this->Cartridge[this->PC.reg];
	this->PC.reg++;
	cout << hex << "LD B, " << "0x" << (int)immediate << endl;
	loadByte(&(this->BC.hi), immediate);
	//cout << hex << "B = " << (int)this->BC.hi << endl;
} 

int CPU::LD_C_n(){
	cout << "load c";
}

int CPU::LD_D_n(){
	cout << "LD B ";
} 

int CPU::LD_E_n(){
	cout << "load c";
}

int CPU::LD_H_n(){
	cout << "LD B ";
} 

int CPU::LD_L_n(){
	cout << "load c";
}

int CPU::LDD_HL_A(){
	//TODO: implement instruction
	cout << hex << "LDD HL, A" << endl;
}

int CPU::LD_SP_nn(){
	this->SP.reg = readWord(this->PC.reg);
	this->PC.reg += 2;
	cout << hex << "LD SP, " << "0x" << (int)this->SP.reg << endl;
}

int CPU::LD_HL_nn(){
	this->HL.reg = readWord(this->PC.reg);
	this->PC.reg += 2;
	cout << hex << "LD HL, " << "0x" << (int)this->HL.reg << endl;
}

//Math instructions
int CPU::XOR_A(){
	this->AF.hi = 0x00;
	cout << hex << "XOR A" << endl;
}