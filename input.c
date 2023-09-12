#include "input.h"

///// Globales

extern int g_loop;

///// Funciones

void handle_events(SDLContext *context, Input *input, Bindings *bindings)
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
				handle_input_player(&event.key, input, bindings);			
				break;
			}
			case SDL_KEYUP: {
				// Player Input
				handle_input_player(&event.key, input, bindings);
				break;
			}
		}
	}
}

void handle_input_general(SDLContext *context, SDL_KeyboardEvent *key)
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

void handle_input_player(SDL_KeyboardEvent *key, Input *input, Bindings *bindings)
{
	input->left	= (key->keysym.scancode == bindings->left)	? key->state : input->left;
	input->right	= (key->keysym.scancode == bindings->right)	? key->state : input->right;
	input->fire	= (key->keysym.scancode == bindings->fire)	? key->state : input->fire;
	input->start	= (key->keysym.scancode == bindings->start)	? key->state : input->start;
}

void init_Bindings(Bindings *bindings)
{
	bindings->left	= SDL_SCANCODE_LEFT;
	bindings->right	= SDL_SCANCODE_RIGHT;
	bindings->fire	= SDL_SCANCODE_SPACE;
	bindings->start	= SDL_SCANCODE_RETURN;
}