#ifndef INPUT_H
#define INPUT_H

#include "init.h"

///// Estructuras

typedef struct {
	int left, right, fire, start;
} KeyBindings;

typedef KeyBindings Input;

///// Funciones

void handle_events(SDL_Context *context);
void handle_input_general(SDL_Context *context, SDL_KeyboardEvent *key);
void handle_input_player(SDL_KeyboardEvent *key);

void init_keybindings();

#endif // INPUT_H