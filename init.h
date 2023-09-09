#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>

///// MACROS

#define NAME "Invaders from Yuggoth"
#define BASE_WIDTH 240
#define BASE_HEIGHT 320

///// Estructuras

typedef struct  {
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Context;

///// Funciones

SDL_Context *init_sdl();
void close_sdl(SDL_Context *ctx);

#endif // INIT_H