#pragma once

#include "texture.h"
#include "cloud.h"
#include "chunk.h"

class Storm
{
    Uint8 nr;
    int counter;

    Cloud* cloud;

    Uint8 c_nr;
    Chunk* chunk;

    Texture blank;

public:

    Storm();
    ~Storm();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );

    void fadeOut( SDL_Renderer* &renderer );
    void halt();
    void random( SDL_Renderer* &renderer, int w, int h );
};
