#include <SDL3/SDL.h>
#include <stdio.h>
#include "./constants.h"
#include <windows.h>
#include <psapi.h>
#include <stdio.h>
PROCESS_MEMORY_COUNTERS_EX pmc;

unsigned int WSDL_GetRamUsage(void) {
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS* ) &pmc, sizeof(pmc))) {
        return (unsigned int)pmc.WorkingSetSize / 1024;
    }
    return 0;
}


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL; 

float WSDL_delta_time;
bool WSDL_is_running = true;
int WSDL_last_frame_time = 0;
char memory_info_puffer[24];

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

void WSDL_Update() {


	// Waste some time until the next frame should be drawn!
	int ticks = SDL_GetTicks();
	int time_to_wait = FRAME_TARGET_TIME - (ticks - WSDL_last_frame_time);
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}
	WSDL_delta_time = (ticks - WSDL_last_frame_time) / 1000.0f;
	
	WSDL_last_frame_time = ticks;

}

void WSDL_CheckEvents(void) {
	SDL_Event windowEvent;
	if ( SDL_PollEvent( &windowEvent ) ) {
		if ( SDL_EVENT_QUIT == windowEvent.type ) {
			WSDL_is_running = false;
		}
		
	}
		
}

void WSDL_RenderDebug(void) {
	SDL_SetRenderDrawColor(renderer, 24,24,24,255);
	SDL_RenderClear(renderer);
	
	snprintf(memory_info_puffer, sizeof(memory_info_puffer), "%d KB", WSDL_GetRamUsage());
	SDL_SetRenderDrawColor(renderer, 255,255,255,255);
	SDL_SetRenderScale(renderer, 4.0f,4.0f);
	SDL_RenderDebugText(renderer, 0,0,memory_info_puffer);
	SDL_SetRenderScale(renderer, 1.0f,1.0f);
	// Drawing objects
	SDL_RenderPresent(renderer);
	
}