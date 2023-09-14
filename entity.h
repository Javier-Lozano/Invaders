#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SDL2/SDL_rect.h>
#include "init.h"
#include "input.h"

///// MACROS

#define CHECK_BETWEEN_RANGE(val, min, max) (val < min) || (val > max)

// Player

#define PLAYER_W 10
#define PLAYER_H 8
#define PLAYER_X (DISPLAY_REAL_WIDTH / 2)
#define PLAYER_Y (DISPLAY_REAL_HEIGHT - 32)
#define PLAYER_SPEED 1.75f

// Bulllets

#define BULLET_W 4
#define BULLET_H 8
#define BULLET_SPEED 8
#define BULLET_INV_W 6

///// Estructuras

enum EntityType {
	TYPE_NONE,
	TYPE_PLAYER,
	TYPE_ENEMY_SQUID,
	TYPE_ENEMY_GAZER,
	TYPE_ENEMY_SKULL,
	TYPE_ENEMY_FACE,
	TYPE_BULLET_PLAYER,
	TYPE_BULLET_ENEMY,
	TYPE_BULLET_ENEMY_SKULL,
	TYPE_BLOCK,
	TYPE_INVUL,
	TYPE_DESTROYED
};

typedef struct sprite_st{} Sprite;

typedef struct entity_st {
	Sprite *sprite;
	SDL_FRect collider;
	SDL_FPoint speed;
	Uint8 type;
} Entity;

///// Funciones

// Entity
Entity *entity_create(Sprite *sprite, SDL_FRect *collider, SDL_FPoint *speed, Uint8 type);
void entity_destroy(Entity *entity);

// Player
Entity *player_create();
void player_update(Entity *player, Input *input);

// Bullets
Entity *bullet_create(float x, float y, Uint8 type);
void bullet_update(Entity *bullet);

#endif // _ENTITY_H_
