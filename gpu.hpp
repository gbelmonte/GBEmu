#include "common.hpp"
#include "SDL.h"
#include "memory.hpp"
#include "util.hpp"
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum LCDMode {
	HorizontalBlank = 0x00,
	VerticalBlank = 0x01,
	OAM = 0x02,
	VRAM = 0x03,
};

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
		BYTE scanline;
		LCDMode mode;
		bool lcdEnabled;
		bool backgroundEnabled;
		bool windowEnabled;
		bool spriteEnabled;
		bool spriteSize16;
		WORD backgroundTileMapAddress;
		WORD windowTileMapAddress;
		bool tileDataSelect;

		bool drawLine;
		bool vblank;


		LCDMode UpdateLCDMode();
		void DrawLine();
		void DrawSprites();
		BYTE getPixelColor(BYTE tileDataRow, BYTE tileDataRow2, int bitPosition, WORD paletteAddress);
		BYTE getPixelColor(WORD paletteAddress, BYTE colorValue);
};