#pragma once
#include "texture.h"

class Title
{
    Texture* texture;

public:
	
	Title();
    ~Title();
    void free();

    bool load( SDL_Renderer* &renderer, int screen_width );
    void render( SDL_Renderer* &renderer );

    int &getW();
    int &getH();
};
