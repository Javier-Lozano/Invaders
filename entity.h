#ifndef ENTITY_H
#define ENTITY_H

#include "init.h"
#include "input.h"
#include "collisions.h"

///// MACROS

// Player

#define PLAYER_WIDTH 10
#define PLAYER_HEIGHT 8
#define PLAYER_START_X (DISPLAY_REAL_WIDTH / 2)
#define PLAYER_START_Y (DISPLAY_REAL_HEIGHT - 32)
#define PLAYER_SPEED 1.75f

///// Estructuras

typedef struct entity_st {
        CollisionBox collider;
	float x_speed, y_speed;
        //Sprite *sprite;
	int delete_flag;
} Entity;

///// Funciones

// Entity
Entity *entity_create(CollisionBox collider /*, Sprite *sprites */);
void entity_destroy(Entity *entity);
//void entity_draw(Entity *entity);

// Player
Entity *player_create();
void player_update(Entity *player, Input *input, Entity **bullets);

// Bullets
Entity *bullet_create(float x, float y, Layer type);
void bullet_update(Entity *bullet);

#endif // ENTITY_H
