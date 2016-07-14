#pragma once

#include "cloud.h"

class Storm
{
    Uint8 nr;
    int counter;

    Cloud* cloud;

public:

    Storm();
    ~Storm();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer, int &w, int &h );
};
