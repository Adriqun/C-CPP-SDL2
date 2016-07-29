#pragma once

#include "texture.h"
class Hearts
{
    int nr;
    int actual_nr;
    Uint8 alpha;

    int* x;
    int* y;
    Texture* texture;

public:

    Hearts();
    ~Hearts();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );
    void set( float x, float y );

    void lose( bool yes );
    bool dead();

    void fadeIn();
    void fadeOut();
};
