#pragma once

#include "texture.h"

class Calendar
{
	
protected:
	
	int nr;
	Texture* texture;
	int type;
	bool focus;
	
	int count;
	int whose;
	
public:

	Calendar();
	~Calendar();
	void free();
	
	bool &setFocus();
	
	bool load( SDL_Renderer* &renderer, int screen_width );
	void render( SDL_Renderer* &renderer, int y );
	void handle( SDL_Event &event );

	int getPeriod();
};

class ProfitCurrency: public Calendar
{
	
public:
	bool load( SDL_Renderer* &renderer, int screen_width );
};