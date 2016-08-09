#pragma once
#include "texture.h"

class Valuables
{
    Texture a;
    Texture b;
	
public:

    Valuables();
    ~Valuables();
    void free();

    bool load( SDL_Renderer* &renderer, int goal_bar_posY, int screen_width );
    void render( SDL_Renderer* &renderer );
    void handle( SDL_Event &event );
};
