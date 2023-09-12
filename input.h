#ifndef INPUT_H
#define INPUT_H

#include "init.h"

///// Estructuras

typedef struct input_st {
	int left, right, fire, start;
} Input;

typedef Input Bindings;

///// Funciones

void handle_events(SDLContext *context, Input *input, Bindings *bindings);
void handle_input_player(SDL_KeyboardEvent *key, Input *input, Bindings *bindings);
void handle_input_general(SDLContext *context, SDL_KeyboardEvent *key);

void init_Bindings(Bindings *bindings);

#endif // INPUT_H