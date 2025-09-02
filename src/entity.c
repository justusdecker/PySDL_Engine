#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdio.h>
struct Entity {
	float x;
	float y;
	float w;
	float h;
	SDL_Texture* texture;
	
};

SDL_Texture* ENTITY_LoadBitmap(SDL_Renderer *renderer, char* filepath) {
	char* fp;
	SDL_asprintf(&fp, "%s%s",SDL_GetBasePath(),filepath);
	SDL_Surface *surface = SDL_LoadBMP(fp);
	if (!surface) {
		printf("Cannot load surface\n%s",fp);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		printf("Cannot create texture\n");
		SDL_free(fp);
	}
	SDL_DestroySurface(surface);
	
	
	return texture;
}

void ENTITY_KeepInside(struct Entity* a, struct Entity* b) {
	if (a->x < b->x) a->x = b->x;
	if (a->y < b->y) a->y = b->y;
	if (a->x + a->w > b->w) a->x = b->w - a->w;
	if (a->y + a->h > b->h) a->y = b->h - a->h;
}

bool ENTITY_GetCollision(struct Entity* a, struct Entity* b) {
	return a->x > b->x && a->y > b->y && a->x + a->w < b->w && a->y + a->h < b->h;
}
