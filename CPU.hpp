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
		BYTE lo;
		BYTE hi;
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
		void Decode();
		void Execute();

	private:
		Register AF;
		Register BC;
		Register DE;
		Register HL;
		
		Register SP;
		Register PC;

		Flags flags;

		BYTE Rom[0x10000];
		BYTE Cartridge[0x200000];
};