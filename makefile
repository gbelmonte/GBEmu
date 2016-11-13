all:
	g++ -std=c++11 gbemu.cpp CPU.cpp memory.cpp gpu.cpp -w -lSDL2 -I/usr/include/SDL2 -o gbemu