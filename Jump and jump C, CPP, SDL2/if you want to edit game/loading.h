#pragma once

#include "texture.h"

class Loading
{
    enum object
    {
        BACKGROUND = 0,
        LOADING,
        WHITE_BAR,
        GREEN_BAR,
        nr
    };

    int counter;

    int* x;
    int* y;
    Texture* texture;

public:

    Loading();
    ~Loading();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer, int state );
};
