#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

class Core
{
	bool quit;
	int width;
	int height;
	
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;
	
public:

	Core();
	
	void init();
	void top_render();
	void bot_render();
	void free();
	
	bool &isQuit();
	int getWidth();
	int getHeight();
	SDL_Event &getEvent();
	SDL_Window* &getWindow();
	SDL_Renderer* &getRenderer();
};