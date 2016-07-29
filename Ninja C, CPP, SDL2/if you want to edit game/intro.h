#pragma once

#include "texture.h"

class Intro
{
    enum object
    {
        BACKGROUND = 0,
        PREVIEW,
        SHURIKEN,
        TITLE,
        AUTHOR,
        PRODUCED,
        nr
    };

    int counter;
    bool quit;

    int* x;
    int* y;
    Texture* texture;

public:

    Intro();
    ~Intro();

    void free();
    bool isClose();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer, int fps );
};
