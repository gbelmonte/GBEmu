#include "common.hpp"
#include "SDL.h"
#include "memory.hpp"
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class GPU {
	public:
		GPU(Memory *memory);
		~GPU();
		BYTE screen[160][144];
		void RenderScreen();
		void UpdateScreen(int cycles);

	private:
		SDL_Window *window; 
		SDL_Renderer *renderer;

		Memory *memory;
		int cycleCounter;

		void UpdateLCDMode();
		void DrawLine();
		void DrawSprites();
		BYTE getPixelColor(BYTE tileDataRow, BYTE tileDataRow2, int bitPosition, WORD paletteAddress);
		BYTE getPixelColor(WORD paletteAddress, BYTE colorValue);
		BYTE GetBit(BYTE value, int bitPos);
};