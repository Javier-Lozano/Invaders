#ifndef PLAYER_H
#define PLAYER_H

#include "input.h"
//#include "collision.h"
//#include "bullet.h"

///// MACROS

#define ENTITY_W 16
#define ENTITY_H 16
#define PLAYER_SPEED 1.75f

///// Estructuras

typedef struct collision_box_st {
	float x, y, w, h;
} Collision_Box;

typedef struct bullet_st {
	Collision_Box collision_box;
	float speed;
	int type;
	int is_active;
} Bullet;

typedef struct player_st {
	float x, y;
	float speed;
	//Collision_Box *collision_box;
} Player;

///// Funciones

Player *player_create(int x, int y, int w, int h, int speed);
void player_destroy(Player *player);

void player_update(Player *player);
void player_draw(Player *player, SDL_Renderer * renderer);

#endif // PLAYER_H
