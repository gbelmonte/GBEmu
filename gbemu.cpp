#include "CPU.hpp"

using namespace std;

int main(int argc, char** argv){

	CPU cpu;
	cpu.LoadCartridge();

	while(1){

		//Fetch
		BYTE opcode = cpu.Fetch();
		cout << hex << "0x" << (int)opcode << endl;

		//Decode

		//Execute

		//ExecuteInterrupt
	}

	
	return 0;
}