struct Entity {
	float x;
	float y;
	float w;
	float h;
};
// Prevents object a from leaving object b x,y,w,h
// In other words it keep it in bounds
// This is not an overlapping check!
void ENTITY_KeepInside(struct Entity* a, struct Entity* b);

bool ENTITY_GetCollision(struct Entity* a, struct Entity* b);

SDL_Texture ENTITY_LoadBitmap(SDL_Renderer *renderer, char* filepath)