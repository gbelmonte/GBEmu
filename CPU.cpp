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
	instructions[0x10] = &CPU::STOP;

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

	instructions[0xF2] = &CPU::LD_A_FF00_C;
	instructions[0xe2] = &CPU::LD_FF00_C_A;
	instructions[0xe0] = &CPU::LD_FF00_n_A;
	instructions[0xF0] = &CPU::LDH_A_FF00_n;
	instructions[0xF8] = &CPU::LDHL_SP_n;

	//Load Dec/Inc
	instructions[0x32] = &CPU::LDD_HL_A;
	instructions[0x22] = &CPU::LDI_HL_A;
	instructions[0x3A] = &CPU::LDD_A_HL;
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

	instructions[0x09] = &CPU::ADD_HL_BC;
	instructions[0x19] = &CPU::ADD_HL_DE;
	instructions[0x29] = &CPU::ADD_HL_HL;
	instructions[0x39] = &CPU::ADD_HL_SP;
	instructions[0xE8] = &CPU::ADD_SP_n;

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

	instructions[0x9F] = &CPU::SBC_A;
	instructions[0x98] = &CPU::SBC_B;
	instructions[0x99] = &CPU::SBC_C;
	instructions[0x9A] = &CPU::SBC_D;
	instructions[0x9B] = &CPU::SBC_E;
	instructions[0x9C] = &CPU::SBC_H;
	instructions[0x9D] = &CPU::SBC_L;
	instructions[0x9E] = &CPU::SBC_HL;
	instructions[0xDE] = &CPU::SBC_n;

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

	//Complement
	instructions[0x2F] = &CPU::CPL;

	instructions[0x37] = &CPU::SCF;
	instructions[0x3F] = &CPU::CCF;

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
	instructions[0xC2] = &CPU::JP_NZ;
	instructions[0xCA] = &CPU::JP_Z;
	instructions[0xD2] = &CPU::JP_NC;
	instructions[0xDA] = &CPU::JP_C;
	instructions[0xE9] = &CPU::JP_HL;

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
	instructions[0xD9] = &CPU::RETI;
	instructions[0xF5] = &CPU::PUSH_AF;
	instructions[0xC5] = &CPU::PUSH_BC;
	instructions[0xD5] = &CPU::PUSH_DE;
	instructions[0xE5] = &CPU::PUSH_HL;

	instructions[0xF1] = &CPU::POP_AF;
	instructions[0xC1] = &CPU::POP_BC;
	instructions[0xD1] = &CPU::POP_DE;
	instructions[0xE1] = &CPU::POP_HL;

	//RSTs
	instructions[0xC7] = &CPU::RST_00;
	instructions[0xCF] = &CPU::RST_08;
	instructions[0xD7] = &CPU::RST_10;
	instructions[0xDF] = &CPU::RST_18;
	instructions[0xE7] = &CPU::RST_20;
	instructions[0xEF] = &CPU::RST_28;
	instructions[0xF7] = &CPU::RST_30;
	instructions[0xFF] = &CPU::RST_38;

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

	instructions_cb[0xC7] = &CPU::SET_0_A;
	instructions_cb[0xCF] = &CPU::SET_1_A;
	instructions_cb[0xD7] = &CPU::SET_2_A;
	instructions_cb[0xDF] = &CPU::SET_3_A;
	instructions_cb[0xE7] = &CPU::SET_4_A;
	instructions_cb[0xEF] = &CPU::SET_5_A;
	instructions_cb[0xF7] = &CPU::SET_6_A;
	instructions_cb[0xFF] = &CPU::SET_7_A;
	instructions_cb[0xC0] = &CPU::SET_0_B;
	instructions_cb[0xC8] = &CPU::SET_1_B;
	instructions_cb[0xD0] = &CPU::SET_2_B;
	instructions_cb[0xD8] = &CPU::SET_3_B;
	instructions_cb[0xE0] = &CPU::SET_4_B;
	instructions_cb[0xE8] = &CPU::SET_5_B;
	instructions_cb[0xF0] = &CPU::SET_6_B;
	instructions_cb[0xF8] = &CPU::SET_7_B;
	instructions_cb[0xC1] = &CPU::SET_0_C;
	instructions_cb[0xC9] = &CPU::SET_1_C;
	instructions_cb[0xD1] = &CPU::SET_2_C;
	instructions_cb[0xD9] = &CPU::SET_3_C;
	instructions_cb[0xE1] = &CPU::SET_4_C;
	instructions_cb[0xE9] = &CPU::SET_5_C;
	instructions_cb[0xF1] = &CPU::SET_6_C;
	instructions_cb[0xF9] = &CPU::SET_7_C;
	instructions_cb[0xC2] = &CPU::SET_0_D;
	instructions_cb[0xCA] = &CPU::SET_1_D;
	instructions_cb[0xD2] = &CPU::SET_2_D;
	instructions_cb[0xDA] = &CPU::SET_3_D;
	instructions_cb[0xE2] = &CPU::SET_4_D;
	instructions_cb[0xEA] = &CPU::SET_5_D;
	instructions_cb[0xF2] = &CPU::SET_6_D;
	instructions_cb[0xFA] = &CPU::SET_7_D;
	instructions_cb[0xC3] = &CPU::SET_0_E;
	instructions_cb[0xCB] = &CPU::SET_1_E;
	instructions_cb[0xD3] = &CPU::SET_2_E;
	instructions_cb[0xDB] = &CPU::SET_3_E;
	instructions_cb[0xE3] = &CPU::SET_4_E;
	instructions_cb[0xEB] = &CPU::SET_5_E;
	instructions_cb[0xF3] = &CPU::SET_6_E;
	instructions_cb[0xFB] = &CPU::SET_7_E;
	instructions_cb[0xC4] = &CPU::SET_0_H;
	instructions_cb[0xCC] = &CPU::SET_1_H;
	instructions_cb[0xD4] = &CPU::SET_2_H;
	instructions_cb[0xDC] = &CPU::SET_3_H;
	instructions_cb[0xE4] = &CPU::SET_4_H;
	instructions_cb[0xEC] = &CPU::SET_5_H;
	instructions_cb[0xF4] = &CPU::SET_6_H;
	instructions_cb[0xFC] = &CPU::SET_7_H;
	instructions_cb[0xC5] = &CPU::SET_0_L;
	instructions_cb[0xCD] = &CPU::SET_1_L;
	instructions_cb[0xD5] = &CPU::SET_2_L;
	instructions_cb[0xDD] = &CPU::SET_3_L;
	instructions_cb[0xE5] = &CPU::SET_4_L;
	instructions_cb[0xED] = &CPU::SET_5_L;
	instructions_cb[0xF5] = &CPU::SET_6_L;
	instructions_cb[0xFD] = &CPU::SET_7_L;
	instructions_cb[0xC6] = &CPU::SET_0_HL;
	instructions_cb[0xCE] = &CPU::SET_1_HL;
	instructions_cb[0xD6] = &CPU::SET_2_HL;
	instructions_cb[0xDE] = &CPU::SET_3_HL;
	instructions_cb[0xE6] = &CPU::SET_4_HL;
	instructions_cb[0xEE] = &CPU::SET_5_HL;
	instructions_cb[0xF6] = &CPU::SET_6_HL;
	instructions_cb[0xFE] = &CPU::SET_7_HL;

	instructions_cb[0x87] = &CPU::RES_0_A;
	instructions_cb[0x8F] = &CPU::RES_1_A;
	instructions_cb[0x97] = &CPU::RES_2_A;
	instructions_cb[0x9F] = &CPU::RES_3_A;
	instructions_cb[0xA7] = &CPU::RES_4_A;
	instructions_cb[0xAF] = &CPU::RES_5_A;
	instructions_cb[0xB7] = &CPU::RES_6_A;
	instructions_cb[0xBF] = &CPU::RES_7_A;
	instructions_cb[0x80] = &CPU::RES_0_B;
	instructions_cb[0x88] = &CPU::RES_1_B;
	instructions_cb[0x90] = &CPU::RES_2_B;
	instructions_cb[0x98] = &CPU::RES_3_B;
	instructions_cb[0xA0] = &CPU::RES_4_B;
	instructions_cb[0xA8] = &CPU::RES_5_B;
	instructions_cb[0xB0] = &CPU::RES_6_B;
	instructions_cb[0xB8] = &CPU::RES_7_B;
	instructions_cb[0x81] = &CPU::RES_0_C;
	instructions_cb[0x89] = &CPU::RES_1_C;
	instructions_cb[0x91] = &CPU::RES_2_C;
	instructions_cb[0x99] = &CPU::RES_3_C;
	instructions_cb[0xA1] = &CPU::RES_4_C;
	instructions_cb[0xA9] = &CPU::RES_5_C;
	instructions_cb[0xB1] = &CPU::RES_6_C;
	instructions_cb[0xB9] = &CPU::RES_7_C;
	instructions_cb[0x82] = &CPU::RES_0_D;
	instructions_cb[0x8A] = &CPU::RES_1_D;
	instructions_cb[0x92] = &CPU::RES_2_D;
	instructions_cb[0x9A] = &CPU::RES_3_D;
	instructions_cb[0xA2] = &CPU::RES_4_D;
	instructions_cb[0xAA] = &CPU::RES_5_D;
	instructions_cb[0xB2] = &CPU::RES_6_D;
	instructions_cb[0xBA] = &CPU::RES_7_D;
	instructions_cb[0x83] = &CPU::RES_0_E;
	instructions_cb[0x8B] = &CPU::RES_1_E;
	instructions_cb[0x93] = &CPU::RES_2_E;
	instructions_cb[0x9B] = &CPU::RES_3_E;
	instructions_cb[0xA3] = &CPU::RES_4_E;
	instructions_cb[0xAB] = &CPU::RES_5_E;
	instructions_cb[0xB3] = &CPU::RES_6_E;
	instructions_cb[0xBB] = &CPU::RES_7_E;
	instructions_cb[0x84] = &CPU::RES_0_H;
	instructions_cb[0x8C] = &CPU::RES_1_H;
	instructions_cb[0x94] = &CPU::RES_2_H;
	instructions_cb[0x9C] = &CPU::RES_3_H;
	instructions_cb[0xA4] = &CPU::RES_4_H;
	instructions_cb[0xAC] = &CPU::RES_5_H;
	instructions_cb[0xB4] = &CPU::RES_6_H;
	instructions_cb[0xBC] = &CPU::RES_7_H;
	instructions_cb[0x85] = &CPU::RES_0_L;
	instructions_cb[0x8D] = &CPU::RES_1_L;
	instructions_cb[0x95] = &CPU::RES_2_L;
	instructions_cb[0x9D] = &CPU::RES_3_L;
	instructions_cb[0xA5] = &CPU::RES_4_L;
	instructions_cb[0xAD] = &CPU::RES_5_L;
	instructions_cb[0xB5] = &CPU::RES_6_L;
	instructions_cb[0xBD] = &CPU::RES_7_L;
	instructions_cb[0x86] = &CPU::RES_0_HL;
	instructions_cb[0x8E] = &CPU::RES_1_HL;
	instructions_cb[0x96] = &CPU::RES_2_HL;
	instructions_cb[0x9E] = &CPU::RES_3_HL;
	instructions_cb[0xA6] = &CPU::RES_4_HL;
	instructions_cb[0xAE] = &CPU::RES_5_HL;
	instructions_cb[0xB6] = &CPU::RES_6_HL;
	instructions_cb[0xBE] = &CPU::RES_7_HL;

	//Swap
	instructions_cb[0x37] = &CPU::SWAP_A;
	instructions_cb[0x30] = &CPU::SWAP_B;
	instructions_cb[0x31] = &CPU::SWAP_C;
	instructions_cb[0x32] = &CPU::SWAP_D;
	instructions_cb[0x33] = &CPU::SWAP_E;
	instructions_cb[0x34] = &CPU::SWAP_H;
	instructions_cb[0x35] = &CPU::SWAP_L;
	instructions_cb[0x36] = &CPU::SWAP_HL;

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

	instructions[0xF3] = &CPU::DI;
	instructions[0xFB] = &CPU::EI;
}

CPU::~CPU(){

}

void CPU::LoadCartridge(char* path){
	if (!this->memory.LoadCartridge(path)) {
		cout << "Cartridge load failed";
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
		//cout << "lcd on. Cycle: " << (int)cycleCounter << endl;
		if (cycleCounter <= 0) {
			BYTE line = this->memory.readByte(0xFF44);
			cout << hex << "Line: " << (int)line;
			cycleCounter = 456;

			if (line == 144) {
				this->gpu.UpdateScreen();
				cout << "DRAW SCREEN VRAM" << endl;
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

int CPU::NOP() {
	Logger::LogInstruction("NOP", "", ""); 
	return 4; 
}

int CPU::STOP() {
	return 4;
}

//instructions
int CPU::LD_A_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "A", "immediate");
	this->AF.hi = immediate;
	return 8;
}

int CPU::LD_B_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "B", "immediate");
	this->BC.hi = immediate;
	return 8;
} 

int CPU::LD_C_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "C", "immediate");
	this->BC.lo = immediate;
	return 8;
}

int CPU::LD_D_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "D", "immediate");
	this->DE.hi = immediate;
	return 8;
} 

int CPU::LD_E_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "E", "immediate");
	this->DE.lo = immediate;
	return 8;
}

int CPU::LD_H_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "H", "immediate");
	this->HL.hi = immediate;
	return 8;
} 

int CPU::LD_L_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "L", "immediate");
	this->HL.lo = immediate;
	return 8;
}

int CPU::LD_A_A() {
	Logger::LogInstruction("LD", "A", "A");
	return 4;
}

int CPU::LD_A_B() {
	this->AF.hi = this->BC.hi;
	Logger::LogInstruction("LD", "A", "B");
	cout << hex << "B = " << (int)this->BC.hi << endl;
	return 4;
}

int CPU::LD_A_C() {
	this->AF.hi = this->BC.lo;
	Logger::LogInstruction("LD", "A", "C");
	return 4;
}

int CPU::LD_A_D() {
	this->AF.hi = this->DE.hi;
	Logger::LogInstruction("LD", "A", "D");
	return 4;
}

int CPU::LD_A_E() {
	this->AF.hi = this->DE.lo;
	Logger::LogInstruction("LD", "A", "E");
	return 4;
}

int CPU::LD_A_H() {
	this->AF.hi = this->HL.hi;
	Logger::LogInstruction("LD", "A", "H");
	return 4;
}

int CPU::LD_A_L() {
	this->AF.hi = this->HL.lo;
	Logger::LogInstruction("LD", "A", "L");
	return 4;
}

int CPU::LD_A_BC() {
	this->AF.hi = this->memory.readByte(this->BC.reg);
	Logger::LogInstruction("LD", "A", "(BC)");
	return 8;
}

int CPU::LD_A_DE() {
	this->AF.hi = this->memory.readByte(this->DE.reg);
	Logger::LogInstruction("LD", "A", "(DE)");
	return 8;
}

int CPU::LD_A_HL() {
	this->AF.hi = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "A", "(HL)");
	return 8;
}

int CPU::LD_A_nn() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	this->AF.hi = this->memory.readByte(address);
	Logger::LogInstruction("LD", "A", "nn");
	return 16;
}

int CPU::LD_B_B() {
	this->BC.hi = this->BC.hi;
	Logger::LogInstruction("LD", "B", "B");
	return 4;
}

int CPU::LD_B_C() {
	this->BC.hi = this->BC.lo;
	Logger::LogInstruction("LD", "B", "C");
	return 4;
}

int CPU::LD_B_D() {
	this->BC.hi = this->DE.hi;
	Logger::LogInstruction("LD", "B", "D");
	return 4;
}

int CPU::LD_B_E() {
	this->BC.hi = this->DE.lo;
	Logger::LogInstruction("LD", "B", "E");
	return 4;
}

int CPU::LD_B_H() {
	this->BC.hi = this->HL.hi;
	Logger::LogInstruction("LD", "B", "H");
	return 4;
}

int CPU::LD_B_L() {
	this->BC.hi = this->HL.lo;
	Logger::LogInstruction("LD", "B", "L");
	return 4;
}

int CPU::LD_B_HL() {
	this->BC.hi = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "B", "(HL)");
	return 8;
}

int CPU::LD_C_B() {
	this->BC.lo = this->BC.hi;
	Logger::LogInstruction("LD", "C", "B");
	return 4;
}

int CPU::LD_C_C() {
	this->BC.lo = this->BC.lo;
	Logger::LogInstruction("LD", "C", "C");
	return 4;
}

int CPU::LD_C_D() {
	this->BC.lo = this->DE.hi;
	Logger::LogInstruction("LD", "C", "D");
	return 4;
}

int CPU::LD_C_E() {
	this->BC.lo = this->DE.lo;
	Logger::LogInstruction("LD", "C", "E");
	return 4;
}

int CPU::LD_C_H() {
	this->BC.lo = this->HL.hi;
	Logger::LogInstruction("LD", "C", "H");
	return 4;
}

int CPU::LD_C_L() {
	this->BC.lo = this->HL.lo;
	Logger::LogInstruction("LD", "C", "L");
	return 4;
}

int CPU::LD_C_HL() {
	this->BC.lo = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "C", "(HL)");
	return 8;
}

int CPU::LD_D_B() {
	this->DE.hi = this->BC.hi;
	Logger::LogInstruction("LD", "D", "B");
	return 4;
}

int CPU::LD_D_C() {
	this->DE.hi = this->BC.lo;
	Logger::LogInstruction("LD", "D", "C");
	return 4;
}

int CPU::LD_D_D() {
	this->DE.hi = this->DE.hi;
	Logger::LogInstruction("LD", "D", "D");
	return 4;
}

int CPU::LD_D_E() {
	this->DE.hi = this->DE.lo;
	Logger::LogInstruction("LD", "D", "E");
	return 4;
}

int CPU::LD_D_H() {
	this->DE.hi = this->HL.hi;
	Logger::LogInstruction("LD", "D", "H");
	return 4;
}

int CPU::LD_D_L() {
	this->DE.hi = this->HL.lo;
	Logger::LogInstruction("LD", "D", "L");
	return 4;
}

int CPU::LD_D_HL() {
	this->DE.hi = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "D", "(HL)");
	return 8;
}


int CPU::LD_E_B() {
	this->DE.lo = this->BC.hi;
	Logger::LogInstruction("LD", "E", "B");
	return 4;
}

int CPU::LD_E_C() {
	this->DE.lo = this->BC.lo;
	Logger::LogInstruction("LD", "E", "C");
	return 4;
}

int CPU::LD_E_D() {
	this->DE.lo = this->DE.hi;
	Logger::LogInstruction("LD", "E", "D");
	return 4;
}

int CPU::LD_E_E() {
	this->DE.lo = this->DE.lo;
	Logger::LogInstruction("LD", "E", "E");
	return 4;
}

int CPU::LD_E_H() {
	this->DE.lo = this->HL.hi;
	Logger::LogInstruction("LD", "E", "H");
	return 4;
}

int CPU::LD_E_L() {
	this->DE.lo = this->HL.lo;
	Logger::LogInstruction("LD", "E", "L");
	return 4;
}

int CPU::LD_E_HL() {
	this->DE.lo = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "E", "(HL)");
	return 8;
}

int CPU::LD_H_B() {
	this->HL.hi = this->BC.hi;
	Logger::LogInstruction("LD", "H", "B");
	return 4;
}

int CPU::LD_H_C() {
	this->HL.hi = this->BC.lo;
	Logger::LogInstruction("LD", "H", "C");
	return 4;
}

int CPU::LD_H_D() {
	this->HL.hi = this->DE.hi;
	Logger::LogInstruction("LD", "H", "D");
	return 4;
}

int CPU::LD_H_E() {
	this->HL.hi = this->DE.lo;
	Logger::LogInstruction("LD", "H", "E");
	return 4;
}

int CPU::LD_H_H() {
	this->HL.hi = this->HL.hi;
	Logger::LogInstruction("LD", "H", "H");
	return 4;
}

int CPU::LD_H_L() {
	this->HL.hi = this->HL.lo;
	Logger::LogInstruction("LD", "H", "L");
	return 4;
}

int CPU::LD_H_HL() {
	this->HL.hi = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "H", "(HL)");
	return 8;
}

int CPU::LD_L_B() {
	this->HL.lo = this->BC.hi;
	Logger::LogInstruction("LD", "L", "B");
	return 4;
}

int CPU::LD_L_C() {
	this->HL.lo = this->BC.lo;
	Logger::LogInstruction("LD", "L", "C");
	return 4;
}

int CPU::LD_L_D() {
	this->HL.lo = this->DE.hi;
	Logger::LogInstruction("LD", "L", "D");
	return 4;
}

int CPU::LD_L_E() {
	this->HL.lo = this->DE.lo;
	Logger::LogInstruction("LD", "L", "E");
	return 4;
}

int CPU::LD_L_H() {
	this->HL.lo = this->HL.hi;
	Logger::LogInstruction("LD", "L", "H");
	return 4;
}

int CPU::LD_L_L() {
	this->HL.lo = this->HL.lo;
	Logger::LogInstruction("LD", "L", "L");
	return 4;
}

int CPU::LD_L_HL() {
	this->HL.lo = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "L", "(HL)");
	return 8;
}

int CPU::LD_B_A() {
	this->BC.hi = this->AF.hi;
	Logger::LogInstruction("LD", "B", "A");
	return 4;
}

int CPU::LD_C_A() {
	this->BC.lo = this->AF.hi;
	Logger::LogInstruction("LD", "C", "A");
	return 4;
}

int CPU::LD_D_A() {
	this->DE.hi = this->AF.hi;
	Logger::LogInstruction("LD", "D", "A");
	return 4;
}

int CPU::LD_E_A() {
	this->DE.lo = this->AF.hi;
	Logger::LogInstruction("LD", "E", "A");
	return 4;
}

int CPU::LD_H_A() {
	this->HL.hi = this->AF.hi;
	Logger::LogInstruction("LD", "H", "A");
	return 4;
}

int CPU::LD_L_A() {
	this->HL.lo = this->AF.hi;
	Logger::LogInstruction("LD", "L", "A");
	return 4;
}

int CPU::LD_BC_A() {
	this->memory.writeByte(this->BC.reg, this->AF.hi);
	Logger::LogInstruction("LD", "(BC)", "A");
	return 8;
}

int CPU::LD_DE_A() {
	this->memory.writeByte(this->DE.reg, this->AF.hi);
	Logger::LogInstruction("LD", "(DE)", "A");
	return 8;
}

int CPU::LD_nn_A() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	this->memory.writeByte(immediate, this->AF.hi);
	Logger::LogInstruction("LD", "(nn)", "A");
	return 16;
}

int CPU::LD_HL_A() {
	this->memory.writeByte(this->HL.reg, this->AF.hi);
	Logger::LogInstruction("LD", "(HL)", "A");
	return 8;
}

int CPU::LD_HL_B() {
	this->memory.writeByte(this->HL.reg, this->BC.hi);
	Logger::LogInstruction("LD", "(HL)", "B");
	return 8;
}

int CPU::LD_HL_C() {
	this->memory.writeByte(this->HL.reg, this->BC.lo);
	Logger::LogInstruction("LD", "(HL)", "C");
	return 8;
}

int CPU::LD_HL_D() {
	this->memory.writeByte(this->HL.reg, this->DE.hi);
	Logger::LogInstruction("LD", "(HL)", "D");
	return 8;
}

int CPU::LD_HL_E() {
	this->memory.writeByte(this->HL.reg, this->DE.lo);
	Logger::LogInstruction("LD", "(HL)", "E");
	return 8;
}

int CPU::LD_HL_H() {
	this->memory.writeByte(this->HL.reg, this->HL.hi);
	Logger::LogInstruction("LD", "(HL)", "H");
	return 8;
}

int CPU::LD_HL_L() {
	this->memory.writeByte(this->HL.reg, this->HL.lo);
	Logger::LogInstruction("LD", "(HL)", "L");
	return 8;
}

int CPU::LD_HL_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("LD", "(HL)", "imm");
	return 12;
}

int CPU::LD_A_FF00_C() {
	WORD address = 0xFF00 + this->BC.lo;
	BYTE value = this->memory.readByte(address);
	this->AF.hi = value;
	Logger::LogInstruction("LD", "A", "(FF00 + C)");
	return 8;
}

int CPU::LD_FF00_C_A(){
	WORD address = 0xFF00 + this->BC.lo;
	this->memory.writeByte(address, this->AF.hi);
	Logger::LogInstruction("LD", "($FF00 + C)", "A");
	return 8;
}

int CPU::LD_FF00_n_A(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	WORD address = 0xFF00 + immediate;
	this->memory.writeByte(address, this->AF.hi);
	Logger::LogInstruction("LD", "($FF00 + imm)", "A");
	return 12;
}

int CPU::LDH_A_FF00_n() {
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	WORD address = 0xFF00 + immediate;
	this->AF.hi = this->memory.readByte(address);
	Logger::LogInstruction("LDH", "A", "($FF00 + imm)");
	return 12;
}

int CPU::LDHL_SP_n() {
	WORD immediate = 0x00;
	immediate |= this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	WORD value = Add16Bit(this->SP.reg, immediate);
	resetFlag(Flag::z);
	this->HL.reg = value;
	Logger::LogInstruction("LDHL", "SP", "n");
	return 12;
}

int CPU::LDD_HL_A(){
	this->memory.writeByte(this->HL.reg, this->AF.hi);
	this->HL.reg--;
	Logger::LogInstruction("LDD", "(HL)", "A");
	return 8;
}

int CPU::LDD_A_HL(){
	this->AF.hi = this->memory.readByte(this->HL.reg);
	this->HL.reg--;
	Logger::LogInstruction("LDD", "A", "(HL)");
	return 8;
}

int CPU::LDI_HL_A(){
	this->memory.writeByte(this->HL.reg, this->AF.hi);
	this->HL.reg++;
	Logger::LogInstruction("LDI", "HL", "A");
	return 8;
}

int CPU::LDI_A_HL() {
	this->AF.hi = this->memory.readByte(this->HL.reg);
	this->HL.reg++;
	Logger::LogInstruction("LDI", "A", "(HL");
	return 8;
}

int CPU::LD_SP_HL() {
	this->SP.reg = this->HL.reg;
	Logger::LogInstruction("LD", "SP", "HL");
	return 8;
}

int CPU::LD_BC_nn(){
	this->BC.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("LD", "BC", "nn");
	return 12;
}

int CPU::LD_DE_nn(){
	this->DE.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("LD", "DE", "nn");
	return 12;
}

int CPU::LD_HL_nn(){
	this->HL.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("LD", "HL", "nn");
	return 12;
}

int CPU::LD_SP_nn(){
	this->SP.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("LD", "SP", "nn");
	return 12;
}

int CPU::LD_nn_SP() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	this->memory.writeByte(address, this->SP.lo);
	this->memory.writeByte(address+1, this->SP.hi);
	Logger::LogInstruction("LD", "nn", "SP");
	return 20;
}

//Jump Instructions
int CPU::JR_NZ() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("JR", "NZ", "");
	if (getFlag(Flag::z) == 0) {
		this->PC.reg += offset;
		cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
	return 8;
}

int CPU::JR_Z() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("JR", "Z", "");
	if (getFlag(Flag::z) == 1) {
		this->PC.reg += offset;
		cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
	return 8;
}

int CPU::JR_NC() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("JR", "NC", "");
	if (getFlag(Flag::c) == 0) {
		this->PC.reg += offset;
		cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
	return 8;
}

int CPU::JR_C() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("JR", "C", "");
	if (getFlag(Flag::c) == 1) {
		this->PC.reg += offset;
		cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
	return 8;
}

int CPU::JR() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("JR", "", "");
	this->PC.reg += offset;
	cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	return 8;
}

int CPU::JP_nn() {
	WORD address = this->memory.readWord(this->PC.reg);
	Logger::LogInstruction("JP", "nn", "");
	this->PC.reg = address;
	return 12;
}

int CPU::JP_NZ() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("JP", "NZ", "");
	if (getFlag(Flag::z) == 0) {
		this->PC.reg = address;
		cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
	return 12;
}

int CPU::JP_Z() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("JP", "Z", "");
	if (getFlag(Flag::z) == 1) {
		this->PC.reg = address;
		cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
	return 12;
}

int CPU::JP_NC() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("JP", "NC", "");
	if (getFlag(Flag::c) == 0) {
		this->PC.reg = address;
		cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
	return 12;
}

int CPU::JP_C() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("JP", "C", "");
	if (getFlag(Flag::c) == 1) {
		this->PC.reg = address;
		cout << hex << "Jump taken to 0x" << (int)this->PC.reg << endl;
	}
	return 12;
}


int CPU::JP_HL() {
	Logger::LogInstruction("JP", "HL", "");
	this->PC.reg = this->HL.reg;
	return 4;
}

void CPU::PushWord(WORD value) {
	BYTE lo = value & 0x00FF;
	BYTE hi = value >> 8;
	PushByte(lo);
	PushByte(hi);
}

void CPU::PushReg(WORD value) {
	BYTE lo = value & 0x00FF;
	BYTE hi = value >> 8;
	PushByte(hi);
	PushByte(lo);
}

WORD CPU::PopWord() {
	WORD retVal = PopByte();
	retVal = retVal << 8;
	retVal = retVal | PopByte();
	//cout << hex << "Pop value 0x" << (int)retVal << endl;
	return retVal;
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

int CPU::CALL_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	PushReg(this->PC.reg);
	this->PC.reg = immediate;
	Logger::LogInstruction("Call", "nn", "");
	return 12;
}

int CPU::CALL_NZ_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	Logger::LogInstruction("Call", "NZ", "nn");
	if (getFlag(Flag::z) == 0) {
		PushReg(this->PC.reg);
		this->PC.reg = immediate;
		cout << hex << "Call taken to 0x" << (int) this->PC.reg << endl;
	}
	return 12;
}

int CPU::CALL_Z_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	Logger::LogInstruction("Call", "Z", "nn");
	if (getFlag(Flag::z) == 1) {
		PushReg(this->PC.reg);
		this->PC.reg = immediate;
		cout << hex << "Call taken to 0x" << (int) this->PC.reg << endl;
	}
	return 12;
}

int CPU::CALL_NC_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	Logger::LogInstruction("Call", "NC", "nn");
	if (getFlag(Flag::c) == 0) {
		PushReg(this->PC.reg);
		this->PC.reg = immediate;
		cout << hex << "Call taken to 0x" << (int) this->PC.reg << endl;
	}
	return 12;
}

int CPU::CALL_C_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	Logger::LogInstruction("Call", "C", "nn");
	if (getFlag(Flag::c) == 1) {
		PushReg(this->PC.reg);
		this->PC.reg = immediate;
		cout << hex << "Call taken to 0x" << (int) this->PC.reg << endl;
	}
	return 12;
}


int CPU::RET() {
	this->PC.reg = PopReg();
	Logger::LogInstruction("RET", "", "");
	return 8;
}

int CPU::RET_NZ() {
	Logger::LogInstruction("RET", "NZ", "");
	if (getFlag(Flag::z) == 0) {
		this->PC.reg = PopReg();
		cout << hex << "Ret taken to 0x" << (int) this->PC.reg << endl;
	}
	return 8;
}

int CPU::RET_Z() {
	Logger::LogInstruction("RET", "Z", "");
	if (getFlag(Flag::z) == 1) {
		this->PC.reg = PopReg();
		cout << hex << "Ret taken to 0x" << (int) this->PC.reg << endl;
	}
	return 8;
}

int CPU::RET_NC() {
	Logger::LogInstruction("RET", "NC", "");
	if (getFlag(Flag::c) == 0) {
		this->PC.reg = PopReg();
		cout << hex << "Ret taken to 0x" << (int) this->PC.reg << endl;
	}
	return 8;
}

int CPU::RET_C() {
	Logger::LogInstruction("RET", "C", "");
	if (getFlag(Flag::c) == 1) {
		this->PC.reg = PopReg();
		cout << hex << "Ret taken to 0x" << (int) this->PC.reg << endl;
	}
	return 8;
}

int CPU::RETI() {
	this->PC.reg = PopReg();
	Logger::LogInstruction("RETI", "", "");
	return 8;
}

int CPU::PUSH_AF() {
	PushReg(this->AF.reg);
	Logger::LogInstruction("PUSH", "AF", "");
	return 16;
}

int CPU::PUSH_BC() {
	PushReg(this->BC.reg);
	Logger::LogInstruction("PUSH", "BC", "");
	return 16;
}

int CPU::PUSH_DE() {
	PushReg(this->DE.reg);
	Logger::LogInstruction("PUSH", "DE", "");
	return 16;
}

int CPU::PUSH_HL() {
	PushReg(this->HL.reg);
	Logger::LogInstruction("PUSH", "HL", "");
	return 16;
}

int CPU::POP_AF() {
	this->AF.reg = PopReg();
	Logger::LogInstruction("POP", "AF", "");
	return 12;
}

int CPU::POP_BC() {
	this->BC.reg = PopReg();
	Logger::LogInstruction("POP", "BC", "");
	return 12;
}

int CPU::POP_DE() {
	this->DE.reg = PopReg();
	Logger::LogInstruction("POP", "DE", "");
	return 12;
}

int CPU::POP_HL() {
	this->HL.reg = PopReg();
	Logger::LogInstruction("POP", "HL", "");
	return 12;
}

int CPU::RST_00() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0000;
	Logger::LogInstruction("RST", "00", "");
	return 32;
}

int CPU::RST_08() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0008;
	Logger::LogInstruction("RST", "08", "");
	return 32;
}

int CPU::RST_10() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0010;
	Logger::LogInstruction("RST", "10", "");
	return 32;
}

int CPU::RST_18() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0018;
	Logger::LogInstruction("RST", "18", "");
	return 32;
}

int CPU::RST_20() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0020;
	Logger::LogInstruction("RST", "20", "");
	return 32;
}

int CPU::RST_28() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0028;
	Logger::LogInstruction("RST", "28", "");
	return 32;
}

int CPU::RST_30() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0030;
	Logger::LogInstruction("RST", "30", "");
	return 32;
}

int CPU::RST_38() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0038;
	Logger::LogInstruction("RST", "38", "");
	return 32;
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

int CPU::ADD_A() {
	this->AF.hi = Add(this->AF.hi, this->AF.hi);
	Logger::LogInstruction("Add", "A", "");
	return 4;
}

int CPU::ADD_B() {
	this->AF.hi = Add(this->AF.hi, this->BC.hi);
	Logger::LogInstruction("Add", "B", "");
	return 4;
}

int CPU::ADD_C() {
	this->AF.hi = Add(this->AF.hi, this->BC.lo);
	Logger::LogInstruction("Add", "C", "");
	return 4;
}

int CPU::ADD_D() {
	this->AF.hi = Add(this->AF.hi, this->DE.hi);
	Logger::LogInstruction("Add", "D", "");
	return 4;
}

int CPU::ADD_E() {
	this->AF.hi = Add(this->AF.hi, this->DE.lo);
	Logger::LogInstruction("Add", "E", "");
	return 4;
}

int CPU::ADD_H() {
	this->AF.hi = Add(this->AF.hi, this->HL.hi);
	Logger::LogInstruction("Add", "H", "");
	return 4;
}

int CPU::ADD_L() {
	this->AF.hi = Add(this->AF.hi, this->HL.lo);
	Logger::LogInstruction("Add", "L", "");
	return 4;
}

int CPU::ADD_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	this->AF.hi = Add(this->AF.hi, value);
	Logger::LogInstruction("Add", "(HL)", "");
	return 8;
}

int CPU::ADD_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->AF.hi = Add(this->AF.hi, value);
	Logger::LogInstruction("Add", "imm", "");
	return 8;
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
	bool setHalfCarry = ((operand1 & 0x0FFF) + (operand2 & 0x0FFF) > 0x0FFF);
	WORD sum = operand1 + operand2;

	resetFlag(Flag::n);

	if (setHalfCarry && (operand2 > 0)) {
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

int CPU::ADD_HL_BC() {
	this->HL.reg = Add16Bit(this->HL.reg, this->BC.reg);
	Logger::LogInstruction("Add", "HL", "BC");
	return 8;
}

int CPU::ADD_HL_DE() {
	this->HL.reg = Add16Bit(this->HL.reg, this->DE.reg);
	Logger::LogInstruction("Add", "HL", "DE");
	return 8;
}

int CPU::ADD_HL_HL() {
	this->HL.reg = Add16Bit(this->HL.reg, this->HL.reg);
	Logger::LogInstruction("Add", "HL", "HL");
	return 8;
}

int CPU::ADD_HL_SP() {
	this->HL.reg = Add16Bit(this->HL.reg, this->SP.reg);
	Logger::LogInstruction("Add", "HL", "SP");
	return 8;
}

int CPU::ADD_SP_n() {
	SIGNED_BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->SP.reg = Add16BitSigned(this->SP.reg, immediate);
	resetFlag(Flag::z);
	resetFlag(Flag::n);
	Logger::LogInstruction("Add", "SP", "n");
	return 16; 
}


int CPU::ADC_A() {
	this->AF.hi = Add(this->AF.hi, this->AF.hi, true);
	Logger::LogInstruction("Adc", "A", "");
	return 4;
}

int CPU::ADC_B() {
	this->AF.hi = Add(this->AF.hi, this->BC.hi, true);
	Logger::LogInstruction("Adc", "B", "");
	return 4;
}

int CPU::ADC_C() {
	this->AF.hi = Add(this->AF.hi, this->BC.lo, true);
	Logger::LogInstruction("Adc", "C", "");
	return 4;
}

int CPU::ADC_D() {
	this->AF.hi = Add(this->AF.hi, this->DE.hi, true);
	Logger::LogInstruction("Adc", "D", "");
	return 4;
}

int CPU::ADC_E() {
	this->AF.hi = Add(this->AF.hi, this->DE.lo, true);
	Logger::LogInstruction("Adc", "E", "");
	return 4;
}

int CPU::ADC_H() {
	this->AF.hi = Add(this->AF.hi, this->HL.hi, true);
	Logger::LogInstruction("Adc", "H", "");
	return 4;
}

int CPU::ADC_L() {
	this->AF.hi = Add(this->AF.hi, this->HL.lo, true);
	Logger::LogInstruction("Adc", "L", "");
	return 4;
}

int CPU::ADC_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	this->AF.hi = Add(this->AF.hi, value, true);
	Logger::LogInstruction("Adc", "(HL)", "");
	return 8;
}

int CPU::ADC_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->AF.hi = Add(this->AF.hi, value, true);
	Logger::LogInstruction("Adc", "imm", "");
	return 8;	
}

//Math instructions
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

int CPU::SUB_A() {
	this->AF.hi = Subtract(this->AF.hi, this->AF.hi);
	Logger::LogInstruction("Sub", "A", "");
	return 4;
}

int CPU::SUB_B() {
	this->AF.hi = Subtract(this->AF.hi, this->BC.hi);
	Logger::LogInstruction("Sub", "B", "");
	return 4;
}

int CPU::SUB_C() {
	this->AF.hi = Subtract(this->AF.hi, this->BC.lo);
	Logger::LogInstruction("Sub", "C", "");
	return 4;
}

int CPU::SUB_D() {
	this->AF.hi = Subtract(this->AF.hi, this->DE.hi);
	Logger::LogInstruction("Sub", "D", "");
	return 4;
}

int CPU::SUB_E() {
	this->AF.hi = Subtract(this->AF.hi, this->DE.lo);
	Logger::LogInstruction("Sub", "E", "");
	return 4;
}

int CPU::SUB_H() {
	this->AF.hi = Subtract(this->AF.hi, this->HL.hi);
	Logger::LogInstruction("Sub", "H", "");
	return 4;
}

int CPU::SUB_L() {
	this->AF.hi = Subtract(this->AF.hi, this->HL.lo);
	Logger::LogInstruction("Sub", "L", "");
	return 4;
}

int CPU::SUB_HL() {
	this->AF.hi = Subtract(this->AF.hi, this->memory.readByte(this->HL.hi));
	Logger::LogInstruction("Sub", "(HL)", "");
	return 8;
}

int CPU::SUB_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->AF.hi = Subtract(this->AF.hi, value);
	Logger::LogInstruction("Sub", "imm", "");
	return 8;
}

int CPU::SBC_A() {
	this->AF.hi = Subtract(this->AF.hi, this->AF.hi, true);
	Logger::LogInstruction("Sbc", "A", "");
	return 4;
}

int CPU::SBC_B() {
	this->AF.hi = Subtract(this->AF.hi, this->BC.hi, true);
	Logger::LogInstruction("Sbc", "B", "");
	return 4;
}

int CPU::SBC_C() {
	this->AF.hi = Subtract(this->AF.hi, this->BC.lo, true);
	Logger::LogInstruction("Sbc", "C", "");
	return 4;
}

int CPU::SBC_D() {
	this->AF.hi = Subtract(this->AF.hi, this->DE.hi, true);
	Logger::LogInstruction("Sbc", "D", "");
	return 4;
}

int CPU::SBC_E() {
	this->AF.hi = Subtract(this->AF.hi, this->DE.lo, true);
	Logger::LogInstruction("Sbc", "E", "");
	return 4;
}

int CPU::SBC_H() {
	this->AF.hi = Subtract(this->AF.hi, this->HL.hi, true);
	Logger::LogInstruction("Sbc", "H", "");
	return 4;
}

int CPU::SBC_L() {
	this->AF.hi = Subtract(this->AF.hi, this->HL.lo, true);
	Logger::LogInstruction("Sbc", "L", "");
	return 4;
}

int CPU::SBC_HL() {
	this->AF.hi = Subtract(this->AF.hi, this->memory.readByte(this->HL.hi), true);
	Logger::LogInstruction("Sbc", "(HL)", "");
	return 8;
}

int CPU::SBC_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->AF.hi = Subtract(this->AF.hi, value, true);
	Logger::LogInstruction("Sbc", "imm", "");
	return 8;
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

int CPU::XOR_A() {
	this->AF.hi = XOR(this->AF.hi, this->AF.hi);
	Logger::LogInstruction("Xor", "A", "");
	return 4;
}

int CPU::XOR_B() {
	this->AF.hi = XOR(this->AF.hi, this->BC.hi);
	Logger::LogInstruction("Xor", "B", "");
	return 4;
}

int CPU::XOR_C() {
	this->AF.hi = XOR(this->AF.hi, this->BC.lo);
	Logger::LogInstruction("Xor", "C", "");
	return 4;
}

int CPU::XOR_D() {
	this->AF.hi = XOR(this->AF.hi, this->DE.hi);
	Logger::LogInstruction("Xor", "D", "");
	return 4;
}

int CPU::XOR_E() {
	this->AF.hi = XOR(this->AF.hi, this->DE.lo);
	Logger::LogInstruction("Xor", "E", "");
	return 4;
}

int CPU::XOR_H() {
	this->AF.hi = XOR(this->AF.hi, this->HL.hi);
	Logger::LogInstruction("Xor", "H", "");
	return 4;
}

int CPU::XOR_L() {
	this->AF.hi = XOR(this->AF.hi, this->HL.lo);
	Logger::LogInstruction("Xor", "L", "");
	return 4;
}

int CPU::XOR_HL() {
	this->AF.hi = XOR(this->AF.hi, this->memory.readByte(this->HL.reg));
	Logger::LogInstruction("Xor", "(HL)", "");
	return 8;	
}

int CPU::XOR_n() {
	this->AF.hi = XOR(this->AF.hi, this->memory.readByte(this->PC.reg));
	this->PC.reg++;
	Logger::LogInstruction("Xor", "imm", "");
	return 8;
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

int CPU::AND_A() {
	AND(this->AF.hi, this->AF.hi);
	Logger::LogInstruction("And", "A", "");
	return 4;
}

int CPU::AND_B() {
	this->AF.hi = AND(this->AF.hi, this->BC.hi);
	Logger::LogInstruction("And", "B", "");
	return 4;
}

int CPU::AND_C() {
	this->AF.hi = AND(this->AF.hi, this->BC.lo);
	Logger::LogInstruction("And", "C", "");
	return 4;
}

int CPU::AND_D() {
	this->AF.hi = AND(this->AF.hi, this->DE.hi);
	Logger::LogInstruction("And", "D", "");
	return 4;
}

int CPU::AND_E() {
	this->AF.hi = AND(this->AF.hi, this->DE.lo);
	Logger::LogInstruction("And", "E", "");
	return 4;
}

int CPU::AND_H() {
	this->AF.hi = AND(this->AF.hi, this->HL.hi);
	Logger::LogInstruction("And", "H", "");
	return 4;
}

int CPU::AND_l() {
	this->AF.hi = AND(this->AF.hi, this->HL.lo);
	Logger::LogInstruction("And", "L", "");
	return 4;
}

int CPU::AND_HL() {
	this->AF.hi = AND(this->AF.hi, this->memory.readByte(this->HL.reg));
	Logger::LogInstruction("And", "(HL)", "");
	return 8;
}

int CPU::AND_n() {
	this->AF.hi = AND(this->AF.hi, this->memory.readByte(this->PC.reg));
	this->PC.reg++;
	Logger::LogInstruction("And", "imm", "");
	return 8;
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

int CPU::OR_A() {
	OR(this->AF.hi, this->AF.hi);
	Logger::LogInstruction("Or", "A", "");
	return 4;
}

int CPU::OR_B() {
	this->AF.hi = OR(this->AF.hi, this->BC.hi);
	Logger::LogInstruction("Or", "B", "");
	return 4;
}

int CPU::OR_C() {
	this->AF.hi = OR(this->AF.hi, this->BC.lo);
	Logger::LogInstruction("Or", "C", "");
	return 4;
}

int CPU::OR_D() {
	this->AF.hi = OR(this->AF.hi, this->DE.hi);
	Logger::LogInstruction("Or", "D", "");
	return 4;
}

int CPU::OR_E() {
	this->AF.hi = OR(this->AF.hi, this->DE.lo);
	Logger::LogInstruction("Or", "E", "");
	return 4;
}

int CPU::OR_H() {
	this->AF.hi = OR(this->AF.hi, this->HL.hi);
	Logger::LogInstruction("Or", "H", "");
	return 4;
}

int CPU::OR_L() {
	this->AF.hi = OR(this->AF.hi, this->HL.lo);
	Logger::LogInstruction("Or", "L", "");
	return 4;
}

int CPU::OR_HL() {
	this->AF.hi = OR(this->AF.hi, this->memory.readByte(this->HL.reg));
	Logger::LogInstruction("Or", "(HL)", "");
	return 8;
}

int CPU::OR_n() {
	this->AF.hi = OR(this->AF.hi, this->memory.readByte(this->PC.reg));
	this->PC.reg++;
	Logger::LogInstruction("Or", "imm", "");
	return 8;
}

int CPU::CPL() {
	this->AF.hi = ~(this->AF.hi);
	setFlag(Flag::n);
	setFlag(Flag::h);
	Logger::LogInstruction("CPL", "", "");
	return 4;
}

int CPU::SCF() {
	setFlag(Flag::c);
	resetFlag(Flag::n);
	resetFlag(Flag::h);
	Logger::LogInstruction("SCF", "", "");
	return 4;
}

int CPU::CCF() {
	if (getFlag(Flag::c) == 1) {
		resetFlag(Flag::c);
	}
	else {
		setFlag(Flag::c);
	}

	resetFlag(Flag::n);
	resetFlag(Flag::h);
	Logger::LogInstruction("CCF", "", "");
	return 4;
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

int CPU::CP_A() {
	Compare(this->AF.hi);
	Logger::LogInstruction("Cp", "A", "");
	return 4;
}

int CPU::CP_B() {
	Compare(this->BC.hi);
	Logger::LogInstruction("Cp", "B", "");
	return 4;
}

int CPU::CP_C() {
	Compare(this->BC.lo);
	Logger::LogInstruction("Cp", "C", "");
	return 4;
}

int CPU::CP_D() {
	Compare(this->DE.hi);
	Logger::LogInstruction("Cp", "D", "");
	return 4;
}

int CPU::CP_E() {
	Compare(this->DE.lo);
	Logger::LogInstruction("Cp", "E", "");
	return 4;
}

int CPU::CP_H() {
	Compare(this->HL.hi);
	Logger::LogInstruction("Cp", "H", "");
	return 4;
}

int CPU::CP_L() {
	Compare(this->HL.lo);
	Logger::LogInstruction("Cp", "L", "");
	return 4;
}

int CPU::CP_MEM_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	Compare(value);
	Logger::LogInstruction("Cp", "(HL)", "");
	return 8;
}

int CPU::CP_n() {
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Compare(immediate);
	Logger::LogInstruction("Cp", "imm", "");
	return 8;
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

int CPU::INC_A() {
	this->AF.hi = RegInc(this->AF.hi);
	Logger::LogInstruction("Inc", "A", "");
	return 4;
}

int CPU::INC_B() {
	this->BC.hi = RegInc(this->BC.hi);
	Logger::LogInstruction("Inc", "B", "");
	return 4;
}

int CPU::INC_C() {
	this->BC.lo = RegInc(this->BC.lo);
	Logger::LogInstruction("Inc", "C", "");
	return 4;
}

int CPU::INC_D() {
	this->DE.hi = RegInc(this->DE.hi);
	Logger::LogInstruction("Inc", "D", "");
	return 4;
}

int CPU::INC_E() {
	this->DE.lo = RegInc(this->DE.lo);
	Logger::LogInstruction("Inc", "E", "");
	return 4;
}

int CPU::INC_H() {
	this->HL.hi = RegInc(this->HL.hi);
	Logger::LogInstruction("Inc", "H", "");
	return 4;
}

int CPU::INC_L() {
	this->HL.lo = RegInc(this->HL.lo);
	Logger::LogInstruction("Inc", "L", "");
	return 4;
}

int CPU::INC_MEM_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = RegInc(value);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("Inc", "(HL)", "");
	return 12;
}

int CPU::INC_BC() {
	this->BC.reg++;
	Logger::LogInstruction("Inc", "BC", "");
	return 8;
}

int CPU::INC_DE() {
	this->DE.reg++;
	Logger::LogInstruction("Inc", "DE", "");
	return 8;
}

int CPU::INC_HL() {
	this->HL.reg++;
	Logger::LogInstruction("Inc", "HL", "");
	return 8;
}

int CPU::INC_SP() {
	this->SP.reg++;
	Logger::LogInstruction("Inc", "SP", "");
	return 8;
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

int CPU::DEC_A() {
	this->AF.hi = RegDec(this->AF.hi);
	Logger::LogInstruction("Dec", "A", "");
	return 4;
}

int CPU::DEC_B() {
	this->BC.hi = RegDec(this->BC.hi);
	Logger::LogInstruction("Dec", "B", "");
	return 4;
}

int CPU::DEC_C() {
	this->BC.lo = RegDec(this->BC.lo);
	Logger::LogInstruction("Dec", "C", "");
	return 4;
}

int CPU::DEC_D() {
	this->DE.hi = RegDec(this->DE.hi);
	Logger::LogInstruction("Dec", "D", "");
	return 4;
}

int CPU::DEC_E() {
	this->DE.lo = RegDec(this->DE.lo);
	Logger::LogInstruction("Dec", "E", "");
	return 4;
}

int CPU::DEC_H() {
	this->HL.hi = RegDec(this->HL.hi);
	Logger::LogInstruction("Dec", "H", "");
	return 4;
}

int CPU::DEC_L() {
	this->HL.lo = RegDec(this->HL.lo);
	Logger::LogInstruction("Dec", "L", "");
	return 4;
}

int CPU::DEC_MEM_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = RegDec(value);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("Dec", "(HL)", "");
	return 12;
}

int CPU::DEC_BC() {
	this->BC.reg--;
	Logger::LogInstruction("Dec", "BC", "");
	return 8;
}

int CPU::DEC_DE() {
	this->DE.reg--;
	Logger::LogInstruction("Dec", "DE", "");
	return 8;
}

int CPU::DEC_HL() {
	this->HL.reg--;
	Logger::LogInstruction("Dec", "HL", "");
	return 8;
}

int CPU::DEC_SP() {
	this->SP.reg--;
	Logger::LogInstruction("Dec", "SP", "");
	return 8;
}



//Bit instructions
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

int CPU::BIT_0_A() {
	TestBit(this->AF.hi, BIT0);
	Logger::LogInstruction("Bit", "0", "A");
	return 4;
} 

int CPU::BIT_1_A() {
	TestBit(this->AF.hi, BIT1);
	Logger::LogInstruction("Bit", "1", "A");
	return 4;
}

int CPU::BIT_2_A() {
	TestBit(this->AF.hi, BIT2);
	Logger::LogInstruction("Bit", "2", "A");
	return 4;
}

int CPU::BIT_3_A() {
	TestBit(this->AF.hi, BIT3);
	Logger::LogInstruction("Bit", "3", "A");
	return 4;
}

int CPU::BIT_4_A() {
	TestBit(this->AF.hi, BIT4);
	Logger::LogInstruction("Bit", "4", "A");
	return 4;
}

int CPU::BIT_5_A() {
	TestBit(this->AF.hi, BIT5);
	Logger::LogInstruction("Bit", "5", "A");
	return 4;
}

int CPU::BIT_6_A() {
	TestBit(this->AF.hi, BIT6);
	Logger::LogInstruction("Bit", "6", "A");
	return 4;
}

int CPU::BIT_7_A() {
	TestBit(this->AF.hi, BIT7);
	Logger::LogInstruction("Bit", "7", "A");
	return 4;
}

int CPU::BIT_0_B() {
	TestBit(this->BC.hi, BIT0);
	Logger::LogInstruction("Bit", "0", "B");
	return 4;
}

int CPU::BIT_1_B() {
	TestBit(this->BC.hi, BIT1);
	Logger::LogInstruction("Bit", "1", "B");
	return 4;
}

int CPU::BIT_2_B() {
	TestBit(this->BC.hi, BIT2);
	Logger::LogInstruction("Bit", "2", "B");
	return 4;
}

int CPU::BIT_3_B() {
	TestBit(this->BC.hi, BIT3);
	Logger::LogInstruction("Bit", "3", "B");
	return 4;
}

int CPU::BIT_4_B() {
	TestBit(this->BC.hi, BIT4);
	Logger::LogInstruction("Bit", "4", "B");
	return 4;
}

int CPU::BIT_5_B() {
	TestBit(this->BC.hi, BIT5);
	Logger::LogInstruction("Bit", "5", "B");
	return 4;
}

int CPU::BIT_6_B() {
	TestBit(this->BC.hi, BIT6);
	Logger::LogInstruction("Bit", "6", "B");
	return 4;
}

int CPU::BIT_7_B() {
	TestBit(this->BC.hi, BIT7);
	Logger::LogInstruction("Bit", "7", "B");
	return 4;
}

int CPU::BIT_0_C() {
	TestBit(this->BC.lo, BIT0);
	Logger::LogInstruction("Bit", "0", "C");
	return 4;
}

int CPU::BIT_1_C() {
	TestBit(this->BC.lo, BIT1);
	Logger::LogInstruction("Bit", "1", "C");
	return 4;
}

int CPU::BIT_2_C() {
	TestBit(this->BC.lo, BIT2);
	Logger::LogInstruction("Bit", "2", "C");
	return 4;
}

int CPU::BIT_3_C() {
	TestBit(this->BC.lo, BIT3);
	Logger::LogInstruction("Bit", "3", "C");
	return 4;
}

int CPU::BIT_4_C() {
	TestBit(this->BC.lo, BIT4);
	Logger::LogInstruction("Bit", "4", "C");
	return 4;
}

int CPU::BIT_5_C() {
	TestBit(this->BC.lo, BIT5);
	Logger::LogInstruction("Bit", "5", "C");
	return 4;
}

int CPU::BIT_6_C() {
	TestBit(this->BC.lo, BIT6);
	Logger::LogInstruction("Bit", "6", "C");
	return 4;
}

int CPU::BIT_7_C() {
	TestBit(this->BC.lo, BIT7);
	Logger::LogInstruction("Bit", "7", "C");
	return 4;
}

int CPU::BIT_0_D() {
	TestBit(this->DE.hi, BIT0);
	Logger::LogInstruction("Bit", "0", "D");
	return 4;
}

int CPU::BIT_1_D() {
	TestBit(this->DE.hi, BIT1);
	Logger::LogInstruction("Bit", "1", "D");
	return 4;
}

int CPU::BIT_2_D() {
	TestBit(this->DE.hi, BIT2);
	Logger::LogInstruction("Bit", "2", "D");
	return 4;
}

int CPU::BIT_3_D() {
	TestBit(this->DE.hi, BIT3);
	Logger::LogInstruction("Bit", "3", "D");
	return 4;
}

int CPU::BIT_4_D() {
	TestBit(this->DE.hi, BIT4);
	Logger::LogInstruction("Bit", "4", "D");
	return 4;
}

int CPU::BIT_5_D() {
	TestBit(this->DE.hi, BIT5);
	Logger::LogInstruction("Bit", "5", "D");
	return 4;
}

int CPU::BIT_6_D() {
	TestBit(this->DE.hi, BIT6);
	Logger::LogInstruction("Bit", "6", "D");
	return 4;
}

int CPU::BIT_7_D() {
	TestBit(this->DE.hi, BIT7);
	Logger::LogInstruction("Bit", "7", "D");
	return 4;
}
 
int CPU::BIT_0_E() {
	TestBit(this->DE.lo, BIT0);
	Logger::LogInstruction("Bit", "0", "E");
	return 4;
}

int CPU::BIT_1_E() {
	TestBit(this->DE.lo, BIT1);
	Logger::LogInstruction("Bit", "1", "E");
	return 4;
}

int CPU::BIT_2_E() {
	TestBit(this->DE.lo, BIT2);
	Logger::LogInstruction("Bit", "2", "E");
	return 4;
}

int CPU::BIT_3_E() {
	TestBit(this->DE.lo, BIT3);
	Logger::LogInstruction("Bit", "3", "E");
	return 4;
}

int CPU::BIT_4_E() {
	TestBit(this->DE.lo, BIT4);
	Logger::LogInstruction("Bit", "4", "E");
	return 4;
}

int CPU::BIT_5_E() {
	TestBit(this->DE.lo, BIT5);
	Logger::LogInstruction("Bit", "5", "E");
	return 4;
}

int CPU::BIT_6_E() {
	TestBit(this->DE.lo, BIT6);
	Logger::LogInstruction("Bit", "6", "E");
	return 4;
}

int CPU::BIT_7_E() {
	TestBit(this->DE.lo, BIT7);
	Logger::LogInstruction("Bit", "7", "E");
	return 4;
}
 
int CPU::BIT_0_H() {
	TestBit(this->HL.hi, BIT0);
	Logger::LogInstruction("Bit", "0", "H");
	return 4;
}

int CPU::BIT_1_H() {
	TestBit(this->HL.hi, BIT1);
	Logger::LogInstruction("Bit", "1", "H");
	return 4;
}

int CPU::BIT_2_H() {
	TestBit(this->HL.hi, BIT2);
	Logger::LogInstruction("Bit", "2", "H");
	return 4;
}

int CPU::BIT_3_H() {
	TestBit(this->HL.hi, BIT3);
	Logger::LogInstruction("Bit", "3", "H");
	return 4;
}

int CPU::BIT_4_H() {
	TestBit(this->HL.hi, BIT4);
	Logger::LogInstruction("Bit", "4", "H");
	return 4;
}

int CPU::BIT_5_H() {
	TestBit(this->HL.hi, BIT5);
	Logger::LogInstruction("Bit", "5", "H");
	return 4;
}

int CPU::BIT_6_H() {
	TestBit(this->HL.hi, BIT6);
	Logger::LogInstruction("Bit", "6", "H");
	return 4;
}

int CPU::BIT_7_H() {
	TestBit(this->HL.hi, BIT7);
	Logger::LogInstruction("Bit", "7", "H");
	return 4;
}
 
int CPU::BIT_0_L() {
	TestBit(this->HL.lo, BIT0);
	Logger::LogInstruction("Bit", "0", "L");
	return 4;
}

int CPU::BIT_1_L() {
	TestBit(this->HL.lo, BIT1);
	Logger::LogInstruction("Bit", "1", "L");
	return 4;
}

int CPU::BIT_2_L() {
	TestBit(this->HL.lo, BIT2);
	Logger::LogInstruction("Bit", "2", "L");
	return 4;
}

int CPU::BIT_3_L() {
	TestBit(this->HL.lo, BIT3);
	Logger::LogInstruction("Bit", "3", "L");
	return 4;
}

int CPU::BIT_4_L() {
	TestBit(this->HL.lo, BIT4);
	Logger::LogInstruction("Bit", "4", "L");
	return 4;
}

int CPU::BIT_5_L() {
	TestBit(this->HL.lo, BIT5);
	Logger::LogInstruction("Bit", "5", "L");
	return 4;
}

int CPU::BIT_6_L() {
	TestBit(this->HL.lo, BIT6);
	Logger::LogInstruction("Bit", "6", "L");
	return 4;
}

int CPU::BIT_7_L() {
	TestBit(this->HL.lo, BIT7);
	Logger::LogInstruction("Bit", "7", "L");
	return 4;
}

int CPU::BIT_0_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT0);
	Logger::LogInstruction("Bit", "0", "(HL)");
	return 4;
}
int CPU::BIT_1_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT1);
	Logger::LogInstruction("Bit", "1", "(HL)");
	return 4;
}
int CPU::BIT_2_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT2);
	Logger::LogInstruction("Bit", "2", "(HL)");
	return 4;
}
int CPU::BIT_3_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT3);
	Logger::LogInstruction("Bit", "3", "(HL)");
	return 4;
}
int CPU::BIT_4_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT4);
	Logger::LogInstruction("Bit", "4", "(HL)");
	return 4;
}
int CPU::BIT_5_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT5);
	Logger::LogInstruction("Bit", "5", "(HL)");
	return 4;
}
int CPU::BIT_6_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT6);
	Logger::LogInstruction("Bit", "6", "(HL)");
	return 4;
}
int CPU::BIT_7_HL() {
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT7);
	Logger::LogInstruction("Bit", "7", "(HL)");
	return 4;
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

int CPU::SET_0_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT0, 1);
	Logger::LogInstruction("SET", "0", "A");
	return 8;
}

int CPU::SET_1_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT1, 1);
	Logger::LogInstruction("SET", "1", "A");
	return 8;
}

int CPU::SET_2_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT2, 1);
	Logger::LogInstruction("SET", "2", "A");
	return 8;
}

int CPU::SET_3_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT3, 1);
	Logger::LogInstruction("SET", "3", "A");
	return 8;
}

int CPU::SET_4_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT4, 1);
	Logger::LogInstruction("SET", "4", "A");
	return 8;
}

int CPU::SET_5_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT5, 1);
	Logger::LogInstruction("SET", "5", "A");
	return 8;
}

int CPU::SET_6_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT6, 1);
	Logger::LogInstruction("SET", "6", "A");
	return 8;
}

int CPU::SET_7_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT7, 1);
	Logger::LogInstruction("SET", "7", "A");
	return 8;
}

int CPU::SET_0_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT0, 1);
	Logger::LogInstruction("SET", "0", "B");
	return 8;
}

int CPU::SET_1_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT1, 1);
	Logger::LogInstruction("SET", "1", "B");
	return 8;
}

int CPU::SET_2_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT2, 1);
	Logger::LogInstruction("SET", "2", "B");
	return 8;
}

int CPU::SET_3_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT3, 1);
	Logger::LogInstruction("SET", "3", "B");
	return 8;
}

int CPU::SET_4_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT4, 1);
	Logger::LogInstruction("SET", "4", "B");
	return 8;
}

int CPU::SET_5_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT5, 1);
	Logger::LogInstruction("SET", "5", "B");
	return 8;
}

int CPU::SET_6_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT6, 1);
	Logger::LogInstruction("SET", "6", "B");
	return 8;
}

int CPU::SET_7_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT7, 1);
	Logger::LogInstruction("SET", "7", "B");
	return 8;
}

int CPU::SET_0_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT0, 1);
	Logger::LogInstruction("SET", "0", "C");
	return 8;
}

int CPU::SET_1_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT1, 1);
	Logger::LogInstruction("SET", "1", "C");
	return 8;
}

int CPU::SET_2_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT2, 1);
	Logger::LogInstruction("SET", "2", "C");
	return 8;
}

int CPU::SET_3_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT3, 1);
	Logger::LogInstruction("SET", "3", "C");
	return 8;
}

int CPU::SET_4_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT4, 1);
	Logger::LogInstruction("SET", "4", "C");
	return 8;
}

int CPU::SET_5_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT5, 1);
	Logger::LogInstruction("SET", "5", "C");
	return 8;
}

int CPU::SET_6_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT6, 1);
	Logger::LogInstruction("SET", "6", "C");
	return 8;
}

int CPU::SET_7_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT7, 1);
	Logger::LogInstruction("SET", "7", "C");
	return 8;
}

int CPU::SET_0_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT0, 1);
	Logger::LogInstruction("SET", "0", "D");
	return 8;
}

int CPU::SET_1_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT1, 1);
	Logger::LogInstruction("SET", "1", "D");
	return 8;
}

int CPU::SET_2_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT2, 1);
	Logger::LogInstruction("SET", "2", "D");
	return 8;
}

int CPU::SET_3_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT3, 1);
	Logger::LogInstruction("SET", "3", "D");
	return 8;
}

int CPU::SET_4_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT4, 1);
	Logger::LogInstruction("SET", "4", "D");
	return 8;
}

int CPU::SET_5_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT5, 1);
	Logger::LogInstruction("SET", "5", "D");
	return 8;
}

int CPU::SET_6_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT6, 1);
	Logger::LogInstruction("SET", "6", "D");
	return 8;
}

int CPU::SET_7_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT7, 1);
	Logger::LogInstruction("SET", "7", "D");
	return 8;
}

int CPU::SET_0_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT0, 1);
	Logger::LogInstruction("SET", "0", "E");
	return 8;
}

int CPU::SET_1_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT1, 1);
	Logger::LogInstruction("SET", "1", "E");
	return 8;
}

int CPU::SET_2_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT2, 1);
	Logger::LogInstruction("SET", "2", "E");
	return 8;
}

int CPU::SET_3_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT3, 1);
	Logger::LogInstruction("SET", "3", "E");
	return 8;
}

int CPU::SET_4_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT4, 1);
	Logger::LogInstruction("SET", "4", "E");
	return 8;
}

int CPU::SET_5_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT5, 1);
	Logger::LogInstruction("SET", "5", "E");
	return 8;
}

int CPU::SET_6_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT6, 1);
	Logger::LogInstruction("SET", "6", "E");
	return 8;
}

int CPU::SET_7_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT7, 1);
	Logger::LogInstruction("SET", "7", "E");
	return 8;
}

int CPU::SET_0_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT0, 1);
	Logger::LogInstruction("SET", "0", "H");
	return 8;
}

int CPU::SET_1_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT1, 1);
	Logger::LogInstruction("SET", "1", "H");
	return 8;
}

int CPU::SET_2_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT2, 1);
	Logger::LogInstruction("SET", "2", "H");
	return 8;
}

int CPU::SET_3_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT3, 1);
	Logger::LogInstruction("SET", "3", "H");
	return 8;
}

int CPU::SET_4_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT4, 1);
	Logger::LogInstruction("SET", "4", "H");
	return 8;
}

int CPU::SET_5_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT5, 1);
	Logger::LogInstruction("SET", "5", "H");
	return 8;
}

int CPU::SET_6_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT6, 1);
	Logger::LogInstruction("SET", "6", "H");
	return 8;
}

int CPU::SET_7_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT7, 1);
	Logger::LogInstruction("SET", "7", "H");
	return 8;
}

int CPU::SET_0_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT0, 1);
	Logger::LogInstruction("SET", "0", "L");
	return 8;
}

int CPU::SET_1_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT1, 1);
	Logger::LogInstruction("SET", "1", "L");
	return 8;
}

int CPU::SET_2_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT2, 1);
	Logger::LogInstruction("SET", "2", "L");
	return 8;
}

int CPU::SET_3_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT3, 1);
	Logger::LogInstruction("SET", "3", "L");
	return 8;
}

int CPU::SET_4_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT4, 1);
	Logger::LogInstruction("SET", "4", "L");
	return 8;
}

int CPU::SET_5_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT5, 1);
	Logger::LogInstruction("SET", "5", "L");
	return 8;
}

int CPU::SET_6_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT6, 1);
	Logger::LogInstruction("SET", "6", "L");
	return 8;
}

int CPU::SET_7_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT7, 1);
	Logger::LogInstruction("SET", "7", "L");
	return 8;
}

int CPU::SET_0_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT0, 1);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "0", "(HL)");
	return 16;
}

int CPU::SET_1_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT1, 1);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "1", "(HL)");
	return 16;
}

int CPU::SET_2_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT2, 1);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "2", "(HL)");
	return 16;
}

int CPU::SET_3_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT3, 1);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "3", "(HL)");
	return 16;
}

int CPU::SET_4_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT4, 1);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "4", "(HL)");
	return 16;
}

int CPU::SET_5_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT5, 1);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "5", "(HL)");
	return 16;
}

int CPU::SET_6_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT6, 1);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "6", "(HL)");
	return 16;
}

int CPU::SET_7_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT7, 1);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "7", "(HL)");
	return 16;
}

int CPU::RES_0_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT0, 0);
	Logger::LogInstruction("RES", "0", "A");
	return 8;
}

int CPU::RES_1_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT1, 0);
	Logger::LogInstruction("RES", "1", "A");
	return 8;
}

int CPU::RES_2_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT2, 0);
	Logger::LogInstruction("RES", "2", "A");
	return 8;
}

int CPU::RES_3_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT3, 0);
	Logger::LogInstruction("RES", "3", "A");
	return 8;
}

int CPU::RES_4_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT4, 0);
	Logger::LogInstruction("RES", "4", "A");
	return 8;
}

int CPU::RES_5_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT5, 0);
	Logger::LogInstruction("RES", "5", "A");
	return 8;
}

int CPU::RES_6_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT6, 0);
	Logger::LogInstruction("RES", "6", "A");
	return 8;
}

int CPU::RES_7_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT7, 0);
	Logger::LogInstruction("RES", "7", "A");
	return 8;
}

int CPU::RES_0_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT0, 0);
	Logger::LogInstruction("RES", "0", "B");
	return 8;
}

int CPU::RES_1_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT1, 0);
	Logger::LogInstruction("RES", "1", "B");
	return 8;
}

int CPU::RES_2_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT2, 0);
	Logger::LogInstruction("RES", "2", "B");
	return 8;
}

int CPU::RES_3_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT3, 0);
	Logger::LogInstruction("RES", "3", "B");
	return 8;
}

int CPU::RES_4_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT4, 0);
	Logger::LogInstruction("RES", "4", "B");
	return 8;
}

int CPU::RES_5_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT5, 0);
	Logger::LogInstruction("RES", "5", "B");
	return 8;
}

int CPU::RES_6_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT6, 0);
	Logger::LogInstruction("RES", "6", "B");
	return 8;
}

int CPU::RES_7_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT7, 0);
	Logger::LogInstruction("RES", "7", "B");
	return 8;
}

int CPU::RES_0_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT0, 0);
	Logger::LogInstruction("RES", "0", "C");
	return 8;
}

int CPU::RES_1_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT1, 0);
	Logger::LogInstruction("RES", "1", "C");
	return 8;
}

int CPU::RES_2_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT2, 0);
	Logger::LogInstruction("RES", "2", "C");
	return 8;
}

int CPU::RES_3_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT3, 0);
	Logger::LogInstruction("RES", "3", "C");
	return 8;
}

int CPU::RES_4_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT4, 0);
	Logger::LogInstruction("RES", "4", "C");
	return 8;
}

int CPU::RES_5_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT5, 0);
	Logger::LogInstruction("RES", "5", "C");
	return 8;
}

int CPU::RES_6_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT6, 0);
	Logger::LogInstruction("RES", "6", "C");
	return 8;
}

int CPU::RES_7_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT7, 0);
	Logger::LogInstruction("RES", "7", "C");
	return 8;
}

int CPU::RES_0_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT0, 0);
	Logger::LogInstruction("RES", "0", "D");
	return 8;
}

int CPU::RES_1_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT1, 0);
	Logger::LogInstruction("RES", "1", "D");
	return 8;
}

int CPU::RES_2_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT2, 0);
	Logger::LogInstruction("RES", "2", "D");
	return 8;
}

int CPU::RES_3_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT3, 0);
	Logger::LogInstruction("RES", "3", "D");
	return 8;
}

int CPU::RES_4_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT4, 0);
	Logger::LogInstruction("RES", "4", "D");
	return 8;
}

int CPU::RES_5_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT5, 0);
	Logger::LogInstruction("RES", "5", "D");
	return 8;
}

int CPU::RES_6_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT6, 0);
	Logger::LogInstruction("RES", "6", "D");
	return 8;
}

int CPU::RES_7_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT7, 0);
	Logger::LogInstruction("RES", "7", "D");
	return 8;
}

int CPU::RES_0_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT0, 0);
	Logger::LogInstruction("RES", "0", "E");
	return 8;
}

int CPU::RES_1_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT1, 0);
	Logger::LogInstruction("RES", "1", "E");
	return 8;
}

int CPU::RES_2_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT2, 0);
	Logger::LogInstruction("RES", "2", "E");
	return 8;
}

int CPU::RES_3_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT3, 0);
	Logger::LogInstruction("RES", "3", "E");
	return 8;
}

int CPU::RES_4_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT4, 0);
	Logger::LogInstruction("RES", "4", "E");
	return 8;
}

int CPU::RES_5_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT5, 0);
	Logger::LogInstruction("RES", "5", "E");
	return 8;
}

int CPU::RES_6_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT6, 0);
	Logger::LogInstruction("RES", "6", "E");
	return 8;
}

int CPU::RES_7_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT7, 0);
	Logger::LogInstruction("RES", "7", "E");
	return 8;
}

int CPU::RES_0_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT0, 0);
	Logger::LogInstruction("RES", "0", "H");
	return 8;
}

int CPU::RES_1_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT1, 0);
	Logger::LogInstruction("RES", "1", "H");
	return 8;
}

int CPU::RES_2_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT2, 0);
	Logger::LogInstruction("RES", "2", "H");
	return 8;
}

int CPU::RES_3_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT3, 0);
	Logger::LogInstruction("RES", "3", "H");
	return 8;
}

int CPU::RES_4_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT4, 0);
	Logger::LogInstruction("RES", "4", "H");
	return 8;
}

int CPU::RES_5_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT5, 0);
	Logger::LogInstruction("RES", "5", "H");
	return 8;
}

int CPU::RES_6_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT6, 0);
	Logger::LogInstruction("RES", "6", "H");
	return 8;
}

int CPU::RES_7_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT7, 0);
	Logger::LogInstruction("RES", "7", "H");
	return 8;
}

int CPU::RES_0_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT0, 0);
	Logger::LogInstruction("RES", "0", "L");
	return 8;
}

int CPU::RES_1_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT1, 0);
	Logger::LogInstruction("RES", "1", "L");
	return 8;
}

int CPU::RES_2_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT2, 0);
	Logger::LogInstruction("RES", "2", "L");
	return 8;
}

int CPU::RES_3_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT3, 0);
	Logger::LogInstruction("RES", "3", "L");
	return 8;
}

int CPU::RES_4_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT4, 0);
	Logger::LogInstruction("RES", "4", "L");
	return 8;
}

int CPU::RES_5_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT5, 0);
	Logger::LogInstruction("RES", "5", "L");
	return 8;
}

int CPU::RES_6_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT6, 0);
	Logger::LogInstruction("RES", "6", "L");
	return 8;
}

int CPU::RES_7_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT7, 0);
	Logger::LogInstruction("RES", "7", "L");
	return 8;
}

int CPU::RES_0_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT0, 0);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "0", "(HL)");
	return 16;
}

int CPU::RES_1_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT1, 0);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "1", "(HL)");
	return 16;
}

int CPU::RES_2_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT2, 0);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "2", "(HL)");
	return 16;
}

int CPU::RES_3_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT3, 0);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "3", "(HL)");
	return 16;
}

int CPU::RES_4_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT4, 0);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "4", "(HL)");
	return 16;
}

int CPU::RES_5_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT5, 0);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "5", "(HL)");
	return 16;
}

int CPU::RES_6_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT6, 0);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "6", "(HL)");
	return 16;
}

int CPU::RES_7_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT7, 0);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "7", "(HL)");
	return 16;
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

int CPU::SWAP_A() {
	this->AF.hi = SWAP(this->AF.hi);
	return 8;
}

int CPU::SWAP_B() {
	this->BC.hi = SWAP(this->BC.hi);
	return 8;
}

int CPU::SWAP_C() {
	this->BC.lo = SWAP(this->BC.lo);
	return 8;
}

int CPU::SWAP_D() {
	this->DE.hi = SWAP(this->DE.hi);
	return 8;
}

int CPU::SWAP_E() {
	this->DE.lo = SWAP(this->DE.lo);
	return 8;
}

int CPU::SWAP_H() {
	this->HL.hi = SWAP(this->HL.hi);
	return 8;
}

int CPU::SWAP_L() {
	this->HL.lo = SWAP(this->HL.lo);
	return 8;
}

int CPU::SWAP_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SWAP(value);
	this->memory.writeByte(this->HL.reg, value);
	return 16;
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

int CPU::RLC_A() {
	this->AF.hi = Rotate(this->AF.hi, Direction::left, false);
	Logger::LogInstruction("RLC", "A", "");
	return 8;
}

int CPU::RLC_B() {
	this->BC.hi = Rotate(this->BC.hi, Direction::left, false);
	Logger::LogInstruction("RLC", "B", "");
	return 8;
}

int CPU::RLC_C() {
	this->BC.lo = Rotate(this->BC.lo, Direction::left, false);
	Logger::LogInstruction("RLC", "C", "");
	return 8;
}

int CPU::RLC_D() {
	this->DE.hi = Rotate(this->DE.hi, Direction::left, false);
	Logger::LogInstruction("RLC", "D", "");
	return 8;
}

int CPU::RLC_E() {
	this->DE.lo = Rotate(this->DE.lo, Direction::left, false);
	Logger::LogInstruction("RLC", "E", "");
	return 8;
}

int CPU::RLC_H() {
	this->HL.hi = Rotate(this->HL.hi, Direction::left, false);
	Logger::LogInstruction("RLC", "H", "");
	return 8;
}

int CPU::RLC_L() {
	this->HL.lo = Rotate(this->HL.lo, Direction::left, false);
	Logger::LogInstruction("RLC", "L", "");
	return 8;
}

int CPU::RLC_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Rotate(value, Direction::left, false);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RLC", "(HL)", "");
	return 16;
}

int CPU::RLA() {
	this->AF.hi = Rotate(this->AF.hi, Direction::left, true);
	resetFlag(Flag::z);
	Logger::LogInstruction("RLA", "", "");
	return 4;
}

int CPU::RLCA() {
	this->AF.hi = Rotate(this->AF.hi, Direction::left, false);
	resetFlag(Flag::z);
	Logger::LogInstruction("RLCA", "", "");
	return 4;
}

int CPU::RRA() {
	this->AF.hi = Rotate(this->AF.hi, Direction::right);
	resetFlag(Flag::z);
	Logger::LogInstruction("RRA", "", "");
	return 4;
}

int CPU::RRCA() {
	this->AF.hi = Rotate(this->AF.hi, Direction::right, false);
	resetFlag(Flag::z);
	Logger::LogInstruction("RRCA", "", "");
	return 4;
}

int CPU::RL_A() {
	this->AF.hi = Rotate(this->AF.hi, Direction::left);
	Logger::LogInstruction("RL", "A", "");
	return 8;
}

int CPU::RL_B() {
	this->BC.hi = Rotate(this->BC.hi, Direction::left);
	Logger::LogInstruction("RL", "B", "");
	return 8;
}

int CPU::RL_C() {
	this->BC.lo = Rotate(this->BC.lo, Direction::left);
	Logger::LogInstruction("RL", "C", "");
	return 8;
}

int CPU::RL_D() {
	this->DE.hi = Rotate(this->DE.hi, Direction::left);
	Logger::LogInstruction("RL", "D", "");
	return 8;
}

int CPU::RL_E() {
	this->DE.lo = Rotate(this->DE.lo, Direction::left);
	Logger::LogInstruction("RL", "E", "");
	return 8;
}

int CPU::RL_H() {
	this->HL.hi = Rotate(this->HL.hi, Direction::left);
	Logger::LogInstruction("RL", "H", "");
	return 8;
}

int CPU::RL_L() {
	this->HL.lo = Rotate(this->HL.lo, Direction::left);
	Logger::LogInstruction("RL", "L", "");
	return 8;
}

int CPU::RL_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Rotate(value, Direction::left);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RL", "(HL)", "");
	return 16;
}

int CPU::RRC_A() {
	this->AF.hi = Rotate(this->AF.hi, Direction::right, false);
	Logger::LogInstruction("RRC", "A", "");
	return 8;
}

int CPU::RRC_B() {
	this->BC.hi = Rotate(this->BC.hi, Direction::right, false);
	Logger::LogInstruction("RRC", "B", "");
	return 8;
}

int CPU::RRC_C() {
	this->BC.lo = Rotate(this->BC.lo, Direction::right, false);
	Logger::LogInstruction("RRC", "C", "");
	return 8;
}

int CPU::RRC_D() {
	this->DE.hi = Rotate(this->DE.hi, Direction::right, false);
	Logger::LogInstruction("RRC", "D", "");
	return 8;
}

int CPU::RRC_E() {
	this->DE.lo = Rotate(this->DE.lo, Direction::right, false);
	Logger::LogInstruction("RRC", "E", "");
	return 8;
}

int CPU::RRC_H() {
	this->HL.hi = Rotate(this->HL.hi, Direction::right, false);
	Logger::LogInstruction("RRC", "H", "");
	return 8;
}

int CPU::RRC_L() {
	this->HL.lo = Rotate(this->HL.lo, Direction::right, false);
	Logger::LogInstruction("RRC", "L", "");
	return 8;
}

int CPU::RRC_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Rotate(value, Direction::right, false);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RRC", "(HL)", "");
	return 16;
}

int CPU::RR_A() {
	this->AF.hi = Rotate(this->AF.hi, Direction::right);
	Logger::LogInstruction("RR", "A", "");
	return 8;
}

int CPU::RR_B() {
	this->BC.hi = Rotate(this->BC.hi, Direction::right);
	Logger::LogInstruction("RR", "B", "");
	return 8;
}

int CPU::RR_C() {
	this->BC.lo = Rotate(this->BC.lo, Direction::right);
	Logger::LogInstruction("RR", "C", "");
	return 8;
}

int CPU::RR_D() {
	this->DE.hi = Rotate(this->DE.hi, Direction::right);
	Logger::LogInstruction("RR", "D", "");
	return 8;
}

int CPU::RR_E() {
	this->DE.lo = Rotate(this->DE.lo, Direction::right);
	Logger::LogInstruction("RR", "E", "");
	return 8;
}

int CPU::RR_H() {
	this->HL.hi = Rotate(this->HL.hi, Direction::right);
	Logger::LogInstruction("RR", "H", "");
	return 8;
}

int CPU::RR_L() {
	this->HL.lo = Rotate(this->HL.lo, Direction::right);
	Logger::LogInstruction("RR", "L", "");
	return 8;
}

int CPU::RR_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Rotate(value, Direction::right);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RR", "(HL)", "");
	return 16;
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

int CPU::SLA_A() {
	this->AF.hi = Shift(this->AF.hi, Direction::left);
	Logger::LogInstruction("SLA", "A", "");
	return 8;
}

int CPU::SLA_B() {
	this->BC.hi = Shift(this->BC.hi, Direction::left);
	Logger::LogInstruction("SLA", "B", "");
	return 8;
}

int CPU::SLA_C() {
	this->BC.lo = Shift(this->BC.lo, Direction::left);
	Logger::LogInstruction("SLA", "C", "");
	return 8;
}

int CPU::SLA_D() {
	this->DE.hi = Shift(this->DE.hi, Direction::left);
	Logger::LogInstruction("SLA", "D", "");
	return 8;
}

int CPU::SLA_E() {
	this->DE.lo = Shift(this->DE.lo, Direction::left);
	Logger::LogInstruction("SLA", "E", "");
	return 8;
}

int CPU::SLA_H() {
	this->HL.hi = Shift(this->HL.hi, Direction::left);
	Logger::LogInstruction("SLA", "H", "");
	return 8;
}

int CPU::SLA_L() {
	this->HL.lo = Shift(this->HL.lo, Direction::left);
	Logger::LogInstruction("SLA", "L", "");
	return 8;
}

int CPU::SLA_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Shift(value, Direction::left);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SLA", "(HL)", "");
	return 16;
}

int CPU::SRA_A() {
	this->AF.hi = Shift(this->AF.hi, Direction::right, false);
	Logger::LogInstruction("SRA", "A", "");
	return 8;
}

int CPU::SRA_B() {
	this->BC.hi = Shift(this->BC.hi, Direction::right, false);
	Logger::LogInstruction("SRA", "B", "");
	return 8;
}

int CPU::SRA_C() {
	this->BC.lo = Shift(this->BC.lo, Direction::right, false);
	Logger::LogInstruction("SRA", "C", "");
	return 8;
}

int CPU::SRA_D() {
	this->DE.hi = Shift(this->DE.hi, Direction::right, false);
	Logger::LogInstruction("SRA", "D", "");
	return 8;
}

int CPU::SRA_E() {
	this->DE.lo = Shift(this->DE.lo, Direction::right, false);
	Logger::LogInstruction("SRA", "E", "");
	return 8;
}

int CPU::SRA_H() {
	this->HL.hi = Shift(this->HL.hi, Direction::right, false);
	Logger::LogInstruction("SRA", "H", "");
	return 8;
}

int CPU::SRA_L() {
	this->HL.lo = Shift(this->HL.lo, Direction::right, false);
	Logger::LogInstruction("SRA", "L", "");
	return 8;
}

int CPU::SRA_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Shift(value, Direction::right, false);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SRA", "(HL)", "");
	return 16;
}

int CPU::SRL_A() {
	this->AF.hi = Shift(this->AF.hi, Direction::right);
	Logger::LogInstruction("SRL", "A", "");
	return 8;
}

int CPU::SRL_B() {
	this->BC.hi = Shift(this->BC.hi, Direction::right);
	Logger::LogInstruction("SRL", "B", "");
	return 8;
}

int CPU::SRL_C() {
	this->BC.lo = Shift(this->BC.lo, Direction::right);
	Logger::LogInstruction("SRL", "C", "");
	return 8;
}

int CPU::SRL_D() {
	this->DE.hi = Shift(this->DE.hi, Direction::right);
	Logger::LogInstruction("SRL", "D", "");
	return 8;
}

int CPU::SRL_E() {
	this->DE.lo = Shift(this->DE.lo, Direction::right);
	Logger::LogInstruction("SRL", "E", "");
	return 8;
}

int CPU::SRL_H() {
	this->HL.hi = Shift(this->HL.hi, Direction::right);
	Logger::LogInstruction("SRL", "H", "");
	return 8;
}

int CPU::SRL_L() {
	this->HL.lo = Shift(this->HL.lo, Direction::right);
	Logger::LogInstruction("SRL", "L", "");
	return 8;
}

int CPU::SRL_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Shift(value, Direction::right);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SRL", "(HL)", "");
	return 16;
}

int CPU::DI() {
	Logger::LogInstruction("DI", "", "");
	return 4;
}

int CPU::EI() {
	Logger::LogInstruction("EI", "", "");
	return 4;
}

