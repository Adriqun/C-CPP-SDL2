#pragma once
#include "goal.h"

class AddCost :public Goal
{
	public:
	bool load( SDL_Renderer* &renderer, int x, int y );
};

class AddName :public Goal
{
	
public:

	bool load( SDL_Renderer* &renderer, int x, int y );
	void handle( SDL_Event &event );
	void render( SDL_Renderer* &renderer );

};

class Profit
{
	SDL_Color color;
	AddCost* addCost;
	AddName addName;
	
	int nr;
	Texture* texture;

	int ch;
	int x, y;
	
	bool thrash;
	
public:
	
	Profit( int ch = 0, int x = 0, int y = 0 );
	~Profit();
	void free();
	
	bool load( SDL_Renderer* &renderer, SDL_Window* &window );
	void render( SDL_Renderer* &renderer );
	void handle( SDL_Event &event );
	
	bool isThrash();
};
