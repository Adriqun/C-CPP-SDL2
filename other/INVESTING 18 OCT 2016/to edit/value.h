#pragma once
#include "title.h"
#include "tax.h"
#include "profit.h"
#include "chunk.h"
#include <vector>


class Value :public Title
{
	Chunk click;
	int startY;
	
	int old_nr;
	vector <Profit*> profitVec;
	
public:

	void free();

	bool load( SDL_Renderer* &renderer, SDL_Window* &window, int goal_height );
	void render( SDL_Renderer* &renderer );
	void handle( SDL_Event &event, SDL_Renderer* &renderer, SDL_Window* &window );
	
	vector <Tax*> get();
};