#include <SDL2/SDL.h>
#include "init.h"
#include "input.h"
#include "player.h"

///// Globales

int g_loop	= 1;
extern Input g_input;

///// Main

void debug_show_input(SDL_Renderer *renderer)
{
	if (g_input.left)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0, 0xFF);
		SDL_Rect r = {0, 0, 16, 16};
		SDL_RenderFillRect(renderer, &r);
	}
	if (g_input.right)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 0xFF);
		SDL_Rect r = {16, 0, 16, 16};
		SDL_RenderFillRect(renderer, &r);
	}
	if (g_input.fire)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
		SDL_Rect r = {32, 0, 16, 16};
		SDL_RenderFillRect(renderer, &r);
	}
	if (g_input.start)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0xFF, 0xFF);
		SDL_Rect r = {48, 0, 16, 16};
		SDL_RenderFillRect(renderer, &r);
	}
}

int main(int argc, char *argv[])
{
	// Variables
	SDL_Context *context = NULL;
	Player *player = player_create(
		BASE_WIDTH / 2,
		BASE_HEIGHT - 32,
		ENTITY_W,
		ENTITY_W,
		PLAYER_SPEED
		);

	// Init SDL
	context = init_sdl();
	if (context)
	{
		init_keybindings();
		// Loop
		while(g_loop)
		{
			// Events
			handle_events(context);

			// Update Player
			player_update(player);

			//update_aliens();

			// Collisions
			//collisions_update();
			
			// Rendering
			SDL_SetRenderDrawColor(context->renderer, 0, 0, 0, 0xFF);
			SDL_RenderClear(context->renderer);

			// Render Player
			player_draw(player, context->renderer);

			debug_show_input(context->renderer);

			SDL_SetRenderDrawColor(context->renderer, 0xFF, 0, 0, 0xFF);
			SDL_RenderDrawPoint(context->renderer, BASE_WIDTH / 2, BASE_HEIGHT / 2);

			SDL_RenderPresent(context->renderer);
		}
	}

	player_destroy(player);

	// Close SDL
	close_sdl(context);
}

