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

	//Jumps
	instructions[0x20] = &CPU::JR_NZ;

	//Bit opcodes
	instructions_cb[0x7c] = &CPU::BIT_7_H;
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

	if (opcode == 0xcb){
		opcode = Fetch();
		if (instructions_cb[opcode] != NULL) {
			(this->*instructions_cb[opcode])();
		}
		else {
			cout << hex << "Opcode: cb " << (int)opcode << " is not implemented yet.";
		}
	}
	else {
		if (instructions[opcode] != NULL){
			(this->*instructions[opcode])();
		}
		else {
			cout << hex << "Opcode: " << (int)opcode << " is not implemented yet.";
		}
	}
}

//instructions
int CPU::LD_B_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	cout << hex << "LD B, " << "0x" << (int)immediate << endl;
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
	this->memory.writeByte(this->HL.reg, this->AF.hi);
	this->HL.reg--;
	cout << hex << "LDD HL, A              " << (int)this->HL.reg << endl;
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

//Jump Instructions
int CPU::JR_NZ() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	cout << hex << "JR NZ, " << (int)offset << endl;
	if (this->flags.z == 0) {
		this->PC.reg += offset;
		cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
}


//Math instructions
int CPU::XOR_A(){
	this->AF.hi = 0x00;
	cout << hex << "XOR A" << endl;
}


//Bit instructions
void CPU::TestBit(BYTE byte, BYTE mask) {
	byte = byte & mask;
	cout << hex << (int)byte << endl;
	if (byte != 0) {
		this->flags.z = 0;
	}
	else {
		this->flags.z = 1;
	}

	this->flags.n = 0;
	this->flags.h = 1;
}


int CPU::BIT_7_H() {
	TestBit(this->HL.hi, BIT7);
	cout << hex << "BIT 7, H" << endl;
}