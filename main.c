#include <SDL2/SDL.h>
#include "init.h"
#include "input.h"
#include "entity.h"

#define DEBUG_INPUT 0
#define DEBUG_COLLIDERS 1

///// Globales

int g_loop	= 1;

///// Main

int main(int argc, char *argv[])
{
	SDLContext *context = NULL;
	Entity *player = NULL;
	Entity *bullets[MAX_BULLETS] = {0};

	Input input		= {0};
	Bindings bindings	= {0};

	// Inicializa SDL
	context = init_sdl();
	if (context)
	{
		player = player_create();
		init_Bindings(&bindings);

		// Bucle Principal
		while(g_loop)
		{
			// Eventos
			handle_events(context, &input, &bindings);

			// Player
			player_update(player, &input, bullets);

			// Bullets
			for(int i = 0; i < MAX_BULLETS; i++)
			{
				if (bullets[i])
				{
					bullet_update(bullets[i]);
				}
			}


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
			if (input.left)
			{
				SDL_SetRenderDrawColor(context->renderer, 0, 0xFF, 0, 0xFF);
				SDL_Rect r = {0, 0, 16, 16};
				SDL_RenderFillRect(context->renderer, &r);
			}
			if (input.right)
			{
				SDL_SetRenderDrawColor(context->renderer, 0, 0, 0xFF, 0xFF);
				SDL_Rect r = {16, 0, 16, 16};
				SDL_RenderFillRect(context->renderer, &r);
			}
			if (input.fire)
			{
				SDL_SetRenderDrawColor(context->renderer, 0xFF, 0, 0, 0xFF);
				SDL_Rect r = {32, 0, 16, 16};
				SDL_RenderFillRect(context->renderer, &r);
			}
			if (input.start)
			{
				SDL_SetRenderDrawColor(context->renderer, 0xFF, 0, 0xFF, 0xFF);
				SDL_Rect r = {48, 0, 16, 16};
				SDL_RenderFillRect(context->renderer, &r);
				bullet->collider.x = player->collider.x;
				bullet->collider.y = player->collider.y;
				bullet->y_speed = -8;
				bullet-> x_speed = 0;
			}
#endif // Input
#if DEBUG_COLLIDERS
			SDL_Color col = {0xFF,0,0,0xFF};
			collider_draw(context->renderer, &player->collider, &col);

			for(int i = 0; i < MAX_BULLETS; i++)
			{
				if (bullets[i])
				{
					collider_draw(context->renderer, &bullets[i]->collider, &col);

				}
			}

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

