#ifndef COMMON_HPP
#define COMMON_HPP

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

#endif