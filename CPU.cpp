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

void CPU::LoadCartridge(){
	if (!this->memory.LoadCartridge()) {
		cout << "Cartridge load failed";
	}
}

BYTE CPU::Fetch(){
	BYTE opcode = this->memory.readByte(this->PC.reg);
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

//instructions

int CPU::LD_B_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->BC.hi = immediate;
	cout << hex << "LD B, " << (int)this->BC.hi << endl;
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
	this->SP.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	cout << hex << "LD SP, " << "0x" << (int)this->SP.reg << endl;
}

int CPU::LD_HL_nn(){
	this->HL.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	cout << hex << "LD HL, " << "0x" << (int)this->HL.reg << endl;
}

//Math instructions
int CPU::XOR_A(){
	this->AF.hi = 0x00;
	cout << hex << "XOR A" << endl;
}