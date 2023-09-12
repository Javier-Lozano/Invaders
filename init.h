#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>

///// MACROS

#define NAME "Invaders from Yuggoth"
#define DISPLAY_REAL_WIDTH 240
#define DISPLAY_REAL_HEIGHT 320

#define MAX_BULLETS 256

///// Estructuras

typedef struct sdl_context_st {
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDLContext;

///// Funciones

SDLContext *init_sdl();
void close_sdl(SDLContext *ctx);

#endif // INIT_H