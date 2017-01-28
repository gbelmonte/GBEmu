#include "CPU.hpp"

using namespace std;

int main(int argc, char** argv){
	Logger::InitLogger(false);

	CPU cpu;
	cpu.LoadCartridge(argv[1]);
	cpu.Run();

	return 0;
}

