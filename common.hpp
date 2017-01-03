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

const BYTE BIT7 = 0x80;
const BYTE BIT6 = 0x40;
const BYTE BIT5 = 0x20;
const BYTE BIT4 = 0x10;
const BYTE BIT3 = 0x08;
const BYTE BIT2 = 0x04;
const BYTE BIT1 = 0x02;
const BYTE BIT0 = 0x01;

enum Direction {
	right,
	left
};

enum Flag {
	z,
	n,
	h,
	c
};

enum Interrupt {
	None = 0x00,
	VBlank = BIT0,
	LCDC = BIT1,
	TimerOverflow = BIT2,
	SerialTransfer = BIT3,
	Transition = BIT4
};

#endif