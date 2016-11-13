#include "CPU.hpp"

using namespace std;

int main(int argc, char** argv){
	CPU cpu;
	cpu.LoadCartridge();

	bool quit = false;
	while(!quit){

		//Fetch
		BYTE opcode = cpu.Fetch();
		//cout << hex << "0x" << (int)opcode << ": " << endl;

		//DecodeExecute
		int cycles = cpu.DecodeExecute(opcode);

		cpu.UpdateScreen(cycles);
		quit = cpu.CheckInput();
	}

	return 0;
}