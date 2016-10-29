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
		int LD_B_n();
		int LD_C_n();
		int LD_D_n();
		int LD_E_n();
		int LD_H_n();
		int LD_L_n();

		//Load Dec
		int LDD_HL_A();

		//16 bit loads
		int LD_SP_nn();
		int LD_HL_nn();

		//XOR
		int XOR_A();

		//Jumps
		int JR_NZ();

		//Bit
		void TestBit(BYTE byte, BYTE mask);

		int BIT_7_H();
};