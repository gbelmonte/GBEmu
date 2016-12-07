#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "common.hpp"
#include <string.h>
using namespace std;

class Logger {
	public:
		Logger();
		~Logger();
		static void InitLogger(bool enable);	
		static void LogOpcode(BYTE opcode);
		static void LogPC(WORD pc);
		static void LogInstruction(string name, string dParam, string rParam);
		static void Log(string log);

	private:
		static bool logEnabled;
};

#endif