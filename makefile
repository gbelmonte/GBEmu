all:
	g++ -std=c++11 gbemu.cpp cpu.cpp memory.cpp gpu.cpp logger.cpp -w -lSDL2 -I/usr/include/SDL2 -o gbemu