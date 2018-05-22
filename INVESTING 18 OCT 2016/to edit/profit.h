#pragma once
#include "goal.h"
#include "period.h"

class Cost :public Goal
{
public:
	using Goal::Goal;
	bool load( SDL_Renderer* &renderer, int x, int y );
	void render( SDL_Renderer* &renderer );
	void setY( int y );
};

class Name :public Goal
{
	
public:
	using Goal::Goal;
	bool load( SDL_Renderer* &renderer, int x, int y );
	void handle( SDL_Event &event );
	void render( SDL_Renderer* &renderer );
	void setY( int y );
};

class Profit
{
	Cost* cost;
	Name* name;
	Period period;
	ProfitCurrency currency;
	
	int nr;
	Texture* texture;

	int type, y;
	bool thrash;
	
public:
	
	Profit( int type = 0, int y = 0 );
	~Profit();
	void free();
	
	bool load( SDL_Renderer* &renderer, SDL_Window* &window );
	void render( SDL_Renderer* &renderer );
	void handle( SDL_Event &event );
	
	bool isThrash();
	unsigned long long getCost( int &a );
	int getCalendar();
	int getCurrency();
	int getH();
	void setY( int y );
};
