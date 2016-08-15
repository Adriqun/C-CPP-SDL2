#pragma once
#include "texture.h"
#include "chunk.h"

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
	
public:

	void free();

	bool load( SDL_Renderer* &renderer, int goal_height, int screen_width );
	void render( SDL_Renderer* &renderer );
	void handle( SDL_Event &event );
	int get();
};
