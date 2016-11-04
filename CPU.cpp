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

	instructions[0x3e] = &CPU::LD_A_n;
	instructions[0x06] = &CPU::LD_B_n;
	instructions[0x0E] = &CPU::LD_C_n;
	instructions[0x16] = &CPU::LD_D_n;
	instructions[0x1E] = &CPU::LD_E_n;
	instructions[0x26] = &CPU::LD_H_n;
	instructions[0x2E] = &CPU::LD_L_n;

	instructions[0x7F] = &CPU::LD_A_A;
	instructions[0x78] = &CPU::LD_A_B;
	instructions[0x79] = &CPU::LD_A_C;
	instructions[0x7A] = &CPU::LD_A_D;
	instructions[0x7B] = &CPU::LD_A_E;
	instructions[0x7C] = &CPU::LD_A_H;
	instructions[0x7D] = &CPU::LD_A_L;
	instructions[0x0A] = &CPU::LD_A_BC;
	instructions[0x1A] = &CPU::LD_A_DE;
	instructions[0x7E] = &CPU::LD_A_HL;
	instructions[0xFA] = &CPU::LD_A_nn;

	instructions[0x47] = &CPU::LD_B_A;
	instructions[0x4F] = &CPU::LD_C_A;
	instructions[0x57] = &CPU::LD_D_A;
	instructions[0x5F] = &CPU::LD_E_A;
	instructions[0x67] = &CPU::LD_H_A;
	instructions[0x6F] = &CPU::LD_L_A;
	instructions[0x02] = &CPU::LD_BC_A;
	instructions[0x12] = &CPU::LD_DE_A;
	instructions[0xEA] = &CPU::LD_nn_A;

	instructions[0x77] = &CPU::LD_HL_A;
	instructions[0xe2] = &CPU::LD_FF00_C_A;
	instructions[0xe0] = &CPU::LD_FF00_n_A;

	//Load Dec
	instructions[0x32] = &CPU::LDD_HL_A;

	//16 bit load immediate
	instructions[0x01] = &CPU::LD_BC_nn;
	instructions[0x11] = &CPU::LD_DE_nn;
	instructions[0x21] = &CPU::LD_HL_nn;
	instructions[0x31] = &CPU::LD_SP_nn;

	//XORs
	instructions[0xAF] = &CPU::XOR_A;

	//Incs
	instructions[0x3C] = &CPU::INC_A;
	instructions[0x04] = &CPU::INC_B;
	instructions[0x0C] = &CPU::INC_C;
	instructions[0x14] = &CPU::INC_D;
	instructions[0x1C] = &CPU::INC_E;
	instructions[0x24] = &CPU::INC_H;
	instructions[0x2C] = &CPU::INC_L;
	instructions[0x34] = &CPU::INC_HL;

	//Jumps
	instructions[0x20] = &CPU::JR_NZ;

	instructions[0xCD] = &CPU::CALL_nn;
	instructions[0xF5] = &CPU::PUSH_AF;
	instructions[0xC5] = &CPU::PUSH_BC;
	instructions[0xD5] = &CPU::PUSH_DE;
	instructions[0xE5] = &CPU::PUSH_HL;

	instructions[0xF1] = &CPU::POP_AF;
	instructions[0xC1] = &CPU::POP_BC;
	instructions[0xD1] = &CPU::POP_DE;
	instructions[0xE1] = &CPU::POP_HL;

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
	string input;
	if (opcode == 0xcb){
		opcode = Fetch();
		if (instructions_cb[opcode] != NULL) {
			(this->*instructions_cb[opcode])();
		}
		else {
			cout << hex << "CB Opcode: cb " << (int)opcode << " is not implemented yet.";
			cin >> input;
		}
	}
	else {
		if (instructions[opcode] != NULL){
			(this->*instructions[opcode])();
		}
		else {
			cout << hex << "Opcode: " << (int)opcode << " is not implemented yet.";
			cin >> input;
		}
	}
}

//instructions
int CPU::LD_A_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	cout << hex << "LD A, " << "0x" << (int)immediate << endl;
	this->AF.hi = immediate;
}

int CPU::LD_B_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	cout << hex << "LD B, " << "0x" << (int)immediate << endl;
	this->BC.hi = immediate;
} 

int CPU::LD_C_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	cout << hex << "LD C, " << "0x" << (int)immediate << endl;
	this->BC.lo = immediate;
}

int CPU::LD_D_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	cout << hex << "LD D, " << "0x" << (int)immediate << endl;
	this->DE.hi = immediate;
} 

int CPU::LD_E_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	cout << hex << "LD E, " << "0x" << (int)immediate << endl;
	this->DE.lo = immediate;
}

int CPU::LD_H_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	cout << hex << "LD H, " << "0x" << (int)immediate << endl;
	this->HL.hi = immediate;
} 

int CPU::LD_L_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	cout << hex << "LD L, " << "0x" << (int)immediate << endl;
	this->HL.lo = immediate;
}

int CPU::LD_A_A() {
	cout << hex << "LD A, A" << endl;
}

int CPU::LD_A_B() {
	this->AF.hi = this->BC.hi;
	cout << hex << "LD A, B" << endl;
}

int CPU::LD_A_C() {
	this->AF.hi = this->BC.lo;
	cout << hex << "LD A, C" << endl;
}

int CPU::LD_A_D() {
	this->AF.hi = this->DE.hi;
	cout << hex << "LD A, D" << endl;
}

int CPU::LD_A_E() {
	this->AF.hi = this->DE.lo;
	cout << hex << "LD A, E" << endl;
}

int CPU::LD_A_H() {
	this->AF.hi = this->HL.hi;
	cout << hex << "LD A, H" << endl;
}

int CPU::LD_A_L() {
	this->AF.hi = this->HL.lo;
	cout << hex << "LD A, L" << endl;
}

int CPU::LD_A_BC() {
	this->AF.hi = this->memory.readByte(this->BC.reg);
	cout << hex << "LD A, (BC)" << endl;
}

int CPU::LD_A_DE() {
	this->AF.hi = this->memory.readByte(this->DE.reg);
	cout << hex << "LD A, (DE)" << endl;
}

int CPU::LD_A_HL() {
	this->AF.hi = this->memory.readByte(this->HL.reg);
	cout << hex << "LD A, (HL)" << endl;
}

int CPU::LD_A_nn() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	this->AF.hi = this->memory.readByte(address);
	cout << hex << "LD A, (0x" << (int)address << ")" << endl;
}

int CPU::LD_B_A() {
	this->BC.hi = this->AF.hi;
	cout << hex << "LD B, A" << endl;
}

int CPU::LD_C_A() {
	this->BC.lo = this->AF.hi;
	cout << hex << "LD C, A" << endl;
}

int CPU::LD_D_A() {
	this->DE.hi = this->AF.hi;
	cout << hex << "LD D, A" << endl;
}

int CPU::LD_E_A() {
	this->DE.lo = this->AF.hi;
	cout << hex << "LD E, A" << endl;
}

int CPU::LD_H_A() {
	this->HL.hi = this->AF.hi;
	cout << hex << "LD H, A" << endl;
}

int CPU::LD_L_A() {
	this->HL.lo = this->AF.hi;
	cout << hex << "LD L, A" << endl;
}

int CPU::LD_BC_A() {
	this->memory.writeByte(this->BC.reg, this->AF.hi);
	cout << hex << "LD (BC), A" << endl;
}

int CPU::LD_DE_A() {
	this->memory.writeByte(this->DE.reg, this->AF.hi);
	cout << hex << "LD (DE), A" << endl;
}

int CPU::LD_nn_A() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	this->memory.writeByte(immediate, this->AF.hi);
	cout << hex << "LD (0x" << (int)immediate << "), A" << endl;
}

int CPU::LD_HL_A() {
	this->memory.writeByte(this->HL.reg, this->AF.hi);
	cout << hex << "LD (HL), A" << endl;
}

int CPU::LD_FF00_C_A(){
	WORD address = 0xFF00 + this->BC.lo;
	this->memory.writeByte(address, this->AF.hi);
	cout << hex << "LD ($FF00 + C), A" << endl;
}

int CPU::LD_FF00_n_A(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	WORD address = 0xFF00 + immediate;
	this->memory.writeByte(address, this->AF.hi);
	cout << hex << "LD ($FF00 + 0x" << (int)immediate << "), A" << endl;
}

int CPU::LDD_HL_A(){
	this->memory.writeByte(this->HL.reg, this->AF.hi);
	this->HL.reg--;
	cout << hex << "LDD (HL), A" << endl;
}

int CPU::LD_BC_nn(){
	this->BC.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	cout << hex << "LD BC, " << "0x" << (int)this->BC.reg << endl;
}

int CPU::LD_DE_nn(){
	this->DE.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	cout << hex << "LD DE, " << "0x" << (int)this->DE.reg << endl;
}

int CPU::LD_HL_nn(){
	this->HL.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	cout << hex << "LD HL, " << "0x" << (int)this->HL.reg << endl;
}

int CPU::LD_SP_nn(){
	this->SP.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	cout << hex << "LD SP, " << "0x" << (int)this->SP.reg << endl;
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

void CPU::PushWord(WORD value) {
	BYTE lo = value & 0x00FF;
	BYTE hi = value >> 8;
	PushByte(lo);
	PushByte(hi);
}

WORD CPU::PopWord() {
	WORD retVal = PopByte();
	retVal << 8;
	retVal = retVal | PopByte();

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

int CPU::CALL_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	PushWord(this->PC.reg);
	this->PC.reg = immediate;
	cout << hex << "CALL 0x" << (int)immediate << endl;
}

int CPU::PUSH_AF() {
	PushWord(this->AF.reg);
	cout << hex << "PUSH AF" << endl;
}

int CPU::PUSH_BC() {
	PushWord(this->BC.reg);
	cout << hex << "PUSH BC" << endl;
}

int CPU::PUSH_DE() {
	PushWord(this->DE.reg);
	cout << hex << "PUSH DE" << endl;
}

int CPU::PUSH_HL() {
	PushWord(this->HL.reg);
	cout << hex << "PUSH HL" << endl;
}

int CPU::POP_AF() {
	this->AF.reg = PopWord();
	cout << hex << "POP AF" << endl;
}

int CPU::POP_BC() {
	this->BC.reg = PopWord();
	cout << hex << "POP BC" << endl;
}

int CPU::POP_DE() {
	this->DE.reg = PopWord();
	cout << hex << "POP DE" << endl;
}

int CPU::POP_HL() {
	this->HL.reg = PopWord();
	cout << hex << "POP HL" << endl;
}



//Math instructions
int CPU::XOR_A(){
	this->AF.hi = 0x00;
	cout << hex << "XOR A" << endl;
}


BYTE CPU::RegInc(BYTE value) {
	BYTE bit3Before = value & BIT3;
	value++;
	BYTE bit3After = value & BIT3;

	if (value == 0) {
		this->flags.z = 1;
	}
	this->flags.n = 0;
	if (bit3Before > 0 && bit3After == 0){
		this->flags.h = 1;
	}
}

int CPU::INC_A() {
	this->AF.hi = RegInc(this->AF.hi);
	cout << hex << "INC A" << endl;
}

int CPU::INC_B() {
	this->BC.hi = RegInc(this->BC.hi);
	cout << hex << "INC B" << endl;
}

int CPU::INC_C() {
	this->BC.lo = RegInc(this->BC.lo);
	cout << hex << "INC C" << endl;
}

int CPU::INC_D() {
	this->DE.hi = RegInc(this->DE.hi);
	cout << hex << "INC D" << endl;
}

int CPU::INC_E() {
	this->DE.lo = RegInc(this->DE.lo);
	cout << hex << "INC E" << endl;
}

int CPU::INC_H() {
	this->HL.hi = RegInc(this->HL.hi);
	cout << hex << "INC H" << endl;
}

int CPU::INC_L() {
	this->HL.lo = RegInc(this->HL.lo);
	cout << hex << "INC L" << endl;
}

int CPU::INC_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = RegInc(value);
	this->memory.writeByte(this->HL.reg, value);
	cout << hex << "INC (HL)" << endl;
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

