#pragma once

//C++ basic Libs and SDL
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

//SelfMade Libs
#include "constantes.hpp"
#include "Entity.hpp"

class SDL_Handler
{
public:
	//Constructor and destructor
	SDL_Handler(const char* title, int width,int height );
	~SDL_Handler();

	//initialiser (returns true if everything worked correctly)
	bool init();

	//Updating screens
	void ClearScreen();
	void RenderEntity(Entity &e);
	void Display() const;
public:
	//window
	SDL_Window		*window;

	//renderer
	SDL_Renderer	*renderer;

	//Event Listener (Mouse, etc...)
	SDL_Event		event;

};