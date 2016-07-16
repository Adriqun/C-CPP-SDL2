#pragma once

#include "texture.h"
class Pause
{
    int nr;
    int state;
    Uint8 alpha;

    int* x;
    int* y;
    Texture* texture;

public:

    Pause();
    ~Pause();
    void free();

    void control();
    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );

    void fadeIn();
    void fadeOut();
    int getState();
};
