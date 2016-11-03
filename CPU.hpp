#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "common.hpp"
#include "memory.hpp"

using namespace std;

class CPU{

	public:
		CPU();
		~CPU();

		void LoadCartridge();
		BYTE Fetch();
		void DecodeExecute(BYTE opcode);

	private:
		Register AF;
		Register BC;
		Register DE;
		Register HL;
		
		Register SP;
		Register PC;

		Flags flags;

		Memory memory;

		int (CPU::*instructions[300])();
		int (CPU::*instructions_cb[300])();

		//instructions

		//load immediates
		int LD_A_n();
		int LD_B_n();
		int LD_C_n();
		int LD_D_n();
		int LD_E_n();
		int LD_H_n();
		int LD_L_n();

		int LD_A_A();
		int LD_A_B();
		int LD_A_C();
		int LD_A_D();
		int LD_A_E();
		int LD_A_H();
		int LD_A_L();
		int LD_A_BC();
		int LD_A_DE();
		int LD_A_HL();
		int LD_A_nn();

		int LD_HL_A();
		int LD_C_A();
		int LD_FF00_n_A();

		//Load Dec
		int LDD_HL_A();

		//16 bit loads
		int LD_BC_nn();
		int LD_DE_nn();
		int LD_HL_nn();
		int LD_SP_nn();

		//XOR
		int XOR_A();

		//Jumps
		int JR_NZ();

		//Increments
		BYTE RegInc(BYTE value);
		int INC_A();
		int INC_B();
		int INC_C();
		int INC_D();
		int INC_E();
		int INC_H();
		int INC_L();
		int INC_HL();

		//Bit
		void TestBit(BYTE byte, BYTE mask);

		int BIT_0_A();
		int BIT_1_A();
		int BIT_2_A();
		int BIT_3_A();
		int BIT_4_A();
		int BIT_5_A();
		int BIT_6_A();
		int BIT_7_A();

		int BIT_0_B();
		int BIT_1_B();
		int BIT_2_B();
		int BIT_3_B();
		int BIT_4_B();
		int BIT_5_B();
		int BIT_6_B();
		int BIT_7_B();

		int BIT_0_C();
		int BIT_1_C();
		int BIT_2_C();
		int BIT_3_C();
		int BIT_4_C();
		int BIT_5_C();
		int BIT_6_C();
		int BIT_7_C();

		int BIT_0_D();
		int BIT_1_D();
		int BIT_2_D();
		int BIT_3_D();
		int BIT_4_D();
		int BIT_5_D();
		int BIT_6_D();
		int BIT_7_D();

		int BIT_0_E();
		int BIT_1_E();
		int BIT_2_E();
		int BIT_3_E();
		int BIT_4_E();
		int BIT_5_E();
		int BIT_6_E();
		int BIT_7_E();

		int BIT_0_H();
		int BIT_1_H();
		int BIT_2_H();
		int BIT_3_H();
		int BIT_4_H();
		int BIT_5_H();
		int BIT_6_H();
		int BIT_7_H();

		int BIT_0_L();
		int BIT_1_L();
		int BIT_2_L();
		int BIT_3_L();
		int BIT_4_L();
		int BIT_5_L();
		int BIT_6_L();
		int BIT_7_L();

		int BIT_0_HL();
		int BIT_1_HL();
		int BIT_2_HL();
		int BIT_3_HL();
		int BIT_4_HL();
		int BIT_5_HL();
		int BIT_6_HL();
		int BIT_7_HL();
};