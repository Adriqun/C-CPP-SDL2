#pragma once

#include "texture.h"

class Calendar
{
	int nr;
	Texture* texture;
	int type;
	
public:

	Calendar();
	~Calendar();
	void free();
	
	bool load( SDL_Renderer* &renderer );
	void render( SDL_Renderer* &renderer, int y );
	void handle( SDL_Event &event );	
};