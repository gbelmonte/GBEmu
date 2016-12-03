#include "CPU.hpp"

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

	this->cycleCounter = 456;

	//Init instructions
	for (int i = 0; i < (sizeof((instructions))/sizeof((instructions[0]))); i++ ){
		instructions[i] = NULL;
	}

	for (int i = 0; i < (sizeof((instructions_cb))/sizeof((instructions_cb[0]))); i++ ){
		instructions_cb[i] = NULL;
	}

	instructions[0x00] = &CPU::NOP;

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

	instructions[0x40] = &CPU::LD_B_B;
	instructions[0x41] = &CPU::LD_B_C;
	instructions[0x42] = &CPU::LD_B_D;
	instructions[0x43] = &CPU::LD_B_E;
	instructions[0x44] = &CPU::LD_B_H;
	instructions[0x45] = &CPU::LD_B_L;
	instructions[0x46] = &CPU::LD_B_HL;

	instructions[0x48] = &CPU::LD_C_B;
	instructions[0x49] = &CPU::LD_C_C;
	instructions[0x4A] = &CPU::LD_C_D;
	instructions[0x4B] = &CPU::LD_C_E;
	instructions[0x4C] = &CPU::LD_C_H;
	instructions[0x4D] = &CPU::LD_C_L;
	instructions[0x4E] = &CPU::LD_C_HL;

	instructions[0x50] = &CPU::LD_D_B;
	instructions[0x51] = &CPU::LD_D_C;
	instructions[0x52] = &CPU::LD_D_D;
	instructions[0x53] = &CPU::LD_D_E;
	instructions[0x54] = &CPU::LD_D_H;
	instructions[0x55] = &CPU::LD_D_L;
	instructions[0x56] = &CPU::LD_D_HL;

	instructions[0x58] = &CPU::LD_E_B;
	instructions[0x59] = &CPU::LD_E_C;
	instructions[0x5A] = &CPU::LD_E_D;
	instructions[0x5B] = &CPU::LD_E_E;
	instructions[0x5C] = &CPU::LD_E_H;
	instructions[0x5D] = &CPU::LD_E_L;
	instructions[0x5E] = &CPU::LD_E_HL;

	instructions[0x60] = &CPU::LD_H_B;
	instructions[0x61] = &CPU::LD_H_C;
	instructions[0x62] = &CPU::LD_H_D;
	instructions[0x63] = &CPU::LD_H_E;
	instructions[0x64] = &CPU::LD_H_H;
	instructions[0x65] = &CPU::LD_H_L;
	instructions[0x66] = &CPU::LD_H_HL;

	instructions[0x68] = &CPU::LD_L_B;
	instructions[0x69] = &CPU::LD_L_C;
	instructions[0x6A] = &CPU::LD_L_D;
	instructions[0x6B] = &CPU::LD_L_E;
	instructions[0x6C] = &CPU::LD_L_H;
	instructions[0x6D] = &CPU::LD_L_L;
	instructions[0x6E] = &CPU::LD_L_HL;

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
	instructions[0x70] = &CPU::LD_HL_B;
	instructions[0x71] = &CPU::LD_HL_C;
	instructions[0x72] = &CPU::LD_HL_D;
	instructions[0x73] = &CPU::LD_HL_E;
	instructions[0x74] = &CPU::LD_HL_H;
	instructions[0x75] = &CPU::LD_HL_L;
	instructions[0x36] = &CPU::LD_HL_n;

	instructions[0xe2] = &CPU::LD_FF00_C_A;
	instructions[0xe0] = &CPU::LD_FF00_n_A;
	instructions[0xF0] = &CPU::LDH_A_FF00_n;

	//Load Dec
	instructions[0x32] = &CPU::LDD_HL_A;
	instructions[0x22] = &CPU::LDI_HL_A;

	instructions[0x2A] = &CPU::LDI_A_HL;

	//16 bit load immediate
	instructions[0xF9] = &CPU::LD_SP_HL;
	instructions[0x01] = &CPU::LD_BC_nn;
	instructions[0x11] = &CPU::LD_DE_nn;
	instructions[0x21] = &CPU::LD_HL_nn;
	instructions[0x31] = &CPU::LD_SP_nn;
	instructions[0x08] = &CPU::LD_nn_SP;

	//Add
	instructions[0x87] = &CPU::ADD_A;
	instructions[0x80] = &CPU::ADD_B;
	instructions[0x81] = &CPU::ADD_C;
	instructions[0x82] = &CPU::ADD_D;
	instructions[0x83] = &CPU::ADD_E;
	instructions[0x84] = &CPU::ADD_H;
	instructions[0x85] = &CPU::ADD_L;
	instructions[0x86] = &CPU::ADD_HL;
	instructions[0xC6] = &CPU::ADD_n;

	instructions[0x8F] = &CPU::ADC_A;
	instructions[0x88] = &CPU::ADC_B;
	instructions[0x89] = &CPU::ADC_C;
	instructions[0x8A] = &CPU::ADC_D;
	instructions[0x8B] = &CPU::ADC_E;
	instructions[0x8C] = &CPU::ADC_H;
	instructions[0x8D] = &CPU::ADC_L;
	instructions[0x8E] = &CPU::ADC_HL;
	instructions[0xCE] = &CPU::ADC_n;

	//Sub
	instructions[0x97] = &CPU::SUB_A;
	instructions[0x90] = &CPU::SUB_B;
	instructions[0x91] = &CPU::SUB_C;
	instructions[0x92] = &CPU::SUB_D;
	instructions[0x93] = &CPU::SUB_E;
	instructions[0x94] = &CPU::SUB_H;
	instructions[0x95] = &CPU::SUB_L;
	instructions[0x96] = &CPU::SUB_HL;
	instructions[0xD6] = &CPU::SUB_n;

	//XORs
	instructions[0xAF] = &CPU::XOR_A;
	instructions[0xA8] = &CPU::XOR_B;
	instructions[0xA9] = &CPU::XOR_C;
	instructions[0xAA] = &CPU::XOR_D;
	instructions[0xAB] = &CPU::XOR_E;
	instructions[0xAC] = &CPU::XOR_H;
	instructions[0xAD] = &CPU::XOR_L;
	instructions[0xAE] = &CPU::XOR_HL;
	instructions[0xEE] = &CPU::XOR_n;

	//ANDs
	instructions[0xA7] = &CPU::AND_A;
	instructions[0xA0] = &CPU::AND_B;
	instructions[0xA1] = &CPU::AND_C;
	instructions[0xA2] = &CPU::AND_D;
	instructions[0xA3] = &CPU::AND_E;
	instructions[0xA4] = &CPU::AND_H;
	instructions[0xA5] = &CPU::AND_l;
	instructions[0xA6] = &CPU::AND_HL;
	instructions[0xE6] = &CPU::AND_n;

	//ORs
	instructions[0xB7] = &CPU::OR_A;
	instructions[0xB0] = &CPU::OR_B;
	instructions[0xB1] = &CPU::OR_C;
	instructions[0xB2] = &CPU::OR_D;
	instructions[0xB3] = &CPU::OR_E;
	instructions[0xB4] = &CPU::OR_H;
	instructions[0xB5] = &CPU::OR_L;
	instructions[0xB6] = &CPU::OR_HL;
	instructions[0xF6] = &CPU::OR_n;

	instructions[0xBF] = &CPU::CP_A;
	instructions[0xB8] = &CPU::CP_B;
	instructions[0xB9] = &CPU::CP_C;
	instructions[0xBA] = &CPU::CP_D;
	instructions[0xBB] = &CPU::CP_E;
	instructions[0xBC] = &CPU::CP_H;
	instructions[0xBD] = &CPU::CP_L;
	instructions[0xBE] = &CPU::CP_MEM_HL;
	instructions[0xFE] = &CPU::CP_n;

	//Incs
	instructions[0x3C] = &CPU::INC_A;
	instructions[0x04] = &CPU::INC_B;
	instructions[0x0C] = &CPU::INC_C;
	instructions[0x14] = &CPU::INC_D;
	instructions[0x1C] = &CPU::INC_E;
	instructions[0x24] = &CPU::INC_H;
	instructions[0x2C] = &CPU::INC_L;
	instructions[0x34] = &CPU::INC_MEM_HL;

	instructions[0x03] = &CPU::INC_BC;
	instructions[0x13] = &CPU::INC_DE;
	instructions[0x23] = &CPU::INC_HL;
	instructions[0x33] = &CPU::INC_SP;

	instructions[0x3D] = &CPU::DEC_A;
	instructions[0x05] = &CPU::DEC_B;
	instructions[0x0D] = &CPU::DEC_C;
	instructions[0x15] = &CPU::DEC_D;
	instructions[0x1D] = &CPU::DEC_E;
	instructions[0x25] = &CPU::DEC_H;
	instructions[0x2D] = &CPU::DEC_L;
	instructions[0x35] = &CPU::DEC_MEM_HL;

	instructions[0x0B] = &CPU::DEC_BC;
	instructions[0x1B] = &CPU::DEC_DE;
	instructions[0x2B] = &CPU::DEC_HL;
	instructions[0x3B] = &CPU::DEC_SP;

	//Jumps
	instructions[0x20] = &CPU::JR_NZ;
	instructions[0x28] = &CPU::JR_Z;
	instructions[0x30] = &CPU::JR_NC;
	instructions[0x38] = &CPU::JR_C;
	instructions[0x18] = &CPU::JR;
	instructions[0xc3] = &CPU::JP_nn;

	//Stack
	instructions[0xCD] = &CPU::CALL_nn;
	instructions[0xC4] = &CPU::CALL_NZ_nn;
	instructions[0xCC] = &CPU::CALL_Z_nn; 
	instructions[0xD4] = &CPU::CALL_NC_nn;
	instructions[0xDC] = &CPU::CALL_C_nn; 
	instructions[0xC9] = &CPU::RET;
	instructions[0xC0] = &CPU::RET_NZ;
	instructions[0xC8] = &CPU::RET_Z;
	instructions[0xD0] = &CPU::RET_NC;
	instructions[0xD8] = &CPU::RET_C;
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

	//Rotates
	instructions[0x17] = &CPU::RLA;
	instructions[0x07] = &CPU::RLCA;
	instructions[0x1F] = &CPU::RRA;
	instructions[0x0F] = &CPU::RRCA;

	instructions_cb[0x07] = &CPU::RLC_A;
	instructions_cb[0x00] = &CPU::RLC_B;
	instructions_cb[0x01] = &CPU::RLC_C;
	instructions_cb[0x02] = &CPU::RLC_D;
	instructions_cb[0x03] = &CPU::RLC_E;
	instructions_cb[0x04] = &CPU::RLC_H;
	instructions_cb[0x05] = &CPU::RLC_L;
	instructions_cb[0x06] = &CPU::RLC_HL;

	instructions_cb[0x17] = &CPU::RL_A;
	instructions_cb[0x10] = &CPU::RL_B;
	instructions_cb[0x11] = &CPU::RL_C;
	instructions_cb[0x12] = &CPU::RL_D;
	instructions_cb[0x13] = &CPU::RL_E;
	instructions_cb[0x14] = &CPU::RL_H;
	instructions_cb[0x15] = &CPU::RL_L;
	instructions_cb[0x16] = &CPU::RL_HL;

	instructions_cb[0x0F] = &CPU::RRC_A;
	instructions_cb[0x08] = &CPU::RRC_B;
	instructions_cb[0x09] = &CPU::RRC_C;
	instructions_cb[0x0A] = &CPU::RRC_D;
	instructions_cb[0x0B] = &CPU::RRC_E;
	instructions_cb[0x0C] = &CPU::RRC_H;
	instructions_cb[0x0D] = &CPU::RRC_L;
	instructions_cb[0x0E] = &CPU::RRC_HL;

	instructions_cb[0x1F] = &CPU::RR_A;
	instructions_cb[0x18] = &CPU::RR_B;
	instructions_cb[0x19] = &CPU::RR_C;
	instructions_cb[0x1A] = &CPU::RR_D;
	instructions_cb[0x1B] = &CPU::RR_E;
	instructions_cb[0x1C] = &CPU::RR_H;
	instructions_cb[0x1D] = &CPU::RR_L;
	instructions_cb[0x1E] = &CPU::RR_HL;

	instructions_cb[0x27] = &CPU::SLA_A;
	instructions_cb[0x20] = &CPU::SLA_B;
	instructions_cb[0x21] = &CPU::SLA_C;
	instructions_cb[0x22] = &CPU::SLA_D;
	instructions_cb[0x23] = &CPU::SLA_E;
	instructions_cb[0x24] = &CPU::SLA_H;
	instructions_cb[0x25] = &CPU::SLA_L;
	instructions_cb[0x26] = &CPU::SLA_HL;

	instructions_cb[0x2F] = &CPU::SRA_A;
	instructions_cb[0x28] = &CPU::SRA_B;
	instructions_cb[0x29] = &CPU::SRA_C;
	instructions_cb[0x2A] = &CPU::SRA_D;
	instructions_cb[0x2B] = &CPU::SRA_E;
	instructions_cb[0x2C] = &CPU::SRA_H;
	instructions_cb[0x2D] = &CPU::SRA_L;
	instructions_cb[0x2E] = &CPU::SRA_HL;

	instructions_cb[0x3F] = &CPU::SRL_A;
	instructions_cb[0x38] = &CPU::SRL_B;
	instructions_cb[0x39] = &CPU::SRL_C;
	instructions_cb[0x3A] = &CPU::SRL_D;
	instructions_cb[0x3B] = &CPU::SRL_E;
	instructions_cb[0x3C] = &CPU::SRL_H;
	instructions_cb[0x3D] = &CPU::SRL_L;
	instructions_cb[0x3E] = &CPU::SRL_HL;

	instructions[0xf3] = &CPU::DI;
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
	if (this->PC.reg > 0xc000 && debug) {
		string hello;
		cin >> hello;
	}
	//cout << hex << "0x" << (int)this->PC.reg << ": ";
	this->PC.reg = this->PC.reg + 1;
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
				this->gpu.UpdateScreen();
			}
			else if((line > 144) && (line <= 153)) {
				//in V-Blank
			}
			else {
				DrawLine();
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

	BYTE ScrollX = this->memory.readByte(0xFF43);
	BYTE Scrolly = this->memory.readByte(0xFF42);

	BYTE yPixel = this->memory.readByte(0xFF44);
	BYTE yPixelRow = Scrolly + yPixel;
	WORD yTileRow = (yPixelRow/8) * 32;

	for (int xPixel = 0; xPixel < 160; xPixel++) {

		BYTE xPixelColumn = ScrollX + xPixel;
		WORD xTileColumn = xPixelColumn/8;

		WORD backgroundTileMap = 0x9800 + yTileRow + xTileColumn;

		BYTE tileNumber = this->memory.readByte(backgroundTileMap);
		
		BYTE row = yPixelRow % 8;
		row = row * 2; //each pixel row is represented by 2 bytes
		BYTE tileDataRow = this->memory.readByte(0x8000 + (tileNumber*16) + row);
		BYTE tileDataRow2 = this->memory.readByte(0x8000 + (tileNumber*16) + row + 1);
			
		int xBit = xPixelColumn % 8;
		xBit -= 7;
		xBit *= -1;

		BYTE colorValue = GetBit(tileDataRow2, xBit);
		colorValue = (colorValue << 1) | GetBit(tileDataRow, xBit);

		switch(colorValue){
			case 0: this->gpu.screen[xPixel][yPixel] = 0; break;
			case 1:
			case 2:
			case 3: this->gpu.screen[xPixel][yPixel] = 1; break;
		}
	}
}

bool CPU::CheckInput(){
	return this->gpu.CheckInput();
}

//instructions
int CPU::LD_A_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	//cout << hex << "LD A, " << "0x" << (int)immediate << endl;
	this->AF.hi = immediate;
	return 4;
}

int CPU::LD_B_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	//cout << hex << "LD B, " << "0x" << (int)immediate << endl;
	this->BC.hi = immediate;
	return 4;
} 

int CPU::LD_C_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	//cout << hex << "LD C, " << "0x" << (int)immediate << endl;
	this->BC.lo = immediate;
	return 4;
}

int CPU::LD_D_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	//cout << hex << "LD D, " << "0x" << (int)immediate << endl;
	this->DE.hi = immediate;
	return 4;
} 

int CPU::LD_E_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	//cout << hex << "LD E, " << "0x" << (int)immediate << endl;
	this->DE.lo = immediate;
	return 4;
}

int CPU::LD_H_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	//cout << hex << "LD H, " << "0x" << (int)immediate << endl;
	this->HL.hi = immediate;
	return 4;
} 

int CPU::LD_L_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	//cout << hex << "LD L, " << "0x" << (int)immediate << endl;
	this->HL.lo = immediate;
	return 4;
}

int CPU::LD_A_A() {
	//cout << hex << "LD A, A" << endl;
	return 4;
}

int CPU::LD_A_B() {
	this->AF.hi = this->BC.hi;
	//cout << hex << "LD A, B" << endl;
	return 4;
}

int CPU::LD_A_C() {
	this->AF.hi = this->BC.lo;
	//cout << hex << "LD A, C" << endl;
	return 4;
}

int CPU::LD_A_D() {
	this->AF.hi = this->DE.hi;
	//cout << hex << "LD A, D" << endl;
	return 4;
}

int CPU::LD_A_E() {
	this->AF.hi = this->DE.lo;
	//cout << hex << "LD A, E" << endl;
	return 4;
}

int CPU::LD_A_H() {
	this->AF.hi = this->HL.hi;
	//cout << hex << "LD A, H (" <<(int)this->HL.hi << ")" << endl;
	return 4;
}

int CPU::LD_A_L() {
	this->AF.hi = this->HL.lo;
	//cout << hex << "LD A, L (" << (int)this->HL.lo << ")" << endl;
	return 4;
}

int CPU::LD_A_BC() {
	this->AF.hi = this->memory.readByte(this->BC.reg);
	//cout << hex << "LD A, (BC)" << endl;
	return 4;
}

int CPU::LD_A_DE() {
	this->AF.hi = this->memory.readByte(this->DE.reg);
	//cout << hex << "LD A, (DE); A = " << (int)this->AF.hi << " DE = " << (int)this->DE.reg << endl;
	return 4;
}

int CPU::LD_A_HL() {
	this->AF.hi = this->memory.readByte(this->HL.reg);
	//cout << hex << "LD A, (HL)" << endl;
	return 4;
}

int CPU::LD_A_nn() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	this->AF.hi = this->memory.readByte(address);
	//cout << hex << "LD A, (0x" << (int)address << ")" << endl;
	return 4;
}

int CPU::LD_B_B() {
	this->BC.hi = this->BC.hi;
	return 4;
}

int CPU::LD_B_C() {
	this->BC.hi = this->BC.lo;
	return 4;
}

int CPU::LD_B_D() {
	this->BC.hi = this->DE.hi;
	return 4;
}

int CPU::LD_B_E() {
	this->BC.hi = this->DE.lo;
	return 4;
}

int CPU::LD_B_H() {
	this->BC.hi = this->HL.hi;
	return 4;
}

int CPU::LD_B_L() {
	this->BC.hi = this->HL.lo;
	return 4;
}

int CPU::LD_B_HL() {
	this->BC.hi = this->memory.readByte(this->HL.hi);
	return 8;
}

int CPU::LD_C_B() {
	this->BC.lo = this->BC.hi;
	return 4;
}

int CPU::LD_C_C() {
	this->BC.lo = this->BC.lo;
	return 4;
}

int CPU::LD_C_D() {
	this->BC.lo = this->DE.hi;
	return 4;
}

int CPU::LD_C_E() {
	this->BC.lo = this->DE.lo;
	return 4;
}

int CPU::LD_C_H() {
	this->BC.lo = this->HL.hi;
	return 4;
}

int CPU::LD_C_L() {
	this->BC.lo = this->HL.lo;
	return 4;
}

int CPU::LD_C_HL() {
	this->BC.lo = this->memory.readByte(this->HL.hi);
	return 8;
}

int CPU::LD_D_B() {
	this->DE.hi = this->BC.hi;
	return 4;
}

int CPU::LD_D_C() {
	this->DE.hi = this->BC.lo;
	return 4;
}

int CPU::LD_D_D() {
	this->DE.hi = this->DE.hi;
	return 4;
}

int CPU::LD_D_E() {
	this->DE.hi = this->DE.lo;
	return 4;
}

int CPU::LD_D_H() {
	this->DE.hi = this->HL.hi;
	return 4;
}

int CPU::LD_D_L() {
	this->DE.hi = this->HL.lo;
	return 4;
}

int CPU::LD_D_HL() {
	this->DE.hi = this->memory.readByte(this->HL.hi);
	return 8;
}


int CPU::LD_E_B() {
	this->DE.lo = this->BC.hi;
	return 4;
}

int CPU::LD_E_C() {
	this->DE.lo = this->BC.lo;
	return 4;
}

int CPU::LD_E_D() {
	this->DE.lo = this->DE.hi;
	return 4;
}

int CPU::LD_E_E() {
	this->DE.lo = this->DE.lo;
	return 4;
}

int CPU::LD_E_H() {
	this->DE.lo = this->HL.hi;
	return 4;
}

int CPU::LD_E_L() {
	this->DE.lo = this->HL.lo;
	return 4;
}

int CPU::LD_E_HL() {
	this->DE.lo = this->memory.readByte(this->HL.hi);
	return 8;
}

int CPU::LD_H_B() {
	this->HL.hi = this->BC.hi;
	return 4;
}

int CPU::LD_H_C() {
	this->HL.hi = this->BC.lo;
	return 4;
}

int CPU::LD_H_D() {
	this->HL.hi = this->DE.hi;
	return 4;
}

int CPU::LD_H_E() {
	this->HL.hi = this->DE.lo;
	return 4;
}

int CPU::LD_H_H() {
	this->HL.hi = this->HL.hi;
	return 4;
}

int CPU::LD_H_L() {
	this->HL.hi = this->HL.lo;
	return 4;
}

int CPU::LD_H_HL() {
	this->HL.hi = this->memory.readByte(this->HL.hi);
	return 8;
}

int CPU::LD_L_B() {
	this->HL.lo = this->BC.hi;
	return 4;
}

int CPU::LD_L_C() {
	this->HL.lo = this->BC.lo;
	return 4;
}

int CPU::LD_L_D() {
	this->HL.lo = this->DE.hi;
	return 4;
}

int CPU::LD_L_E() {
	this->HL.lo = this->DE.lo;
	return 4;
}

int CPU::LD_L_H() {
	this->HL.lo = this->HL.hi;
	return 4;
}

int CPU::LD_L_L() {
	this->HL.lo = this->HL.lo;
	return 4;
}

int CPU::LD_L_HL() {
	this->HL.lo = this->memory.readByte(this->HL.hi);
	return 8;
}

int CPU::LD_B_A() {
	this->BC.hi = this->AF.hi;
	//cout << hex << "LD B, A" << endl;
	return 4;
}

int CPU::LD_C_A() {
	this->BC.lo = this->AF.hi;
	//cout << hex << "LD C, A = " << (int)this->AF.hi << endl;
	return 4;
}

int CPU::LD_D_A() {
	this->DE.hi = this->AF.hi;
	//cout << hex << "LD D, A" << endl;
	return 4;
}

int CPU::LD_E_A() {
	this->DE.lo = this->AF.hi;
	//cout << hex << "LD E, A" << endl;
	return 4;
}

int CPU::LD_H_A() {
	this->HL.hi = this->AF.hi;
	//cout << hex << "LD H, A" << endl;
	return 4;
}

int CPU::LD_L_A() {
	this->HL.lo = this->AF.hi;
	//cout << hex << "LD L, A" << endl;
	return 4;
}

int CPU::LD_BC_A() {
	this->memory.writeByte(this->BC.reg, this->AF.hi);
	//cout << hex << "LD (BC), A" << endl;
	return 4;
}

int CPU::LD_DE_A() {
	this->memory.writeByte(this->DE.reg, this->AF.hi);
	//cout << hex << "LD (DE= "<< (int)this->DE.reg <<"), A" << endl;
	return 4;
}

int CPU::LD_nn_A() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	this->memory.writeByte(immediate, this->AF.hi);
	//cout << hex << "LD (0x" << (int)immediate << "), A (" << (int)this->AF.hi <<")" << endl;
	return 4;
}

int CPU::LD_HL_A() {
	this->memory.writeByte(this->HL.reg, this->AF.hi);
	//cout << hex << "LD (HL), A" << endl;
	return 8;
}

int CPU::LD_HL_B() {
	this->memory.writeByte(this->HL.reg, this->BC.hi);
	return 8;
}

int CPU::LD_HL_C() {
	this->memory.writeByte(this->HL.reg, this->BC.lo);
	return 8;
}

int CPU::LD_HL_D() {
	this->memory.writeByte(this->HL.reg, this->DE.hi);
	return 8;
}

int CPU::LD_HL_E() {
	this->memory.writeByte(this->HL.reg, this->DE.lo);
	return 8;
}

int CPU::LD_HL_H() {
	this->memory.writeByte(this->HL.reg, this->HL.hi);
	return 8;
}

int CPU::LD_HL_L() {
	this->memory.writeByte(this->HL.reg, this->HL.lo);
	return 8;
}

int CPU::LD_HL_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->memory.writeByte(this->HL.reg, value);
	return 12;
}


int CPU::LD_FF00_C_A(){
	WORD address = 0xFF00 + this->BC.lo;
	this->memory.writeByte(address, this->AF.hi);
	//cout << hex << "LD ($FF00 + C), A Address: " << (int)address << " C: " << (int)this->BC.lo << endl;
	return 4;
}

int CPU::LD_FF00_n_A(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	WORD address = 0xFF00 + immediate;
	this->memory.writeByte(address, this->AF.hi);
	//cout << hex << "LD ($FF00 + 0x" << (int)immediate << "), A (" << (int)this->AF.hi <<")" << endl;
	return 4;
}

int CPU::LDH_A_FF00_n() {
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	WORD address = 0xFF00 + immediate;
	this->AF.hi = this->memory.readByte(address);
	//cout << hex << "LD A, ($FF00 + 0x" << (int)immediate << ") A = " << (int)this->AF.hi << endl;
	return 4;
}

int CPU::LDD_HL_A(){
	this->memory.writeByte(this->HL.reg, this->AF.hi);
	this->HL.reg--;
	//cout << hex << "LDD (HL), A" << endl;
	return 4;
}

int CPU::LDI_HL_A(){
	this->memory.writeByte(this->HL.reg, this->AF.hi);
	//cout << hex << "HL = " << (int)this->HL.reg << endl;
	this->HL.reg++;
	//cout << hex << "LDI (HL), A = " << (int)this->AF.hi << endl;
	return 4;
}

int CPU::LDI_A_HL() {
	this->AF.hi = this->memory.readByte(this->HL.reg);
	this->HL.reg++;
	//cout << hex << "LDI A ("<<(int)this->AF.hi<< "), (HL) = " << (int)this->HL.reg << endl;
	return 8;
}

int CPU::LD_SP_HL() {
	this->SP.reg = this->HL.reg;
	return 8;
}

int CPU::LD_BC_nn(){
	this->BC.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	//cout << hex << "LD BC, " << "0x" << (int)this->BC.reg << endl;
	return 4;
}

int CPU::LD_DE_nn(){
	this->DE.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	//cout << hex << "LD DE, " << "0x" << (int)this->DE.reg << endl;
	return 4;
}

int CPU::LD_HL_nn(){
	this->HL.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	//cout << hex << "LD HL, " << "0x" << (int)this->HL.reg << endl;
}

int CPU::LD_SP_nn(){
	this->SP.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	//cout << hex << "LD SP, " << "0x" << (int)this->SP.reg << endl;
	return 12;
}

int CPU::LD_nn_SP() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	this->memory.writeByte(address, this->SP.lo);
	this->memory.writeByte(address+1, this->SP.hi);
	return 20;
}

//Jump Instructions
int CPU::JR_NZ() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	//cout << hex << "JR NZ, " << (int)offset << endl;
	if (this->flags.z == 0) {
		this->PC.reg += offset;
		//cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
	return 4;
}

int CPU::JR_Z() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	//cout << hex << "JR Z, " << (int)offset << endl;
	if (this->flags.z == 1) {
		this->PC.reg += offset;
		//cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
	return 4;
}

int CPU::JR_NC() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	//cout << hex << "JR NC, " << (int)offset << endl;
	if (this->flags.c == 0) {
		this->PC.reg += offset;
	//	cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
	return 4;
}

int CPU::JR_C() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	//cout << hex << "JR C, " << (int)offset << endl;
	if (this->flags.c == 1) {
		this->PC.reg += offset;
	//	cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
	return 4;
}

int CPU::JR() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	//cout << hex << "JR 0x" << (int)offset << endl;
	this->PC.reg += offset;
	//cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	return 8;
}

int CPU::JP_nn() {
	WORD address = this->memory.readWord(this->PC.reg);
	//cout << hex << "Jump to: 0x" << address << endl;
	this->PC.reg = address;
	return 12;
}

void CPU::PushWord(WORD value) {
	BYTE lo = value & 0x00FF;
	BYTE hi = value >> 8;
	PushByte(lo);
	PushByte(hi);
}

WORD CPU::PopWord() {
	WORD retVal = PopByte();
	retVal = retVal << 8;
	retVal = retVal | PopByte();
	//cout << hex << "Pop value 0x" << (int)retVal << endl;
	return retVal;
}

void CPU::PushByte(BYTE value) {
	this->SP.reg--;
	this->memory.writeByte(this->SP.reg, value);
	//cout << hex << "PUSH SP: 0x" << (int)this->SP.reg << " value:" << (int)value << endl;
}

BYTE CPU::PopByte() {
	//cout << hex << "sp 0x" << (int)this->SP.reg << endl;
	BYTE retVal = this->memory.readByte(this->SP.reg);
	//cout << hex << "POP SP: 0x" << (int)this->SP.reg << endl;
	this->SP.reg++; 
	return retVal;
}

int CPU::CALL_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	PushWord(this->PC.reg);
	this->PC.reg = immediate;
	//cout << hex << "CALL 0x" << (int)immediate << endl;
	return 12;
}

int CPU::CALL_NZ_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg++;
	if (this->flags.z == 0) {
		PushWord(this->PC.reg);
		this->PC.reg = immediate;
	}
	return 12;
}

int CPU::CALL_Z_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg++;
	if (this->flags.z == 1) {
		PushWord(this->PC.reg);
		this->PC.reg = immediate;
	}
	return 12;
}

int CPU::CALL_NC_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg++;
	if (this->flags.c == 0) {
		PushWord(this->PC.reg);
		this->PC.reg = immediate;
	}
	return 12;
}

int CPU::CALL_C_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg++;
	if (this->flags.c == 1) {
		PushWord(this->PC.reg);
		this->PC.reg = immediate;
	}
	return 12;
}


int CPU::RET() {
	this->PC.reg = PopWord();
	return 8;
}

int CPU::RET_NZ() {
	if (this->flags.z == 0) {
		this->PC.reg = PopWord();
	}
	return 8;
}

int CPU::RET_Z() {
	if (this->flags.z == 1) {
		this->PC.reg = PopWord();
	}
	return 8;
}

int CPU::RET_NC() {
	if (this->flags.c == 0) {
		this->PC.reg = PopWord();
	}
	return 8;
}

int CPU::RET_C() {
	if (this->flags.c == 1) {
		this->PC.reg = PopWord();
	}
	return 8;
}

int CPU::PUSH_AF() {
	PushWord(this->AF.reg);
//	cout << hex << "PUSH AF" << endl;
	return 4;
}

int CPU::PUSH_BC() {
	PushWord(this->BC.reg);
	//cout << hex << "PUSH BC: " << (int)this->BC.reg << endl;
	return 4;
}

int CPU::PUSH_DE() {
	PushWord(this->DE.reg);
	//cout << hex << "PUSH DE" << endl;
	return 4;
}

int CPU::PUSH_HL() {
	PushWord(this->HL.reg);
	//cout << hex << "PUSH HL" << endl;
	return 4;
}

int CPU::POP_AF() {
	this->AF.reg = PopWord();
	//cout << hex << "POP AF" << endl;
	return 4;
}

int CPU::POP_BC() {
	this->BC.reg = PopWord();
	//cout << hex << "POP BC: " << (int)this->BC.reg << endl;
	return 4;
}

int CPU::POP_DE() {
	this->DE.reg = PopWord();
	//cout << hex << "POP DE" << endl;
	return 4;
}

int CPU::POP_HL() {
	this->HL.reg = PopWord();
	//cout << hex << "POP HL" << endl;
	return 4;
}

BYTE CPU::Add(BYTE operand1, BYTE operand2, bool addCarryFlag) {
	BYTE carry = (addCarryFlag) ? this->flags.c : 0;
	bool setHalfCarry = ((operand1 & 0x0F) + ((operand2 + carry) & 0x0F) > 0x0F);
	BYTE sum = operand1 + operand2 + carry;

	if (sum == 0) {
		this->flags.z = 1;
	}
	else {
		this->flags.z = 0;
	}

	this->flags.n = 0;

	if (setHalfCarry) {
		this->flags.h = 1;
	}
	else {
		this->flags.h = 0;
	}

	if (sum < operand1) {
		this->flags.c = 1;
	}
	else {
		this->flags.c = 0;
	}
	
	return sum;
}

int CPU::ADD_A() {
	this->AF.hi = Add(this->AF.hi, this->AF.hi);
	return 4;
}

int CPU::ADD_B() {
	this->AF.hi = Add(this->AF.hi, this->BC.hi);
	return 4;
}

int CPU::ADD_C() {
	this->AF.hi = Add(this->AF.hi, this->BC.lo);
	return 4;
}

int CPU::ADD_D() {
	this->AF.hi = Add(this->AF.hi, this->DE.hi);
	return 4;
}

int CPU::ADD_E() {
	this->AF.hi = Add(this->AF.hi, this->DE.lo);
	return 4;
}

int CPU::ADD_H() {
	this->AF.hi = Add(this->AF.hi, this->HL.hi);
	return 4;
}

int CPU::ADD_L() {
	this->AF.hi = Add(this->AF.hi, this->HL.lo);
	return 4;
}

int CPU::ADD_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	this->AF.hi = Add(this->AF.hi, value);
	return 8;
}

int CPU::ADD_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->AF.hi = Add(this->AF.hi, value);
	return 8;
}

int CPU::ADC_A() {
	this->AF.hi = Add(this->AF.hi, this->AF.hi, true);
	return 4;
}

int CPU::ADC_B() {
	this->AF.hi = Add(this->AF.hi, this->BC.hi, true);
	return 4;
}

int CPU::ADC_C() {
	this->AF.hi = Add(this->AF.hi, this->BC.lo, true);
	return 4;
}

int CPU::ADC_D() {
	this->AF.hi = Add(this->AF.hi, this->DE.hi, true);
	return 4;
}

int CPU::ADC_E() {
	this->AF.hi = Add(this->AF.hi, this->DE.lo, true);
	return 4;
}

int CPU::ADC_H() {
	this->AF.hi = Add(this->AF.hi, this->HL.hi, true);
	return 4;
}

int CPU::ADC_L() {
	this->AF.hi = Add(this->AF.hi, this->HL.lo, true);
	return 4;
}

int CPU::ADC_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	this->AF.hi = Add(this->AF.hi, value, true);
	return 8;
}

int CPU::ADC_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->AF.hi = Add(this->AF.hi, value, true);
	return 8;	
}

//Math instructions
BYTE CPU::Subtract(BYTE from, BYTE sub) {
	bool setHalfCarry = ((int)(from & 0x0F) - (int)(sub & 0x0F) < 0x00);
	this->flags.c = (sub > from);
	from = from - sub;

	if (from == 0) {
		this->flags.z = 1;
	}
	else {
		this->flags.z = 0;
	}

	this->flags.n = 1;

	if (setHalfCarry) {
		this->flags.h = 0;
	}
	else {
		this->flags.h = 1;
	}
	

	return from;
}

int CPU::SUB_A() {
	this->AF.hi = Subtract(this->AF.hi, this->AF.hi);
	return 4;
}

int CPU::SUB_B() {
	this->AF.hi = Subtract(this->AF.hi, this->BC.hi);
	//cout << "B: " << (int)this->BC.hi << endl;
	return 4;
}

int CPU::SUB_C() {
	this->AF.hi = Subtract(this->AF.hi, this->BC.lo);
	return 4;
}

int CPU::SUB_D() {
	this->AF.hi = Subtract(this->AF.hi, this->DE.hi);
	return 4;
}

int CPU::SUB_E() {
	this->AF.hi = Subtract(this->AF.hi, this->DE.lo);
	return 4;
}

int CPU::SUB_H() {
	this->AF.hi = Subtract(this->AF.hi, this->HL.hi);
	return 4;
}

int CPU::SUB_L() {
	this->AF.hi = Subtract(this->AF.hi, this->HL.lo);
	return 4;
}

int CPU::SUB_HL() {
	this->AF.hi = Subtract(this->AF.hi, this->memory.readByte(this->HL.hi));
	return 8;
}

int CPU::SUB_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->AF.hi = Subtract(this->AF.hi, value);
	return 8;
}


BYTE CPU::XOR(BYTE operand1, BYTE operand2) {
	BYTE retVal = operand1 ^ operand2;
	if (retVal == 0) {
		this->flags.z = 1;
	}
	else {
		this->flags.z = 0;
	}

	this->flags.n = 0;
	this->flags.c = 0;
	this->flags.h = 0;

	return retVal;
}

int CPU::XOR_A() {
	this->AF.hi = XOR(this->AF.hi, this->AF.hi);
	//cout << hex << "XOR A" << endl;
	return 4;
}

int CPU::XOR_B() {
	this->AF.hi = XOR(this->AF.hi, this->BC.hi);
	return 4;
}

int CPU::XOR_C() {
	this->AF.hi = XOR(this->AF.hi, this->BC.lo);
	return 4;
}

int CPU::XOR_D() {
	this->AF.hi = XOR(this->AF.hi, this->DE.hi);
	return 4;
}

int CPU::XOR_E() {
	this->AF.hi = XOR(this->AF.hi, this->DE.lo);
	return 4;
}

int CPU::XOR_H() {
	this->AF.hi = XOR(this->AF.hi, this->HL.hi);
	return 4;
}

int CPU::XOR_L() {
	this->AF.hi = XOR(this->AF.hi, this->HL.lo);
	return 4;
}

int CPU::XOR_HL() {
	this->AF.hi = XOR(this->AF.hi, this->memory.readByte(this->HL.reg));
	return 8;	
}

int CPU::XOR_n() {
	this->AF.hi = XOR(this->AF.hi, this->memory.readByte(this->PC.reg));
	this->PC.reg++;
	return 8;
}

BYTE CPU::AND(BYTE operand1, BYTE operand2) {
	BYTE retVal = operand1 & operand2;
	if (retVal == 0) {
		this->flags.z = 1;
	}
	else {
		this->flags.z = 0;
	}

	this->flags.n = 0;
	this->flags.c = 0;
	this->flags.h = 1;

	return retVal;
}

int CPU::AND_A() {
	AND(this->AF.hi, this->AF.hi);
	return 4;
}

int CPU::AND_B() {
	this->AF.hi = AND(this->AF.hi, this->BC.hi);
	return 4;
}

int CPU::AND_C() {
	this->AF.hi = AND(this->AF.hi, this->BC.lo);
	return 4;
}

int CPU::AND_D() {
	this->AF.hi = AND(this->AF.hi, this->DE.hi);
	return 4;
}

int CPU::AND_E() {
	this->AF.hi = AND(this->AF.hi, this->DE.lo);
	return 4;
}

int CPU::AND_H() {
	this->AF.hi = AND(this->AF.hi, this->HL.hi);
	return 4;
}

int CPU::AND_l() {
	this->AF.hi = AND(this->AF.hi, this->HL.lo);
	return 4;
}

int CPU::AND_HL() {
	this->AF.hi = AND(this->AF.hi, this->memory.readByte(this->HL.reg));
	return 8;
}

int CPU::AND_n() {
	this->AF.hi = AND(this->AF.hi, this->memory.readByte(this->PC.reg));
	this->PC.reg++;
	return 8;
}

BYTE CPU::OR(BYTE operand1, BYTE operand2) {
	BYTE retVal = operand1 | operand2;
	if (retVal == 0) {
		this->flags.z = 1;
	}
	else {
		this->flags.z = 0;
	}

	this->flags.n = 0;
	this->flags.c = 0;
	this->flags.h = 0;

	return retVal;
}

int CPU::OR_A() {
	OR(this->AF.hi, this->AF.hi);
	return 4;
}

int CPU::OR_B() {
	this->AF.hi = OR(this->AF.hi, this->BC.hi);
	return 4;
}

int CPU::OR_C() {
	//cout << hex << "OR C; A = " << (int)this->AF.hi << " C = " << (int)this->BC.lo <<endl;
	this->AF.hi = OR(this->AF.hi, this->BC.lo);
	//cout << hex << "A = " << (int)this->AF.hi << endl;
	return 4;
}

int CPU::OR_D() {
	this->AF.hi = OR(this->AF.hi, this->DE.hi);
	return 4;
}

int CPU::OR_E() {
	this->AF.hi = OR(this->AF.hi, this->DE.lo);
	return 4;
}

int CPU::OR_H() {
	this->AF.hi = OR(this->AF.hi, this->HL.hi);
	return 4;
}

int CPU::OR_L() {
	this->AF.hi = OR(this->AF.hi, this->HL.lo);
	return 4;
}

int CPU::OR_HL() {
	this->AF.hi = OR(this->AF.hi, this->memory.readByte(this->HL.reg));
	return 8;
}

int CPU::OR_n() {
	this->AF.hi = OR(this->AF.hi, this->memory.readByte(this->PC.reg));
	this->PC.reg++;
	return 8;
}

void CPU::Compare(BYTE value) {
	bool setHalfCarry = ((int)(this->AF.hi & 0x0F) - (int)(value & 0x0F) < 0x00);
	BYTE diff = this->AF.hi - value;

	if (diff == 0) {
		this->flags.z = 1;
	}
	else {
		this->flags.z = 0;
	}

	this->flags.n = 1;

	if (setHalfCarry){
		this->flags.h = 1;
	}
	if (this->AF.hi < value) {
		this->flags.c = 1;
	}
}

int CPU::CP_A() {
	Compare(this->AF.hi);
	//cout << hex << "CP A"<< endl;
	return 4;
}

int CPU::CP_B() {
	Compare(this->BC.hi);
	//cout << hex << "CP B"<< endl;
	return 4;
}

int CPU::CP_C() {
	Compare(this->BC.lo);
	//cout << hex << "CP C"<< endl;
	return 4;
}

int CPU::CP_D() {
	Compare(this->DE.hi);
	//cout << hex << "CP D"<< endl;
	return 4;
}

int CPU::CP_E() {
	Compare(this->DE.lo);
	//cout << hex << "CP E"<< endl;
	return 4;
}

int CPU::CP_H() {
	Compare(this->HL.hi);
	//cout << hex << "CP H"<< endl;
	return 4;
}

int CPU::CP_L() {
	Compare(this->HL.lo);
	//cout << hex << "CP L"<< endl;
	return 4;
}

int CPU::CP_MEM_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	Compare(value);
	//cout << hex << "CP (HL)"<< endl;
	return 4;
}

int CPU::CP_n() {
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Compare(immediate);
	//cout << hex << "CP 0x" << (int)immediate << " A = " << (int)this->AF.hi << endl;
	return 4;
}


BYTE CPU::RegInc(BYTE value) {
	bool setHalfCarry = ((value & 0x0F) + (1 & 0x0F) > 0x0F);
	value++;

	if (value == 0) {
		this->flags.z = 1;
	}
	else {
		this->flags.z = 0;
	}

	this->flags.n = 0;
	if (setHalfCarry){
		this->flags.h = 1;
	}
	else {
		this->flags.h = 0;
	}

	return value;
}

int CPU::INC_A() {
	this->AF.hi = RegInc(this->AF.hi);
	//cout << hex << "INC A" << endl;
	return 4;
}

int CPU::INC_B() {
	this->BC.hi = RegInc(this->BC.hi);
	//cout << hex << "INC B" << endl;
	return 4;
}

int CPU::INC_C() {
	this->BC.lo = RegInc(this->BC.lo);
	//cout << hex << "INC C = " << (int)this->BC.lo << endl;
	return 4;
}

int CPU::INC_D() {
	this->DE.hi = RegInc(this->DE.hi);
	//cout << hex << "INC D" << endl;
	return 4;
}

int CPU::INC_E() {
	this->DE.lo = RegInc(this->DE.lo);
	//cout << hex << "INC E: " << (int)this->DE.lo << endl;
	return 4;
}

int CPU::INC_H() {
	this->HL.hi = RegInc(this->HL.hi);
	//cout << hex << "INC H" << endl;
	return 4;
}

int CPU::INC_L() {
	this->HL.lo = RegInc(this->HL.lo);
	//cout << hex << "INC L" << endl;
	return 4;
}

int CPU::INC_MEM_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = RegInc(value);
	this->memory.writeByte(this->HL.reg, value);
//	cout << hex << "INC (HL)" << endl;
	return 4;
}

int CPU::INC_BC() {
	this->BC.reg++;
	//cout << hex << "INC BC = " << (int)this->BC.reg << endl;
	return 4;
}

int CPU::INC_DE() {
	this->DE.reg++;
//	cout << hex << "INC DE" << endl;
	return 4;
}

int CPU::INC_HL() {
	this->HL.reg++;
//	cout << hex << "INC HL" << endl;
	return 4;
}

int CPU::INC_SP() {
	this->SP.reg++;
	//cout << hex << "INC SP" << endl;
	return 4;
}


BYTE CPU::RegDec(BYTE value) {
	bool setHalfCarry = ((int)(value & 0x0F) - (int)(1 & 0x0F) < 0x00);
	value--;

	if (value == 0) {
		this->flags.z = 1;
	}
	else {
		this->flags.z = 0;
	}

	this->flags.n = 1;
	if (setHalfCarry){
		this->flags.h = 1;
	}
	return value;
}

int CPU::DEC_A() {
	this->AF.hi = RegDec(this->AF.hi);
	//cout << hex << "DEC A" << endl;
	return 4;
}

int CPU::DEC_B() {
	this->BC.hi = RegDec(this->BC.hi);
	//cout << hex << "DEC B: " << (int)this->BC.hi << endl;
	return 4;
}

int CPU::DEC_C() {
	this->BC.lo = RegDec(this->BC.lo);
	return 4;
}

int CPU::DEC_D() {
	this->DE.hi = RegDec(this->DE.hi);
	//cout << hex << "DEC D: " << (int)this->DE.hi << endl;
	return 4;
}

int CPU::DEC_E() {
	this->DE.lo = RegDec(this->DE.lo);
	//cout << hex << "DEC E" << endl;
	return 4;
}

int CPU::DEC_H() {
	this->HL.hi = RegDec(this->HL.hi);
	//cout << hex << "DEC H" << endl;
	return 4;
}

int CPU::DEC_L() {
	this->HL.lo = RegDec(this->HL.lo);
	//cout << hex << "DEC L" << endl;
	return 4;
}

int CPU::DEC_MEM_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = RegDec(value);
	this->memory.writeByte(this->HL.reg, value);
	//cout << hex << "DEC (HL)" << endl;
	return 4;
}

int CPU::DEC_BC() {
	this->BC.reg--;
	//cout << hex << "DEC BC" << endl;
	return 4;
}

int CPU::DEC_DE() {
	this->DE.reg--;
	//cout << hex << "DEC DE" << endl;
	return 4;
}

int CPU::DEC_HL() {
	this->HL.reg--;
	//cout << hex << "DEC HL" << endl;
	return 4;
}

int CPU::DEC_SP() {
	this->SP.reg--;
	//cout << hex << "DEC SP" << endl;
	return 4;
}



//Bit instructions
void CPU::TestBit(BYTE byte, BYTE mask) {
	byte = byte & mask;
//	cout << hex << (int)byte << endl;
	if (byte != 0) {
		this->flags.z = 0;
	}
	else {
		this->flags.z = 1;
	}

	this->flags.n = 0;
	this->flags.h = 1;
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

int CPU::BIT_0_A() {
	TestBit(this->AF.hi, BIT0);
//	cout << hex << "Bit 0, A" << endl;
	return 4;
} 

int CPU::BIT_1_A() {
	TestBit(this->AF.hi, BIT1);
//	cout << hex << "Bit 1, A" << endl;
	return 4;
}

int CPU::BIT_2_A() {
	TestBit(this->AF.hi, BIT2);
//	cout << hex << "Bit 2, A" << endl;
	return 4;
}

int CPU::BIT_3_A() {
	TestBit(this->AF.hi, BIT3);
//	cout << hex << "Bit 3, A" << endl;
	return 4;
}

int CPU::BIT_4_A() {
	TestBit(this->AF.hi, BIT4);
//	cout << hex << "Bit 4, A" << endl;
	return 4;
}

int CPU::BIT_5_A() {
	TestBit(this->AF.hi, BIT5);
//	cout << hex << "Bit 5, A" << endl;
	return 4;
}

int CPU::BIT_6_A() {
	TestBit(this->AF.hi, BIT6);
//	cout << hex << "Bit 6, A" << endl;
	return 4;
}

int CPU::BIT_7_A() {
	TestBit(this->AF.hi, BIT7);
//	cout << hex << "Bit 7, A" << endl;
	return 4;
}

int CPU::BIT_0_B() {
	TestBit(this->BC.hi, BIT0);
//	cout << hex << "Bit 0, B" << endl;
	return 4;
}

int CPU::BIT_1_B() {
	TestBit(this->BC.hi, BIT1);
//	cout << hex << "Bit 1, B" << endl;
	return 4;
}

int CPU::BIT_2_B() {
	TestBit(this->BC.hi, BIT2);
//	cout << hex << "Bit 2, B" << endl;
	return 4;
}

int CPU::BIT_3_B() {
	TestBit(this->BC.hi, BIT3);
//	cout << hex << "Bit 3, B" << endl;
	return 4;
}

int CPU::BIT_4_B() {
	TestBit(this->BC.hi, BIT4);
//	cout << hex << "Bit 4, B" << endl;
	return 4;
}

int CPU::BIT_5_B() {
	TestBit(this->BC.hi, BIT5);
//	cout << hex << "Bit 5, B" << endl;
	return 4;
}

int CPU::BIT_6_B() {
	TestBit(this->BC.hi, BIT6);
//	cout << hex << "Bit 6, B" << endl;
	return 4;
}

int CPU::BIT_7_B() {
	TestBit(this->BC.hi, BIT7);
//	cout << hex << "Bit 7, B" << endl;
	return 4;
}

int CPU::BIT_0_C() {
	TestBit(this->BC.lo, BIT0);
//	cout << hex << "Bit 0, C" << endl;
	return 4;
}

int CPU::BIT_1_C() {
	TestBit(this->BC.lo, BIT1);
//	cout << hex << "Bit 1, C" << endl;
	return 4;
}

int CPU::BIT_2_C() {
	TestBit(this->BC.lo, BIT2);
//	cout << hex << "Bit 2, C" << endl;
	return 4;
}

int CPU::BIT_3_C() {
	TestBit(this->BC.lo, BIT3);
//	cout << hex << "Bit 3, C" << endl;
	return 4;
}

int CPU::BIT_4_C() {
	TestBit(this->BC.lo, BIT4);
//	cout << hex << "Bit 4, C" << endl;
	return 4;
}

int CPU::BIT_5_C() {
	TestBit(this->BC.lo, BIT5);
//	cout << hex << "Bit 5, C" << endl;
	return 4;
}

int CPU::BIT_6_C() {
	TestBit(this->BC.lo, BIT6);
//	cout << hex << "Bit 6, C" << endl;
	return 4;
}

int CPU::BIT_7_C() {
	TestBit(this->BC.lo, BIT7);
//	cout << hex << "Bit 7, C" << endl;
	return 4;
}

int CPU::BIT_0_D() {
	TestBit(this->DE.hi, BIT0);
//	cout << hex << "Bit 0, D" << endl;
	return 4;
}

int CPU::BIT_1_D() {
	TestBit(this->DE.hi, BIT1);
//	cout << hex << "Bit 1, D" << endl;
	return 4;
}

int CPU::BIT_2_D() {
	TestBit(this->DE.hi, BIT2);
//	cout << hex << "Bit 2, D" << endl;
	return 4;
}

int CPU::BIT_3_D() {
	TestBit(this->DE.hi, BIT3);
//	cout << hex << "Bit 3, D" << endl;
	return 4;
}

int CPU::BIT_4_D() {
	TestBit(this->DE.hi, BIT4);
//	cout << hex << "Bit 4, D" << endl;
	return 4;
}

int CPU::BIT_5_D() {
	TestBit(this->DE.hi, BIT5);
//	cout << hex << "Bit 5, D" << endl;
	return 4;
}

int CPU::BIT_6_D() {
	TestBit(this->DE.hi, BIT6);
//	cout << hex << "Bit 6, D" << endl;
	return 4;
}

int CPU::BIT_7_D() {
	TestBit(this->DE.hi, BIT7);
//	cout << hex << "Bit 7, D" << endl;
	return 4;
}
 
int CPU::BIT_0_E() {
	TestBit(this->DE.lo, BIT0);
//	cout << hex << "Bit 0, E" << endl;
	return 4;
}

int CPU::BIT_1_E() {
	TestBit(this->DE.lo, BIT1);
//	cout << hex << "Bit 1, E" << endl;
	return 4;
}

int CPU::BIT_2_E() {
	TestBit(this->DE.lo, BIT2);
//	cout << hex << "Bit 2, E" << endl;
	return 4;
}

int CPU::BIT_3_E() {
	TestBit(this->DE.lo, BIT3);
//	cout << hex << "Bit 3, E" << endl;
	return 4;
}

int CPU::BIT_4_E() {
	TestBit(this->DE.lo, BIT4);
//	cout << hex << "Bit 4, E" << endl;
	return 4;
}

int CPU::BIT_5_E() {
	TestBit(this->DE.lo, BIT5);
//	cout << hex << "Bit 5, E" << endl;
	return 4;
}

int CPU::BIT_6_E() {
	TestBit(this->DE.lo, BIT6);
//	cout << hex << "Bit 6, E" << endl;
	return 4;
}

int CPU::BIT_7_E() {
	TestBit(this->DE.lo, BIT7);
//	cout << hex << "Bit 7, E" << endl;
	return 4;
}
 
int CPU::BIT_0_H() {
	TestBit(this->HL.hi, BIT0);
//	cout << hex << "Bit 0, H" << endl;
	return 4;
}

int CPU::BIT_1_H() {
	TestBit(this->HL.hi, BIT1);
//	cout << hex << "Bit 1, H" << endl;
	return 4;
}

int CPU::BIT_2_H() {
	TestBit(this->HL.hi, BIT2);
//	cout << hex << "Bit 2, H" << endl;
	return 4;
}

int CPU::BIT_3_H() {
	TestBit(this->HL.hi, BIT3);
//	cout << hex << "Bit 3, H" << endl;
	return 4;
}

int CPU::BIT_4_H() {
	TestBit(this->HL.hi, BIT4);
//	cout << hex << "Bit 4, H" << endl;
	return 4;
}

int CPU::BIT_5_H() {
	TestBit(this->HL.hi, BIT5);
//	cout << hex << "Bit 5, H" << endl;
	return 4;
}

int CPU::BIT_6_H() {
	TestBit(this->HL.hi, BIT6);
//	cout << hex << "Bit 6, H" << endl;
	return 4;
}

int CPU::BIT_7_H() {
	TestBit(this->HL.hi, BIT7);
//	cout << hex << "BIT 7, H" << endl;
	return 4;
}
 
int CPU::BIT_0_L() {
	TestBit(this->HL.lo, BIT0);
//	cout << hex << "Bit 0, L" << endl;
	return 4;
}

int CPU::BIT_1_L() {
	TestBit(this->HL.lo, BIT1);
//	cout << hex << "Bit 1, L" << endl;
	return 4;
}

int CPU::BIT_2_L() {
	TestBit(this->HL.lo, BIT2);
//	cout << hex << "Bit 2, L" << endl;
	return 4;
}

int CPU::BIT_3_L() {
	TestBit(this->HL.lo, BIT3);
//	cout << hex << "Bit 3, L" << endl;
	return 4;
}

int CPU::BIT_4_L() {
	TestBit(this->HL.lo, BIT4);
//	cout << hex << "Bit 4, L" << endl;
	return 4;
}

int CPU::BIT_5_L() {
	TestBit(this->HL.lo, BIT5);
//	cout << hex << "Bit 5, L" << endl;
	return 4;
}

int CPU::BIT_6_L() {
	TestBit(this->HL.lo, BIT6);
//	cout << hex << "Bit 6, L" << endl;
	return 4;
}

int CPU::BIT_7_L() {
	TestBit(this->HL.lo, BIT7);
//	cout << hex << "Bit 7, L" << endl;
	return 4;
}

int CPU::BIT_0_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT0);
//	cout << hex << "Bit 0, (HL)" << endl;
	return 4;
}
int CPU::BIT_1_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT1);
//	cout << hex << "Bit 1, (HL)" << endl;
	return 4;
}
int CPU::BIT_2_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT2);
//	cout << hex << "Bit 2, (HL)" << endl;
	return 4;
}
int CPU::BIT_3_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT3);
//	cout << hex << "Bit 3, (HL)" << endl;
	return 4;
}
int CPU::BIT_4_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT4);
//	cout << hex << "Bit 4, (HL)" << endl;
	return 4;
}
int CPU::BIT_5_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT5);
//	cout << hex << "Bit 5, (HL)" << endl;
	return 4;
}
int CPU::BIT_6_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT6);
//	cout << hex << "Bit 6, (HL)" << endl;
	return 4;
}
int CPU::BIT_7_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT7);
//	cout << hex << "Bit 7, (HL)" << endl;
	return 4;
}

BYTE CPU::Rotate(BYTE value, Direction direction, bool fromC) {
	if (direction == Direction::right) {
		BYTE carry = value & BIT0;
		value = value >> 1;
		BYTE sevenBit = (fromC) ? this->flags.c : carry;
		value = value | (sevenBit << 7);
		this->flags.c = carry;
	}
	else {
		BYTE carry = (value & BIT7) >> 7;
		value = value << 1;
		BYTE zeroBit = (fromC) ? this->flags.c : carry; 
		value = value | this->flags.c;
		this->flags.c = carry;
	}

	if (value == 0) {
		this->flags.z = 1;
	}
	else {
		this->flags.z = 0;
	}

	this->flags.n = 0;
	this->flags.h = 0;

	return value;
}

int CPU::RLC_A() {
	this->AF.hi = Rotate(this->AF.hi, Direction::left, false);
	return 8;
}

int CPU::RLC_B() {
	this->BC.hi = Rotate(this->BC.hi, Direction::left, false);
	return 8;
}

int CPU::RLC_C() {
	this->BC.lo = Rotate(this->BC.lo, Direction::left, false);
	return 8;
}

int CPU::RLC_D() {
	this->DE.hi = Rotate(this->DE.hi, Direction::left, false);
	return 8;
}

int CPU::RLC_E() {
	this->DE.lo = Rotate(this->DE.lo, Direction::left, false);
	return 8;
}

int CPU::RLC_H() {
	this->HL.hi = Rotate(this->HL.hi, Direction::left, false);
	return 8;
}

int CPU::RLC_L() {
	this->HL.lo = Rotate(this->HL.lo, Direction::left, false);
	return 8;
}

int CPU::RLC_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Rotate(value, Direction::left, false);
	this->memory.writeByte(this->HL.reg, value);
	return 16;
}

int CPU::RLA() {
	this->AF.hi = Rotate(this->AF.hi, Direction::left);
	return 8;
}

int CPU::RLCA() {
	this->AF.hi = Rotate(this->AF.hi, Direction::left, false);
	return 8;
}

int CPU::RRA() {
	this->AF.hi = Rotate(this->AF.hi, Direction::right);
	return 4;
}

int CPU::RRCA() {
	this->AF.hi = Rotate(this->AF.hi, Direction::right, false);
	return 4;
}

int CPU::RL_A() {
	this->AF.hi = Rotate(this->AF.hi, Direction::left);
//	cout << hex << "RL A" << endl;
	return 8;
}

int CPU::RL_B() {
	this->BC.hi = Rotate(this->BC.hi, Direction::left);
//	cout << hex << "RL B" << endl;
	return 8;
}

int CPU::RL_C() {
	this->BC.lo = Rotate(this->BC.lo, Direction::left);
	//cout << hex << "RL C" << endl;
	return 8;
}

int CPU::RL_D() {
	this->DE.hi = Rotate(this->DE.hi, Direction::left);
//	cout << hex << "RL D" << endl;
	return 8;
}

int CPU::RL_E() {
	this->DE.lo = Rotate(this->DE.lo, Direction::left);
//	cout << hex << "RL E" << endl;
	return 8;
}

int CPU::RL_H() {
	this->HL.hi = Rotate(this->HL.hi, Direction::left);
//	cout << hex << "RL H" << endl;
	return 8;
}

int CPU::RL_L() {
	this->HL.lo = Rotate(this->HL.lo, Direction::left);
//	cout << hex << "RL L" << endl;
	return 8;
}

int CPU::RL_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Rotate(value, Direction::left);
	this->memory.writeByte(this->HL.reg, value);
//	cout << hex << "RL (HL)" << endl;
	return 16;
}

int CPU::RRC_A() {
	this->AF.hi = Rotate(this->AF.hi, Direction::right, false);
	return 8;
}

int CPU::RRC_B() {
	this->BC.hi = Rotate(this->BC.hi, Direction::right, false);
	return 8;
}

int CPU::RRC_C() {
	this->BC.lo = Rotate(this->BC.lo, Direction::right, false);
	return 8;
}

int CPU::RRC_D() {
	this->DE.hi = Rotate(this->DE.hi, Direction::right, false);
	return 8;
}

int CPU::RRC_E() {
	this->DE.lo = Rotate(this->DE.lo, Direction::right, false);
	return 8;
}

int CPU::RRC_H() {
	this->HL.hi = Rotate(this->HL.hi, Direction::right, false);
	return 8;
}

int CPU::RRC_L() {
	this->HL.lo = Rotate(this->HL.lo, Direction::right, false);
	return 8;
}

int CPU::RRC_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Rotate(value, Direction::right, false);
	this->memory.writeByte(this->HL.reg, value);
	return 16;
}

int CPU::RR_A() {
	this->AF.hi = Rotate(this->AF.hi, Direction::right);
	return 8;
}

int CPU::RR_B() {
	this->BC.hi = Rotate(this->BC.hi, Direction::right);
	return 8;
}

int CPU::RR_C() {
	this->BC.lo = Rotate(this->BC.lo, Direction::right);
	return 8;
}

int CPU::RR_D() {
	this->DE.hi = Rotate(this->DE.hi, Direction::right);
	return 8;
}

int CPU::RR_E() {
	this->DE.lo = Rotate(this->DE.lo, Direction::right);
	return 8;
}

int CPU::RR_H() {
	this->HL.hi = Rotate(this->HL.hi, Direction::right);
	return 8;
}

int CPU::RR_L() {
	this->HL.lo = Rotate(this->HL.lo, Direction::right);
	return 8;
}

int CPU::RR_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Rotate(value, Direction::right);
	this->memory.writeByte(this->HL.reg, value);
	return 16;
}

BYTE CPU::Shift(BYTE value, Direction direction, bool resetSB) {
	if (direction == Direction::right) {
		BYTE carry = value & BIT0;
		BYTE bit7 = (value & BIT7) >> 7;
		value = value >> 1;
		value |= (resetSB) ? 0: bit7;
		this->flags.c = carry;
	}
	else {
		BYTE carry = (value & BIT7) >> 7;
		BYTE bit0 = (value & BIT0);
		value = value << 1;
		value |= (resetSB) ? 0: bit0;
		this->flags.c = carry;
	}

	if (value == 0) {
		this->flags.z = 1;
	}
	else {
		this->flags.z = 0;
	}

	this->flags.n = 0;
	this->flags.h = 0;

	return value;
}

int CPU::SLA_A() {
	this->AF.hi = Shift(this->AF.hi, Direction::left);
	return 8;
}

int CPU::SLA_B() {
	this->BC.hi = Shift(this->BC.hi, Direction::left);
	return 8;
}

int CPU::SLA_C() {
	this->BC.lo = Shift(this->BC.lo, Direction::left);
	return 8;
}

int CPU::SLA_D() {
	this->DE.hi = Shift(this->DE.hi, Direction::left);
	return 8;
}

int CPU::SLA_E() {
	this->DE.lo = Shift(this->DE.lo, Direction::left);
	return 8;
}

int CPU::SLA_H() {
	this->HL.hi = Shift(this->HL.hi, Direction::left);
	return 8;
}

int CPU::SLA_L() {
	this->HL.lo = Shift(this->HL.lo, Direction::left);
	return 8;
}

int CPU::SLA_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Shift(value, Direction::left);
	this->memory.writeByte(this->HL.reg, value);
	return 16;
}

int CPU::SRA_A() {
	this->AF.hi = Shift(this->AF.hi, Direction::right, false);
	return 8;
}

int CPU::SRA_B() {
	this->BC.hi = Shift(this->BC.hi, Direction::right, false);
	return 8;
}

int CPU::SRA_C() {
	this->BC.lo = Shift(this->BC.lo, Direction::right, false);
	return 8;
}

int CPU::SRA_D() {
	this->DE.hi = Shift(this->DE.hi, Direction::right, false);
	return 8;
}

int CPU::SRA_E() {
	this->DE.lo = Shift(this->DE.lo, Direction::right, false);
	return 8;
}

int CPU::SRA_H() {
	this->HL.hi = Shift(this->HL.hi, Direction::right, false);
	return 8;
}

int CPU::SRA_L() {
	this->HL.lo = Shift(this->HL.lo, Direction::right, false);
	return 8;
}

int CPU::SRA_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Shift(value, Direction::right, false);
	this->memory.writeByte(this->HL.reg, value);
	return 16;
}

int CPU::SRL_A() {
	this->AF.hi = Shift(this->AF.hi, Direction::right);
	return 8;
}

int CPU::SRL_B() {
	this->BC.hi = Shift(this->BC.hi, Direction::right);
	return 8;
}

int CPU::SRL_C() {
	this->BC.lo = Shift(this->BC.lo, Direction::right);
	return 8;
}

int CPU::SRL_D() {
	this->DE.hi = Shift(this->DE.hi, Direction::right);
	return 8;
}

int CPU::SRL_E() {
	this->DE.lo = Shift(this->DE.lo, Direction::right);
	return 8;
}

int CPU::SRL_H() {
	this->HL.hi = Shift(this->HL.hi, Direction::right);
	return 8;
}

int CPU::SRL_L() {
	this->HL.lo = Shift(this->HL.lo, Direction::right);
	return 8;
}

int CPU::SRL_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Shift(value, Direction::right);
	this->memory.writeByte(this->HL.reg, value);
	return 16;
}

int CPU::DI() {
	return 4;
}

