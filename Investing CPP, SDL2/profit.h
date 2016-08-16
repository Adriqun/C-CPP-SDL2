#pragma once
#include "goal.h"
#include "calendar.h"

class AddCost :public Goal
{
	public:
	bool load( SDL_Renderer* &renderer, int x, int y );
	void render( SDL_Renderer* &renderer );
	void setY( int y );
};

class AddName :public Goal
{
	
public:

	bool load( SDL_Renderer* &renderer, int x, int y );
	void handle( SDL_Event &event );
	void render( SDL_Renderer* &renderer );
	void setY( int y );
};

class Profit
{
	SDL_Color color;
	AddCost* addCost;
	AddName addName;
	Calendar calendar;
	ProfitCurrency currency;
	
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
	unsigned long long getCost();
	int getCalendar();
	int getCurrency();
	int getH();
	void setY( int y );
};
