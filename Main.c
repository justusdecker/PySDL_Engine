#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include "./src/constants.h"
#include "./src/log.h"
#include "./src/entity.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL; 

struct PlayerMovement {
	char w;
	char s;
	char a;
	char d;
} PMove;

int last_frame_time = 0;
float delta_time;
bool is_running = true;

struct Entity Ball;
struct Entity Canvas;

SDL_Texture *player_texture = NULL;

int initialize_window(void) {
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		LOG_WRITE("Error initializing SDL Video",LOG_ERROR,LOG_TYPES.ERROR);
		return 0;
	}
	
	// Creating the SDL Window
	// Define the parameters in the constants.h
	
	window = SDL_CreateWindow(
			"PySDL", 
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_HIGH_PIXEL_DENSITY
			);
		
	if (window == NULL) {
		LOG_WRITE("Error creating SDL Window",LOG_ERROR,LOG_TYPES.ERROR);
		return 0;
	}

	renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer) {
		LOG_WRITE("Error creating SDL Renderer",LOG_ERROR,LOG_TYPES.ERROR);
		return 0;
	}
	LOG_WRITE("Initialized SDL successfully",LOG_INFO,LOG_TYPES.INFO);
	return 1;
}

void setup(void) {
	Ball.x = 16;
	Ball.y = 16;
	Ball.w = 32;
	Ball.h = 32;
	Canvas.x = 0;
	Canvas.y = 0;
	Canvas.w = (float)WINDOW_WIDTH;
	Canvas.h = (float)WINDOW_HEIGHT;
	PMove.w = 0;
	PMove.a = 0;
	PMove.s = 0;
	PMove.d = 0;
}

void move_ball(int x, int y) {
	// Move ball over the display
	Ball.x += x * delta_time;
	Ball.y += y * delta_time;
	ENTITY_KeepInside(&Ball,&Canvas);
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

	move_ball((PMove.a + PMove.d) * 100,(PMove.w + PMove.s) * 100);

}

void render(void) {
	SDL_SetRenderDrawColor(renderer, 24,24,24,255);
	SDL_RenderClear(renderer);
	
	
	
	// Drawing Rectangle
	//SDL_SetRenderDrawColor(renderer, 48,48,48,255);
	SDL_FRect ball_rect = { Ball.x,Ball.y,Ball.w,Ball.h };
	//SDL_RenderFillRect(renderer, &ball_rect);

	SDL_RenderTexture(renderer, player_texture, NULL, &ball_rect);
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
			if (key == SDLK_S) PMove.s = 1;
			if (key == SDLK_W) PMove.w = -1;
			if (key == SDLK_A) PMove.a = -1;
			if (key == SDLK_D) PMove.d = 1;
		}
		if ( SDL_EVENT_KEY_UP == windowEvent.type) {
			int key = (int)windowEvent.key.key;

			if (key == SDLK_S) PMove.s = 0;
			if (key == SDLK_W) PMove.w = 0;
			if (key == SDLK_A) PMove.a = 0;
			if (key == SDLK_D) PMove.d = 0;

		}
		
	}
		
}

int main() {
	LOG_WRITE("Start App...",LOG_INFO,LOG_TYPES.INFO);
	setup();
	initialize_window();
	player_texture = ENTITY_LoadBitmap(renderer, "data\\img\\figure.bmp");
	while ( is_running ) {
		update();
		render();
		check_events();
		//printf("c:%d\n",collision(&Ball,&Canvas));
	}
	destroy_window();
	return 0;
}
