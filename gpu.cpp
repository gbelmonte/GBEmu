#include "gpu.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

GPU::GPU() {

	window = NULL;  
	renderer = NULL;
	for (int x = 0; x < 160; x++) {
		for (int y = 0; y < 144; y++) {
			screen[x][y] = 0;
		}
	}

	//Initialize SDL 
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) { 
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
	}
	else {
		window = SDL_CreateWindow( "GBEmu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ); 
		
		if( window == NULL) { 
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl; 
		}
		else { 
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			//Fill the surface white 
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				for (int y = 0; y < SCREEN_HEIGHT; y++) {
					SDL_RenderDrawPoint(renderer, x, y);
				}
			}

			SDL_RenderPresent(renderer);
		}
	}
}

GPU::~GPU() {
	//Destroy window 
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window ); 
	 
	//Quit SDL subsystems 
	SDL_Quit();
}

void GPU::UpdateScreen() {
	
	for (int y = 0; y < 144; y++) {
		for(int x = 0; x < 160; x++) {

			switch(screen[x][y]) {
				case 0:	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); break;
				case 1:	SDL_SetRenderDrawColor(renderer, 0xD3, 0xD3, 0xD3, 0xFF); break;
				case 2:	SDL_SetRenderDrawColor(renderer, 0xA9, 0xA9, 0xA9, 0xFF); break;
				case 3:	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); break;
			}
			
			SDL_RenderDrawPoint(renderer, x, y);				
		}
	}

	SDL_RenderPresent(renderer);
}