#pragma once

#include "text.h"
#include "image.h"

class Options
{
    int nr;
    Text* text;

public:

    Options();
    ~Options();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );

    // Animation
    void fadeIO( int value );
};
