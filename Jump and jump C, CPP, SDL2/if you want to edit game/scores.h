#pragma once

#include "texture.h"

class Scores
{
    int nr;

    int* x;
    int* y;
    Texture* texture;

public:

    Scores();
    ~Scores();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );
};
