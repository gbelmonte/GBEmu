#include "common.hpp"
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class GPU {
	public:
		GPU();
		~GPU();
		BYTE screen[160][144];
		void UpdateScreen();		

	private:
		SDL_Window * window; 
		SDL_Renderer * renderer;
};