#include "input.h"

///// Globales

KeyBindings g_key_bindings;
Input g_input;

extern int g_loop;

///// Funciones

void handle_events(SDL_Context *context)
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			///// QUIT
			case SDL_QUIT: {
				g_loop = 0;
				break;
			}
			///// KEYBOARD
			case SDL_KEYDOWN: {
				// Player Input
				handle_input_general(context, &event.key);
				handle_input_player(&event.key);			
				break;
			}
			case SDL_KEYUP: {
				// Player Input
				handle_input_player(&event.key);
				break;
			}
		}
	}
}

void handle_input_general(SDL_Context *context, SDL_KeyboardEvent *key)
{
	// La resolucion del juegos esta ajustada a 240x320 pixeles, el aumento se limita unicamente a
	// escalar dicha resolucion por un una escala de enteros, es decir 1x, 2x, 3x, etc. tratando de
	// no sobrepasar la resolucion real del monitor.
	if (key->keysym.scancode == SDL_SCANCODE_PAGEUP)
	{
		// Aumenta Resolucion
	}
	else if (key->keysym.scancode == SDL_SCANCODE_PAGEDOWN)
	{
		// Reduce Resolucion
	}
}

void handle_input_player(SDL_KeyboardEvent *key)
{
	g_input.left	= (key->keysym.scancode == g_key_bindings.left) ? key->state : g_input.left;
	g_input.right	= (key->keysym.scancode == g_key_bindings.right) ? key->state : g_input.right;
	g_input.fire	= (key->keysym.scancode == g_key_bindings.fire) ? key->state : g_input.fire;
	g_input.start	= (key->keysym.scancode == g_key_bindings.start) ? key->state : g_input.start;
}

void init_keybindings()
{
	g_key_bindings.left = SDL_SCANCODE_LEFT;
	g_key_bindings.right = SDL_SCANCODE_RIGHT;
	g_key_bindings.fire = SDL_SCANCODE_SPACE;
	g_key_bindings.start = SDL_SCANCODE_RETURN;
}