#include "util.hpp"
#include "common.hpp"

BYTE GetBit(BYTE value, int bitPos) {
	
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

bool IsBitSet(BYTE value, BYTE bitMask) {
	if ((value & bitMask) > 0) {
		return true;
	}

	return false;
}
