#ifndef COLLISIONES
#define COLLISIONES

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

///// Estructuras

typedef enum {
	LAYER_NONE,
	LAYER_PLAYER,
	LAYER_ENEMY,
	LAYER_ENEMY_INVINCIBLE
} Layer;

typedef struct collision_box_st{
	float x, y, w, h;
	Layer type;
} CollisionBox;

///// Funciones

void collider_draw(SDL_Renderer *renderer, CollisionBox *collider, SDL_Color *color);

void collisions_update(CollisionBox **colliders);

#endif // COLLISIONES
