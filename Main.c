#include <stdio.h>
#include <SDL3/SDL.h>
#include "./src/constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL; 

struct ball {
	float x;
	float y;
	float w;
	float h;
} ball;


int initialize_window(void) {
	
	SDL_Init(SDL_INIT_VIDEO);
	
	// Creating the SDL Window
	// Define the parameters in the constants.h
	
	window = SDL_CreateWindow(
			NULL, 
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_HIGH_PIXEL_DENSITY
			);
		
	if (window == NULL) {
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

void setup(void) {
	ball.x = 16;
	ball.y = 16;
	ball.w = 32;
	ball.h = 48;
}

void update(void) {

}

void render(void) {
	SDL_SetRenderDrawColor(renderer, 24,24,24,255);
	SDL_RenderClear(renderer);
	
	
	
	// Drawing Rectangle
	SDL_SetRenderDrawColor(renderer, 48,48,48,255);
	SDL_FRect ball_rect = { ball.x,ball.y,ball.w,ball.h };
	SDL_RenderFillRect(renderer, &ball_rect);

	// Drawing objects
	SDL_RenderPresent(renderer);
	
}

void destroy_window(void) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



int main() {
	printf("Start App...");
	setup();
	initialize_window();
	SDL_Event windowEvent;
	while ( true ) {

		update();
		render();

		if ( SDL_PollEvent( &windowEvent ) ) {
			if ( SDL_EVENT_QUIT == windowEvent.type ) {
				break;
			}
		}
	}
	destroy_window();
	return 0;
}
