#include "entity.h"

///// Entity

Entity *entity_create(CollisionBox collider /*, Sprite *sprites*/)
{
	Entity *entity = NULL;

	entity = malloc(sizeof(Entity));
	if (!entity)
	{
		printf("Error: entity_create() -> Not enough memory to allocate Entity.\n");
	}

	entity->collider = collider;
	entity->x_speed = 0;
	entity->y_speed = 0;
	entity->delete_flag = 0;
	//entity->sprites = sprites;

	return entity;
}

void entity_destroy(Entity *entity)
{
	if (entity)
	{
		/*sprite_destroy(entity->sprite)*/
		free(entity);
		entity = NULL;
	}
}

///// Player

Entity *player_create()
{
	Entity *player = NULL;

	CollisionBox collider = {
		PLAYER_START_X,
		PLAYER_START_Y,
		PLAYER_WIDTH,
		PLAYER_HEIGHT,
		LAYER_PLAYER
	};

	// Entity
	player = entity_create(collider);
	if (!player)
	{
		printf("Error: player_create() -> Couldn't create Entity (Player).\n");
		return NULL;
	}

	return player;
}


void player_update(Entity *player, Input *input, Entity **bullets)
{
	// Bala
	static Entity *bullet_ref = NULL;

	// Movimiento
	player->x_speed = (input->right - input->left) * PLAYER_SPEED;
	player->collider.x += player->x_speed;

	//if (input->right)	{ player->x_speed += PLAYER_SPEED; }
	//if (input->left)	{ player->x_speed -= PLAYER_SPEED; }

	// Limita la posicion
	if (player->collider.x < 0) { player->collider.x = 0; }
	if (player->collider.x > DISPLAY_REAL_WIDTH - PLAYER_WIDTH) { player->collider.x = DISPLAY_REAL_WIDTH - PLAYER_WIDTH; }

	// Disparo
	if (input->fire && bullet_ref == NULL)
	{
		// Check bullets for an empty space
		for(int i = 0; i < MAX_BULLETS; i++)
		{
			if (!bullets[i] && bullet_ref == NULL)
			{
				bullets[i] = bullet_create(player->collider.x, player->collider.y - 4, LAYER_PLAYER);
				bullet_ref = bullets[i];
			}
		}
	}
}

///// Bullets

Entity *bullet_create(float x, float y, Layer type)
{
	Entity *bullet = NULL;
	float x_speed = 0, y_speed = 0;
	CollisionBox col = {x, y, 0, 0, type};

	switch (type)
	{
		case LAYER_PLAYER:
		{
			col.w = 3;
			col.h = 8;
			col.type = type;
			y_speed = -16; 
			break;
		}
		case LAYER_ENEMY:
		{
			col.w = 2;
			col.h = 8;
			col.type = type;
			y_speed = 16; 
			break;
		}
		default:
		{
			printf("Error: create_bullet() -> Wrong type.\n");
			return NULL;
		}
	}

	bullet = entity_create(col);
	if (!bullet)
	{
		printf("Error: bullet_create() -> Couldn't create Entity (Bullet).\n");
		return NULL;
	}

	bullet->x_speed = x_speed;
	bullet->y_speed = y_speed;

	return bullet;
}

void bullet_update(Entity *bullet)
{
	bullet->collider.x += bullet->x_speed;
	bullet->collider.y += bullet->y_speed;

	if ((bullet->collider.x < 0) || (bullet->collider.x > DISPLAY_REAL_WIDTH)) {bullet->x_speed = -bullet->x_speed;}

	// Elimina las balas que llegan a los bordes de la pantalla
	if ((bullet->collider.y < 16) || (bullet->collider.y > DISPLAY_REAL_HEIGHT - 16))
	{
		bullet->delete_flag = 1;
		bullet->collider.type = LAYER_NONE;
	}

}