#pragma once
#include "texture.h"

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

    int getH();
};