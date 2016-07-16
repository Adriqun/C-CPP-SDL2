#pragma once

#include "texture.h"

class Options
{
    int nr;

    int* x;
    int* y;
    Texture* texture;

public:

    Options();
    ~Options();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );
};
