#ifndef COMMON_HPP
#define COMMON_HPP

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

const BYTE BIT7 = 0x80;
const BYTE BIT6 = 0x40;
const BYTE BIT5 = 0x20;
const BYTE BIT4 = 0x10;
const BYTE BIT3 = 0x08;
const BYTE BIT2 = 0x04;
const BYTE BIT1 = 0x02;
const BYTE BIT0 = 0x01;

#endif