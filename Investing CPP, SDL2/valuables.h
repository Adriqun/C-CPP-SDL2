#pragma once
#include "texture.h"
#include "font.h"

class Valuables
{
    Texture plus;
    Texture minus;

public:

    Valuables();
    ~Valuables();
    void free();

    bool load( SDL_Renderer* &renderer, int title_bar_posY );
    void render( SDL_Renderer* &renderer, int screen_width );
    void handle( SDL_Event &event );
};
