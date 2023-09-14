#ifndef _INPUT_H_
#define _INPUT_H_

#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>

#include "init.h"

///// MACROS

#define CHECK_INPUT(key, keyboard, value) (key.binding == keyboard->keysym.scancode) ? value : key.state;

///// Estructuras

typedef struct key_st
{
	SDL_Scancode binding;
	int state;
} Key;

typedef struct input_st {
	Key left, right, fire, start;
} Input;

///// Funciones

void handle_events(SDLContext *context, Input *input);
void handle_input_player(SDL_KeyboardEvent *keyboard, Input *input, Uint8 state);
void handle_input_general(SDLContext *context, SDL_KeyboardEvent *keyboard);

void init_bindings(Input *input);

#endif // _INPUT_H_