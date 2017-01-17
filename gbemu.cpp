#include "CPU.hpp"

using namespace std;

int main(int argc, char** argv){
	CPU cpu;
	cpu.LoadCartridge(argv[1]);
	Logger::InitLogger(false);

	bool quit = false;
	while(!quit){

		//Fetch
		BYTE opcode = cpu.Fetch();
		Logger::LogOpcode(opcode);

		//DecodeExecute
		int cycles = cpu.DecodeExecute(opcode);

		cpu.UpdateScreen(cycles);
		cpu.UpdateTimers(cycles);

		quit = cpu.CheckInput();
		
		cpu.HandleInterrupt();
	}

	return 0;
}