#pragma once
#include "texture.h"
#include "chunk.h"
#include "profit.h"
#include <vector>

class Title
{
protected:
    Texture label;
	Texture wallpaper;

public:
	
	Title();
    ~Title();
    void free();

    bool load( SDL_Renderer* &renderer, int screen_width );
    void render( SDL_Renderer* &renderer, int screen_width, int screen_height );

    int &getH();
};

class Value :public Title
{
	Chunk click;
	int type;
	int startY;
	
	vector <Profit*> profitVec;
	
public:

	void free();

	bool load( SDL_Renderer* &renderer, SDL_Window* &window, int goal_height );
	void render( SDL_Renderer* &renderer );
	void handle( SDL_Event &event, SDL_Renderer* &renderer, SDL_Window* &window );
	int get();
};
