#include "common.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

// Cartridge 0 to 0x7FFF 32KB
// Video Ram 0x8000 to 0x9FFF 8KB
// External Ram 0xA000 to 0xBFFF 8KB
// Work Ram 0xC000 to 0xDFFF 8KB
/* Copy of Work Ram 0xE000 to 0xFFFF 8KB
		OAM Sprite Attribute Table 0xFE00 to 0xFE9F
		Not Used 0xFEA0 to 0xFEFF
		Devices/Timers memory map 0xFF00 to 0xFF7F
		High Ram 0xFF80 to 0xFFFE
		Interrupt Switch 0xFFFF
*/

enum CartridgeType {
	Rom,
	Rom_MBC1
};

class Memory {
	public:
		Memory();

		BYTE readByte(WORD address);
		WORD readWord(WORD address);

		void writeByte(WORD address, BYTE value);
		void writeWord(WORD address, WORD value);

		bool LoadCartridge();

	private:
		BYTE Rom[200000];
		BYTE Ram[200000];
		BYTE Cartridge[200000];

		CartridgeType type;
		bool RomMode;
		bool RamEnabled;
		int RomBank;
		int RamBank;
};