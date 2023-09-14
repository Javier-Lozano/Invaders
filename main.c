#include <SDL2/SDL.h>
#include "init.h"
#include "input.h"
#include "entity.h"

#define DEBUG_INPUT 1
#define DEBUG_COLLIDERS 1

///// Globales

int g_loop	= 1;


void collider_draw(SDL_Renderer *renderer, SDL_FRect *collider, SDL_Color *color)
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

///// Main

int main(int argc, char *argv[])
{
	SDLContext *context				= NULL;
	Entity *player					= NULL;
	Entity *bullet_player			= NULL;
	Entity *bullet_enemy			= NULL;
	Entity *bullet_enemy_skull		= NULL;
	//Entity *enemies[ENEMY_COUNT]	= {0};
	//Entity *bullets[MAX_BULLETS]	= {0};
	Input input						= {0};

	// Inicializa SDL
	context = init_sdl();
	if (context)
	{
		// Inicializa el Juego
		init_bindings(&input);
		player = player_create();

		// Bucle Principal
		while(g_loop)
		{
			// Eventos
			handle_events(context, &input);

			// Player
			player_update(player, &input);


			if (!bullet_player)
			{
				bullet_player = bullet_create(DISPLAY_REAL_WIDTH / 2, DISPLAY_REAL_HEIGHT - 32, TYPE_BULLET_PLAYER);
			}
			if (!bullet_enemy)
			{
				bullet_enemy = bullet_create(DISPLAY_REAL_WIDTH / 2, 32, TYPE_BULLET_ENEMY);
			}
			if (!bullet_enemy_skull)
			{
				bullet_enemy_skull = bullet_create(DISPLAY_REAL_WIDTH / 4, 32, TYPE_BULLET_ENEMY_SKULL);
			}

			bullet_update(bullet_player);
			bullet_update(bullet_enemy);
			bullet_update(bullet_enemy_skull);

			if (bullet_player->type == TYPE_NONE)
			{
				entity_destroy(bullet_player);
				bullet_player = NULL;
			}
			if (bullet_enemy->type == TYPE_NONE)
			{
				entity_destroy(bullet_enemy);
				bullet_enemy = NULL;
			}
			if (bullet_enemy_skull->type == TYPE_NONE)
			{
				entity_destroy(bullet_enemy_skull);
				bullet_enemy_skull = NULL;
			}

			// Bullets
			//for(int i = 0; i < MAX_BULLETS; i++)
			//{
			//	if (bullets[i])
			//	{
			//		bullet_update(bullets[i]);
			//		if (bullets[i]->delete_flag)
			//		{
			//			entity_destroy(bullets[i]);
			//			bullets[i] = NULL;
			//		}
			//	}
			//}


			//update_aliens();

			// Collisions
			//collisions_update();

			// Elimina todas las entidades marcadas
			
			
			// Rendering
			SDL_SetRenderDrawColor(context->renderer, 0, 0, 0, 0xFF);
			SDL_RenderClear(context->renderer);

			// Render Player
			//player_draw(player, context->renderer);
#if DEBUG_INPUT
			if (input.left.state)
			{
				SDL_SetRenderDrawColor(context->renderer, 0, 0xFF, 0, 0xFF);
				SDL_Rect r = {0, 0, 16, 16};
				SDL_RenderFillRect(context->renderer, &r);
			}
			if (input.right.state)
			{
				SDL_SetRenderDrawColor(context->renderer, 0, 0, 0xFF, 0xFF);
				SDL_Rect r = {16, 0, 16, 16};
				SDL_RenderFillRect(context->renderer, &r);
			}
			if (input.fire.state)
			{
				SDL_SetRenderDrawColor(context->renderer, 0xFF, 0, 0, 0xFF);
				SDL_Rect r = {32, 0, 16, 16};
				SDL_RenderFillRect(context->renderer, &r);
			}
			if (input.start.state)
			{
				SDL_SetRenderDrawColor(context->renderer, 0xFF, 0, 0xFF, 0xFF);
				SDL_Rect r = {48, 0, 16, 16};
				SDL_RenderFillRect(context->renderer, &r);
				//bullet->collider.x = player->collider.x;
				//bullet->collider.y = player->collider.y;
				//bullet->y_speed = -8;
				//bullet-> x_speed = 0;
			}
#endif // Input
#if DEBUG_COLLIDERS
			SDL_Color col = {0xFF,0,0,0xFF};
			collider_draw(context->renderer, &player->collider, &col);

			if (bullet_player)
			{
				collider_draw(context->renderer, &bullet_player->collider, &col);
			}
			if (bullet_enemy)
			{
				collider_draw(context->renderer, &bullet_enemy->collider, &col);
			}
			if (bullet_enemy_skull)
			{
				collider_draw(context->renderer, &bullet_enemy_skull->collider, &col);
			}

			//for(int i = 0; i < MAX_BULLETS; i++)
			//{
			//	if (bullets[i])
			//	{
			//		collider_draw(context->renderer, &bullets[i]->collider, &col);
//
			//	}
			//}

#endif // Colliders

			SDL_SetRenderDrawColor(context->renderer, 0xFF, 0, 0, 0xFF);
			SDL_RenderDrawPoint(context->renderer, DISPLAY_REAL_WIDTH / 2, DISPLAY_REAL_HEIGHT / 2);

			SDL_RenderPresent(context->renderer);
		}
	}

	entity_destroy(player);

	// Close SDL
	close_sdl(context);
}

