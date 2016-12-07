#include "CPU.hpp"

using namespace std;

int main(int argc, char** argv){
	CPU cpu;
	cpu.LoadCartridge();
	Logger::InitLogger(true);

	bool quit = false;
	while(!quit){

		//Fetch
		BYTE opcode = cpu.Fetch();
		Logger::LogOpcode(opcode);

		//DecodeExecute
		int cycles = cpu.DecodeExecute(opcode);

		cpu.UpdateScreen(cycles);
		quit = cpu.CheckInput();
	}

	return 0;
}