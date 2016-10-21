#include "CPU.hpp"

using namespace std;

int main(int argc, char** argv){
	string input;
	int batchSize = 10;
	int stepNumber = 0;
	CPU cpu;
	cpu.LoadCartridge();

	while(1){

		//Fetch
		BYTE opcode = cpu.Fetch();
		cout << hex << "0x" << (int)opcode << endl;

		//DecodeExecute
		cpu.DecodeExecute(opcode);

		//ExecuteInterrupt

		//This is just for debugging opcodes, enter input to execute next batch of instructions
		stepNumber++;
		if (stepNumber >= batchSize) {
			cin >> input;
			stepNumber = 0;
		}
	}

	
	return 0;
}