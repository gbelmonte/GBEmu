#include "logger.hpp"
using namespace std;

Logger::Logger() {

}

Logger::~Logger() {

}

bool Logger::logEnabled = false;

void Logger::InitLogger(bool enable = false) {
	logEnabled = enable;

	if (enable == true) {
		freopen("log.txt", "w", stdout);
	}
}

void Logger::LogOpcode(BYTE opcode) {
	if (logEnabled == true) {
		cout << hex << "0x" << (int)opcode << " =";
	}
}

void Logger::LogPC(WORD pc) {
	if (logEnabled == true) {
		cout << hex << "0x" << (int)pc << ": ";
	}
}

void Logger::LogInstruction(string name, string dParam, string rParam) {
	if (logEnabled == true) {
		cout << hex << " " << name << " " << dParam << ", " << rParam << endl;
	}
}

void Logger::Log(string log) {
	if (logEnabled == true) {
		cout << hex << log << endl;
	}
}