#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef unsigned char BYTE;
typedef char SIGNED_BYTE;
typedef unsigned short WORD;
typedef short SIGNED_WORD;

union Register{
	WORD reg;
	struct {
		BYTE hi;
		BYTE lo;
	};
};

struct Flags{
	unsigned z:1; //Zero Flag
	unsigned n:1; //Subtract Flag
	unsigned h:1; //Half Carry Flag
	unsigned c:1; //Carry Flag
};

class CPU{

	public:
		CPU();
		~CPU();

		bool LoadCartridge();
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

		int (CPU::*instructions[300])();

		BYTE Rom[0x10000];
		BYTE Cartridge[0x200000];

		//Opcode helpers
		void loadByte(BYTE * dest, BYTE imm);
		void loadByte(BYTE * dest, BYTE * src);

		WORD readWord(int location);

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

};