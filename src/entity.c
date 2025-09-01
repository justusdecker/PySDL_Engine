#include <SDL3/SDL.h>
struct Entity {
	float x;
	float y;
	float w;
	float h;
	SDL_Texture* texture;
	
};

void ENTITY_LoadBitmap(char* filepath) {
	SDL_asprintf(&filepath, "%s",SDL_GetBasePath());
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
