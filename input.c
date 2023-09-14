#include "input.h"

///// Globales

extern int g_loop;

///// Funciones

void handle_events(SDLContext *context, Input *input)
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
				// Player Input -> KEYDOWN
				handle_input_general(context, &event.key);
				handle_input_player(&event.key, input, 1);			
				break;
			}
			case SDL_KEYUP: {
				// Player Input -> KEYUP
				handle_input_player(&event.key, input, 0);
				break;
			}
		}
	}
}

void handle_input_general(SDLContext *context, SDL_KeyboardEvent *keyboard)
{
	// La resolucion del juegos esta ajustada a 240x320 pixeles, el aumento se limita unicamente a
	// escalar dicha resolucion por un una escala de enteros, es decir 1x, 2x, 3x, etc. tratando de
	// no sobrepasar la resolucion real del monitor.
	if (keyboard->keysym.scancode == SDL_SCANCODE_PAGEUP)
	{
		// Aumenta Resolucion
	}
	else if (keyboard->keysym.scancode == SDL_SCANCODE_PAGEDOWN)
	{
		// Reduce Resolucion
	}
}

void handle_input_player(SDL_KeyboardEvent *keyboard, Input *input, Uint8 state)
{
	input->left.state	= CHECK_INPUT(input->left, keyboard, state);
	input->right.state	= CHECK_INPUT(input->right, keyboard, state);
	input->fire.state	= CHECK_INPUT(input->fire, keyboard, state);
	input->start.state	= CHECK_INPUT(input->start, keyboard, state);
}

void init_bindings(Input *input)
{
	input->left.binding		= SDL_SCANCODE_LEFT;
	input->right.binding	= SDL_SCANCODE_RIGHT;
	input->fire.binding		= SDL_SCANCODE_SPACE;
	input->start.binding	= SDL_SCANCODE_RETURN;
}