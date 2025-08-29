#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include "./src/constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL; 

struct ball {
	float x;
	float y;
	float w;
	float h;
} ball;

int last_frame_time = 0;
float delta_time;

int initialize_window(void) {
	
	SDL_Init(SDL_INIT_VIDEO);
	
	// Creating the SDL Window
	// Define the parameters in the constants.h
	
	window = SDL_CreateWindow(
			"PySDL", 
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

void update() {


	// Waste some time until the next frame should be drawn!
	int ticks = SDL_GetTicks();
	int time_to_wait = FRAME_TARGET_TIME - (ticks - last_frame_time);
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}
	delta_time = (ticks - last_frame_time) / 1000.0f;
	
	last_frame_time = ticks;
}

void move_ball(int x, int y) {
	// Move ball over the display
	ball.x += x * delta_time;
	ball.y += y * delta_time;

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
	int moving_x = 0;
	int moving_y = 0;
	SDL_Event windowEvent;
	while ( true ) {

		update();

		move_ball(moving_x * 100,moving_y * 100);
	
		render();

		if ( SDL_PollEvent( &windowEvent ) ) {
			if ( SDL_EVENT_QUIT == windowEvent.type ) {
				break;
			}
			if ( SDL_EVENT_KEY_DOWN == windowEvent.type) {
				
				int key = (int)windowEvent.key.key;

				if (key == SDLK_S) {
					
					moving_y = 1;
				}
				else if (key == SDLK_W) {
					moving_y = -1;
				}
				if (key == SDLK_A) {
					moving_x = -1;
				}
				else if (key == SDLK_D) {
					moving_x = 1;
				}	
			}
			if ( SDL_EVENT_KEY_UP == windowEvent.type) {
				
				int key = (int)windowEvent.key.key;

				if (key == SDLK_S) {
					
					moving_y = 0;
				}
				else if (key == SDLK_W) {
					moving_y = 0;
				}
				if (key == SDLK_A) {
					moving_x = 0;
				}
				else if (key == SDLK_D) {
					moving_x = 0;
				}	
			}
			
		}
		
		
		
	}
	destroy_window();
	return 0;
}
