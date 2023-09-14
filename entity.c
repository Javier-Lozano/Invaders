#include "entity.h"

///// Entity

Entity *entity_create(Sprite *sprite, SDL_FRect *collider, SDL_FPoint *speed, Uint8 type)
{
	Entity *entity = NULL;

	entity = malloc(sizeof(Entity));
	if (!entity)
	{
		printf("Error: entity_create() -> Not enough memory to allocate Entity.\n");
	}

	entity->sprite = sprite;
	entity->collider = *collider;
	entity->speed = *speed;
	entity->type = type;

	return entity;
}

void entity_destroy(Entity *entity)
{
	if (entity)
	{
		//sprite_destroy(entity->sprite)
		free(entity);
	}
}

///// Player

Entity *player_create()
{
	Entity *player = NULL;

	SDL_FRect collider = {
		PLAYER_X,
		PLAYER_Y,
		PLAYER_W,
		PLAYER_H
	};

	SDL_FPoint speed = {0};

	// Entity
	player = entity_create(NULL, &collider, &speed, TYPE_PLAYER);
	if (!player)
	{
		printf("Error: player_create() -> Couldn't create Entity (Player).\n");
		return NULL;
	}

	return player;
}


void player_update(Entity *player, Input *input)
{
	// Movimiento
	player->speed.x = (input->right.state - input->left.state) * PLAYER_SPEED;
	player->collider.x += player->speed.x;

	// Limita la posicion
	if (player->collider.x < 0) { player->collider.x = 0; }
	if (player->collider.x > DISPLAY_REAL_WIDTH - PLAYER_W) { player->collider.x = DISPLAY_REAL_WIDTH - PLAYER_W; }

	// Disparo
	if (input->fire.state)
	{
		//player_bullet = bullet_create(player->collider.x, player->collider.y - 4, LAYER_PLAYER);
	}
}

///// Bullets

Entity *bullet_create(float x, float y, Uint8 type)
{
	Entity *bullet = NULL;

	SDL_FRect collider = {x, y, BULLET_W, BULLET_H};
	SDL_FPoint speed = {0};

	switch (type)
	{
		case TYPE_BULLET_PLAYER:
		{
			speed.y = -BULLET_SPEED;
			break;
		}
		case TYPE_BULLET_ENEMY:
		{
			speed.y = BULLET_SPEED;
			break;
		}
		case TYPE_BULLET_ENEMY_SKULL:
		{
			collider.w = BULLET_INV_W;
			speed.y = BULLET_SPEED * 1.5f;
			break;
		}
		default:
		{
			printf("Error: create_bullet() -> Wrong type.\n");
			return NULL;
		}
	}

	bullet = entity_create(NULL, &collider, &speed, type);
	if (!bullet)
	{
		printf("Error: bullet_create() -> Couldn't create Entity (Bullet).\n");
		return NULL;
	}

	return bullet;
}

void bullet_update(Entity *bullet)
{
	bullet->collider.x += bullet->speed.x;
	bullet->collider.y += bullet->speed.y;

	//if ((bullet->collider.x < 0) || (bullet->collider.x > DISPLAY_REAL_WIDTH)) {bullet->x_speed = -bullet->x_speed;}

	// Marca las balas que llegan a los bordes de la pantalla
	if (CHECK_BETWEEN_RANGE(bullet->collider.y, 16, DISPLAY_REAL_HEIGHT - 16))
	{
		bullet->type = TYPE_NONE;
	}

}