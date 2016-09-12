#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;
typedef char SIGNED_BYTE;
typedef unsigned short WORD;
typedef short SIGNED_WORD;

#include "cpu_state.h"

using namespace std;

void init(cpu_state *state){
	
	//Init Registers
	state->SP.reg = 0xFFFE;
	state->PC.reg = 0x100;

	state->AF.reg = 0x01B0;
	state->BC.reg = 0x0013;
	state->DE.reg = 0x00D8;
	state->HL.reg = 0x014D;

	//Init Memory
	state->Rom[0xFF05] = 0x00;
	state->Rom[0xFF06] = 0x00;
	state->Rom[0xFF07] = 0x00;
	state->Rom[0xFF10] = 0x80;
	state->Rom[0xFF11] = 0xBF;
	state->Rom[0xFF12] = 0xF3;
	state->Rom[0xFF14] = 0xBF;
	state->Rom[0xFF16] = 0x3F;
	state->Rom[0xFF17] = 0x00;
	state->Rom[0xFF19] = 0xBF;
	state->Rom[0xFF1A] = 0x7F;
	state->Rom[0xFF1B] = 0xFF;
	state->Rom[0xFF1C] = 0x9F;
	state->Rom[0xFF1E] = 0xBF;
	state->Rom[0xFF20] = 0xFF;
	state->Rom[0xFF21] = 0x00;
	state->Rom[0xFF22] = 0x00;
	state->Rom[0xFF23] = 0xBF;
	state->Rom[0xFF24] = 0x77;
	state->Rom[0xFF25] = 0xF3;
	state->Rom[0xFF26] = 0xF1;
	state->Rom[0xFF40] = 0x91;
	state->Rom[0xFF42] = 0x00;
	state->Rom[0xFF43] = 0x00;
	state->Rom[0xFF45] = 0x00;
	state->Rom[0xFF47] = 0xFC;
	state->Rom[0xFF48] = 0xFF;
	state->Rom[0xFF49] = 0xFF;
	state->Rom[0xFF4A] = 0x00;
	state->Rom[0xFF4B] = 0x00;
	state->Rom[0xFFFF] = 0x00;
}

bool readCartridge(BYTE * cartridgeMemory){
	size_t result;

	FILE * pFile = fopen("DrMario.gb", "rb");
	if (pFile == NULL) {
		cout << "Could not find file";
		return 0;
	}

	result = fread(cartridgeMemory, 1, 200000, pFile);

	return 1;
}


int main(int argc, char** argv){

	cpu_state state;

	if(!readCartridge(state.Cartridge)) {
		return 0;
	}
	init(&state);

	//read game title
	// for (int i = 0x134; i<0x142; i++) {

	// 	cout << static_cast<char>(state.Cartridge[i]);
	// }
	cout << std::to_string(state.Cartridge[0x147]);
	return 0;
}