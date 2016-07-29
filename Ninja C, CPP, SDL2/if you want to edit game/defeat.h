#pragma once

#include "texture.h"
#include "chunk.h"

class Defeat
{
    int nr;

    int *x;
    int *y;
    Texture* texture;
    Chunk click;

    Uint8 alpha;
    int state;

public:

    Defeat();
    ~Defeat();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );

    int control();
};
