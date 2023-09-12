#include "collisions.h"

void collider_draw(SDL_Renderer *renderer, CollisionBox *collider, SDL_Color *color)
{
	SDL_Rect r = {
		collider->x,
		collider->y,
		collider->w,
		collider->h
	};

	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	SDL_RenderDrawRect(renderer, &r);
}

void collisions_update(CollisionBox **colliders)
{
	
}