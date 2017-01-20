#include "CPU.hpp"

using namespace std;

Uint32 ExecuteFrame(Uint32 interval, void *param);

int main(int argc, char** argv){
	CPU cpu;
	cpu.LoadCartridge(argv[1]);
	Logger::InitLogger(false);

	if( SDL_Init( SDL_INIT_TIMER ) < 0 ) { 
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
	}
	SDL_TimerID timerID = SDL_AddTimer(16, ExecuteFrame, &cpu);

	while(cpu.IsOn()) {

	}

	SDL_RemoveTimer(timerID);
	SDL_Quit();

	return 0;
}

Uint32 ExecuteFrame(Uint32 interval, void *param) {
	CPU* cpu = (CPU*) param;

	int cyclesThisFrame = 0;
	while (cyclesThisFrame < 69905) {

		//Fetch
		BYTE opcode = cpu->Fetch();
		Logger::LogOpcode(opcode);

		//DecodeExecute
		int cycles = cpu->DecodeExecute(opcode);

		cpu->UpdateScreen(cycles);
		cpu->UpdateTimers(cycles);

		cpu->CheckInput();
			
		cpu->HandleInterrupt();

		cyclesThisFrame += cycles;
	}

	cpu->RenderScreen();

	return interval;
}