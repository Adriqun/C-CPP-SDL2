#pragma once
#include "texture.h"
#include "font.h"

class Attain
{
    Font font;

    Texture label;
    Texture result;

    string never;

public:

    Attain();
    ~Attain();
    void free();

    bool load( SDL_Renderer* &renderer, int goal_height );
    void render( SDL_Renderer* &renderer, int screen_width );
	
	int getB();
};
