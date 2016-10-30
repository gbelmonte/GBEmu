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
	instructions_cb[0x47] = &CPU::BIT_0_A;
	instructions_cb[0x4F] = &CPU::BIT_1_A;
	instructions_cb[0x57] = &CPU::BIT_2_A;
	instructions_cb[0x5F] = &CPU::BIT_3_A;
	instructions_cb[0x67] = &CPU::BIT_4_A;
	instructions_cb[0x6F] = &CPU::BIT_5_A;
	instructions_cb[0x77] = &CPU::BIT_6_A;
	instructions_cb[0x7F] = &CPU::BIT_7_A;
	instructions_cb[0x40] = &CPU::BIT_0_B;
	instructions_cb[0x48] = &CPU::BIT_1_B;
	instructions_cb[0x50] = &CPU::BIT_2_B;
	instructions_cb[0x58] = &CPU::BIT_3_B;
	instructions_cb[0x60] = &CPU::BIT_4_B;
	instructions_cb[0x68] = &CPU::BIT_5_B;
	instructions_cb[0x70] = &CPU::BIT_6_B;
	instructions_cb[0x78] = &CPU::BIT_7_B;
	instructions_cb[0x41] = &CPU::BIT_0_C;
	instructions_cb[0x49] = &CPU::BIT_1_C;
	instructions_cb[0x51] = &CPU::BIT_2_C;
	instructions_cb[0x59] = &CPU::BIT_3_C;
	instructions_cb[0x61] = &CPU::BIT_4_C;
	instructions_cb[0x69] = &CPU::BIT_5_C;
	instructions_cb[0x71] = &CPU::BIT_6_C;
	instructions_cb[0x79] = &CPU::BIT_7_C;
	instructions_cb[0x42] = &CPU::BIT_0_D;
	instructions_cb[0x4A] = &CPU::BIT_1_D;
	instructions_cb[0x52] = &CPU::BIT_2_D;
	instructions_cb[0x5A] = &CPU::BIT_3_D;
	instructions_cb[0x62] = &CPU::BIT_4_D;
	instructions_cb[0x6A] = &CPU::BIT_5_D;
	instructions_cb[0x72] = &CPU::BIT_6_D;
	instructions_cb[0x7A] = &CPU::BIT_7_D;
	instructions_cb[0x43] = &CPU::BIT_0_E;
	instructions_cb[0x4B] = &CPU::BIT_1_E;
	instructions_cb[0x53] = &CPU::BIT_2_E;
	instructions_cb[0x5B] = &CPU::BIT_3_E;
	instructions_cb[0x63] = &CPU::BIT_4_E;
	instructions_cb[0x6B] = &CPU::BIT_5_E;
	instructions_cb[0x73] = &CPU::BIT_6_E;
	instructions_cb[0x7B] = &CPU::BIT_7_E;
	instructions_cb[0x44] = &CPU::BIT_0_H;
	instructions_cb[0x4C] = &CPU::BIT_1_H;
	instructions_cb[0x54] = &CPU::BIT_2_H;
	instructions_cb[0x5C] = &CPU::BIT_3_H;
	instructions_cb[0x64] = &CPU::BIT_4_H;
	instructions_cb[0x6C] = &CPU::BIT_5_H;
	instructions_cb[0x74] = &CPU::BIT_6_H;
	instructions_cb[0x7C] = &CPU::BIT_7_H;
	instructions_cb[0x45] = &CPU::BIT_0_L;
	instructions_cb[0x4D] = &CPU::BIT_1_L;
	instructions_cb[0x55] = &CPU::BIT_2_L;
	instructions_cb[0x5D] = &CPU::BIT_3_L;
	instructions_cb[0x65] = &CPU::BIT_4_L;
	instructions_cb[0x6D] = &CPU::BIT_5_L;
	instructions_cb[0x75] = &CPU::BIT_6_L;
	instructions_cb[0x7D] = &CPU::BIT_7_L;
	instructions_cb[0x46] = &CPU::BIT_0_HL;
	instructions_cb[0x4E] = &CPU::BIT_1_HL;
	instructions_cb[0x56] = &CPU::BIT_2_HL;
	instructions_cb[0x5E] = &CPU::BIT_3_HL;
	instructions_cb[0x66] = &CPU::BIT_4_HL;
	instructions_cb[0x6E] = &CPU::BIT_5_HL;
	instructions_cb[0x76] = &CPU::BIT_6_HL;
	instructions_cb[0x7E] = &CPU::BIT_7_HL;
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

int CPU::BIT_0_A() {
	TestBit(this->AF.hi, BIT0);
	cout << hex << "Bit 0, A" << endl;
} 

int CPU::BIT_1_A() {
	TestBit(this->AF.hi, BIT1);
	cout << hex << "Bit 1, A" << endl;
}

int CPU::BIT_2_A() {
	TestBit(this->AF.hi, BIT2);
	cout << hex << "Bit 2, A" << endl;
}

int CPU::BIT_3_A() {
	TestBit(this->AF.hi, BIT3);
	cout << hex << "Bit 3, A" << endl;
}

int CPU::BIT_4_A() {
	TestBit(this->AF.hi, BIT4);
	cout << hex << "Bit 4, A" << endl;
}

int CPU::BIT_5_A() {
	TestBit(this->AF.hi, BIT5);
	cout << hex << "Bit 5, A" << endl;
}

int CPU::BIT_6_A() {
	TestBit(this->AF.hi, BIT6);
	cout << hex << "Bit 6, A" << endl;
}

int CPU::BIT_7_A() {
	TestBit(this->AF.hi, BIT7);
	cout << hex << "Bit 7, A" << endl;
}

int CPU::BIT_0_B() {
	TestBit(this->BC.hi, BIT0);
	cout << hex << "Bit 0, B" << endl;
}

int CPU::BIT_1_B() {
	TestBit(this->BC.hi, BIT1);
	cout << hex << "Bit 1, B" << endl;
}

int CPU::BIT_2_B() {
	TestBit(this->BC.hi, BIT2);
	cout << hex << "Bit 2, B" << endl;
}

int CPU::BIT_3_B() {
	TestBit(this->BC.hi, BIT3);
	cout << hex << "Bit 3, B" << endl;
}

int CPU::BIT_4_B() {
	TestBit(this->BC.hi, BIT4);
	cout << hex << "Bit 4, B" << endl;
}

int CPU::BIT_5_B() {
	TestBit(this->BC.hi, BIT5);
	cout << hex << "Bit 5, B" << endl;
}

int CPU::BIT_6_B() {
	TestBit(this->BC.hi, BIT6);
	cout << hex << "Bit 6, B" << endl;
}

int CPU::BIT_7_B() {
	TestBit(this->BC.hi, BIT7);
	cout << hex << "Bit 7, B" << endl;
}

int CPU::BIT_0_C() {
	TestBit(this->BC.lo, BIT0);
	cout << hex << "Bit 0, C" << endl;
}

int CPU::BIT_1_C() {
	TestBit(this->BC.lo, BIT1);
	cout << hex << "Bit 1, C" << endl;
}

int CPU::BIT_2_C() {
	TestBit(this->BC.lo, BIT2);
	cout << hex << "Bit 2, C" << endl;
}

int CPU::BIT_3_C() {
	TestBit(this->BC.lo, BIT3);
	cout << hex << "Bit 3, C" << endl;
}

int CPU::BIT_4_C() {
	TestBit(this->BC.lo, BIT4);
	cout << hex << "Bit 4, C" << endl;
}

int CPU::BIT_5_C() {
	TestBit(this->BC.lo, BIT5);
	cout << hex << "Bit 5, C" << endl;
}

int CPU::BIT_6_C() {
	TestBit(this->BC.lo, BIT6);
	cout << hex << "Bit 6, C" << endl;
}

int CPU::BIT_7_C() {
	TestBit(this->BC.lo, BIT7);
	cout << hex << "Bit 7, C" << endl;
}

int CPU::BIT_0_D() {
	TestBit(this->DE.hi, BIT0);
	cout << hex << "Bit 0, D" << endl;
}

int CPU::BIT_1_D() {
	TestBit(this->DE.hi, BIT1);
	cout << hex << "Bit 1, D" << endl;
}

int CPU::BIT_2_D() {
	TestBit(this->DE.hi, BIT2);
	cout << hex << "Bit 2, D" << endl;
}

int CPU::BIT_3_D() {
	TestBit(this->DE.hi, BIT3);
	cout << hex << "Bit 3, D" << endl;
}

int CPU::BIT_4_D() {
	TestBit(this->DE.hi, BIT4);
	cout << hex << "Bit 4, D" << endl;
}

int CPU::BIT_5_D() {
	TestBit(this->DE.hi, BIT5);
	cout << hex << "Bit 5, D" << endl;
}

int CPU::BIT_6_D() {
	TestBit(this->DE.hi, BIT6);
	cout << hex << "Bit 6, D" << endl;
}

int CPU::BIT_7_D() {
	TestBit(this->DE.hi, BIT7);
	cout << hex << "Bit 7, D" << endl;
}
 
int CPU::BIT_0_E() {
	TestBit(this->DE.lo, BIT0);
	cout << hex << "Bit 0, E" << endl;
}

int CPU::BIT_1_E() {
	TestBit(this->DE.lo, BIT1);
	cout << hex << "Bit 1, E" << endl;
}

int CPU::BIT_2_E() {
	TestBit(this->DE.lo, BIT2);
	cout << hex << "Bit 2, E" << endl;
}

int CPU::BIT_3_E() {
	TestBit(this->DE.lo, BIT3);
	cout << hex << "Bit 3, E" << endl;
}

int CPU::BIT_4_E() {
	TestBit(this->DE.lo, BIT4);
	cout << hex << "Bit 4, E" << endl;
}

int CPU::BIT_5_E() {
	TestBit(this->DE.lo, BIT5);
	cout << hex << "Bit 5, E" << endl;
}

int CPU::BIT_6_E() {
	TestBit(this->DE.lo, BIT6);
	cout << hex << "Bit 6, E" << endl;
}

int CPU::BIT_7_E() {
	TestBit(this->DE.lo, BIT7);
	cout << hex << "Bit 7, E" << endl;
}
 
int CPU::BIT_0_H() {
	TestBit(this->HL.hi, BIT0);
	cout << hex << "Bit 0, H" << endl;
}

int CPU::BIT_1_H() {
	TestBit(this->HL.hi, BIT1);
	cout << hex << "Bit 1, H" << endl;
}

int CPU::BIT_2_H() {
	TestBit(this->HL.hi, BIT2);
	cout << hex << "Bit 2, H" << endl;
}

int CPU::BIT_3_H() {
	TestBit(this->HL.hi, BIT3);
	cout << hex << "Bit 3, H" << endl;
}

int CPU::BIT_4_H() {
	TestBit(this->HL.hi, BIT4);
	cout << hex << "Bit 4, H" << endl;
}

int CPU::BIT_5_H() {
	TestBit(this->HL.hi, BIT5);
	cout << hex << "Bit 5, H" << endl;
}

int CPU::BIT_6_H() {
	TestBit(this->HL.hi, BIT6);
	cout << hex << "Bit 6, H" << endl;
}

int CPU::BIT_7_H() {
	TestBit(this->HL.hi, BIT7);
	cout << hex << "BIT 7, H" << endl;
}
 
int CPU::BIT_0_L() {
	TestBit(this->HL.lo, BIT0);
	cout << hex << "Bit 0, L" << endl;
}

int CPU::BIT_1_L() {
	TestBit(this->HL.lo, BIT1);
	cout << hex << "Bit 1, L" << endl;
}

int CPU::BIT_2_L() {
	TestBit(this->HL.lo, BIT2);
	cout << hex << "Bit 2, L" << endl;
}

int CPU::BIT_3_L() {
	TestBit(this->HL.lo, BIT3);
	cout << hex << "Bit 3, L" << endl;
}

int CPU::BIT_4_L() {
	TestBit(this->HL.lo, BIT4);
	cout << hex << "Bit 4, L" << endl;
}

int CPU::BIT_5_L() {
	TestBit(this->HL.lo, BIT5);
	cout << hex << "Bit 5, L" << endl;
}

int CPU::BIT_6_L() {
	TestBit(this->HL.lo, BIT6);
	cout << hex << "Bit 6, L" << endl;
}

int CPU::BIT_7_L() {
	TestBit(this->HL.lo, BIT7);
	cout << hex << "Bit 7, L" << endl;
}

int CPU::BIT_0_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT0);
	cout << hex << "Bit 0, (HL)" << endl;
}
int CPU::BIT_1_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT1);
	cout << hex << "Bit 1, (HL)" << endl;
}
int CPU::BIT_2_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT2);
	cout << hex << "Bit 2, (HL)" << endl;
}
int CPU::BIT_3_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT3);
	cout << hex << "Bit 3, (HL)" << endl;
}
int CPU::BIT_4_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT4);
	cout << hex << "Bit 4, (HL)" << endl;
}
int CPU::BIT_5_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT5);
	cout << hex << "Bit 5, (HL)" << endl;
}
int CPU::BIT_6_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT6);
	cout << hex << "Bit 6, (HL)" << endl;
}
int CPU::BIT_7_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT7);
	cout << hex << "Bit 7, (HL)" << endl;
}

