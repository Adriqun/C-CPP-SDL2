#pragma once

#include "text.h"
#include "image.h"

class Scores
{
    int nr;
    Text* text;

public:

    Scores();
    ~Scores();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );

    void fadeIO( int value );
};
