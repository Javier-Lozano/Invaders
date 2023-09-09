#include "init.h"

SDL_Context *init_sdl()
{
	SDL_Context *ctx;
	SDL_Window *window;
	SDL_Renderer *renderer;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("init_sdl(): SDL Error: %s", SDL_GetError());
		return NULL;
	}

	// Ventana
	window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, BASE_WIDTH, BASE_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		printf("init_sdl(): SDL Error: %s", SDL_GetError());
		SDL_Quit();

		return NULL;
	}

	// Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		printf("init_sdl(): SDL Error: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();

		return NULL;
	}

	ctx = (SDL_Context *)malloc(sizeof(SDL_Context));
	if (ctx)
	{
		ctx->window = window;
		ctx->renderer = renderer;
	}

	return ctx;
}

void close_sdl(SDL_Context *ctx)
{
	if (ctx)
	{
		SDL_DestroyRenderer(ctx->renderer);
		SDL_DestroyWindow(ctx->window);
		free(ctx);
	}
}
