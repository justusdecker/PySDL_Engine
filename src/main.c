#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL; 


int initialize_window(void) {
	
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return 0;
	}
	

	// Creating the SDL Window
	// Define the parameters in the constants.h
	window = SDL_CreateWindow(
			NULL, 
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800,
			600,
			SDL_WINDOW_BORDERLESS
			);

	if (!window) {
		fprintf(stderr, "Error creating SDL Window.\n");
		return 0;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		fprintf(stderr, "Error creating SDL Renderer.\n");
		return 0;
	}

	return 1;
}

int main() {
	printf("Start App...");
	initialize_window();
	return STATUS_OK;
}
