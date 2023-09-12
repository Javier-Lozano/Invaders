#include "init.h"

SDLContext *init_sdl()
{
	SDLContext *ctx;
	SDL_Window *window;
	SDL_Renderer *renderer;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Error: init_sdl() -> SDL Error: %s.\n", SDL_GetError());
		return NULL;
	}

	// Ventana
	window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_REAL_WIDTH, DISPLAY_REAL_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		printf("Error: init_sdl() -> SDL Error: %s.\n", SDL_GetError());
		SDL_Quit();

		return NULL;
	}

	// Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		printf("Error: init_sdl() -> SDL Error: %s.\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();

		return NULL;
	}

	ctx = (SDLContext *)malloc(sizeof(SDLContext));
	if (!ctx)
	{
		printf("Error: init_sdl() -> Not enough memory to allocate SDLContext.\n");
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();

		return NULL;
	}
	
	ctx->window = window;
	ctx->renderer = renderer;

	printf("SDL Initialized!\n");

	return ctx;
}

void close_sdl(SDLContext *ctx)
{
	if (ctx)
	{
		SDL_DestroyRenderer(ctx->renderer);
		SDL_DestroyWindow(ctx->window);
		free(ctx);

		SDL_Quit();

		printf("SDL Closed!\n");
	}
}
