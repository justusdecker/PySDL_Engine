#include <SDL3/SDL.h>
#include <stdio.h>
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL; 

char WSDL_InitializeWindow(
	char* window_title,
	unsigned int window_width, 
	unsigned int window_height) {
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf(SDL_GetError());
		return 0;
	}
	
	// Creating the SDL Window
	window = SDL_CreateWindow(
			window_title, 
			(int)window_width,
			(int)window_height,
			SDL_WINDOW_HIGH_PIXEL_DENSITY
			);

	// Cannot create window
	if (window == NULL) {
		printf(SDL_GetError());
		return 0;
	}

	renderer = SDL_CreateRenderer(window, NULL);
	
	// Cannot create window
	if (!renderer) {
		printf(SDL_GetError());
		return 0;
	}
	return 1;
}