#include "player.h"

extern Input g_input;

Player *player_create(int x, int y, int w, int h, int speed)
{
	// Variables
	Player *p = NULL;

	if (p = malloc(sizeof(Player)))
	{
		p->x = x;
		p->y = y;
		p->speed = speed;
	}	
	
	return p;
}

void player_destroy(Player *player)
{
	if (player)
	{
		free(player);
	}
}

void player_update(Player *player)
{
	// Movimiento
	if (g_input.right)	{ player->x += player->speed; }
	if (g_input.left)	{ player->x -= player->speed; }

	// Limita la posicion
	if (player->x < 0) { player->x = 0; }
	if (player->x > BASE_WIDTH - ENTITY_W) { player->x = BASE_WIDTH - ENTITY_W; }

	// Disparo
	if (g_input.fire)
	{
		//bullet_create(x, y);
	}
}

void player_draw(Player *player, SDL_Renderer * renderer)
{
	SDL_Rect r = {
		player->x,
		player->y,
		ENTITY_W,
		ENTITY_H
	};

	SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(renderer, &r);
}