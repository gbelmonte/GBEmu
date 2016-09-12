union Register{
	WORD reg;
	struct {
		char lo;
		char hi;
	};
};

struct Flags{
	unsigned z:1; //Zero Flag
	unsigned n:1; //Subtract Flag
	unsigned h:1; //Half Carry Flag
	unsigned c:1; //Carry Flag
};

struct cpu_state {
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