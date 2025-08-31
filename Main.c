#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include "./src/constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL; 

struct Entity {
	float x;
	float y;
	float w;
	float h;
};

struct PlayerMovement {
	int moving_x;
	int moving_y;
} PMove;

int last_frame_time = 0;
float delta_time;
bool is_running = true;

struct Entity Ball;
struct Entity Canvas;

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
	Ball.x = 16;
	Ball.y = 16;
	Ball.w = 32;
	Ball.h = 48;
	Canvas.x = 0;
	Canvas.y = 0;
	Canvas.w = (float)WINDOW_WIDTH;
	Canvas.h = (float)WINDOW_HEIGHT;
}


// Prevents object a from colliding with object b
// This is not an overlapping check!
bool collide(struct Entity* a, struct Entity* b) {
	if (a->x < b->x) a->x = b->x;
	if (a->y < b->x) a->y = b->x;
	if (a->x + a->w > b->w) a->x = b->w - a->w;
	if (a->y + a->h > b->h) a->y = b->h - a->h;
}

void move_ball(int x, int y) {
	// Move ball over the display
	Ball.x += x * delta_time;
	Ball.y += y * delta_time;
	collide(&Ball,&Canvas);
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

	move_ball(PMove.moving_x * 100,PMove.moving_y * 100);

}

void render(void) {
	SDL_SetRenderDrawColor(renderer, 24,24,24,255);
	SDL_RenderClear(renderer);
	
	
	
	// Drawing Rectangle
	SDL_SetRenderDrawColor(renderer, 48,48,48,255);
	SDL_FRect ball_rect = { Ball.x,Ball.y,Ball.w,Ball.h };
	SDL_RenderFillRect(renderer, &ball_rect);

	// Drawing objects
	SDL_RenderPresent(renderer);
	
}

void destroy_window(void) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void check_events(void) {
	SDL_Event windowEvent;
	if ( SDL_PollEvent( &windowEvent ) ) {
		if ( SDL_EVENT_QUIT == windowEvent.type ) {
			is_running = false;
		}
		if ( SDL_EVENT_KEY_DOWN == windowEvent.type) {
			int key = (int)windowEvent.key.key;
			if (key == SDLK_S) PMove.moving_y = 1;
			else if (key == SDLK_W) PMove.moving_y = -1;
			if (key == SDLK_A) PMove.moving_x = -1;
			else if (key == SDLK_D) PMove.moving_x = 1;
		}
		if ( SDL_EVENT_KEY_UP == windowEvent.type) {
			int key = (int)windowEvent.key.key;
			if (key == SDLK_S || key == SDLK_W) PMove.moving_y = 0;
			if (key == SDLK_A || key == SDLK_D) PMove.moving_x = 0;

		}
		
	}
		
}



int main() {
	
	printf("Start App...");
	PMove.moving_x = 0;
	PMove.moving_y = 0;
	setup();
	initialize_window();
	
	while ( is_running ) {
		update();
		render();
		check_events();
	}
	destroy_window();
	return 0;
}
