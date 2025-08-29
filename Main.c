#include <stdio.h>
#include <SDL3/SDL.h>
#include "./src/constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL; 


int initialize_window(void) {
	
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return 0;
	}
	

	// Creating the SDL Window
	// Define the parameters in the constants.h
	window = SDL_CreateWindow(
			NULL, 
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_BORDERLESS
			);

	if (!window) {
		fprintf(stderr, "Error creating SDL Window.\n");
		return 0;
	}

	renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer) {
		fprintf(stderr, "Error creating SDL Renderer.\n");
		return 0;
	}

	return 1;
}

int main() {
	printf("Start App...");
	initialize_window();
	return 0;
}
