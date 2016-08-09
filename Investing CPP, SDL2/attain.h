#pragma once
#include "texture.h"
#include "font.h"

class Attain
{
    Font font;

    Texture texture;
    Texture result;

    string once;
    string never;

public:

    Attain();
    ~Attain();
    void free();

    bool load( SDL_Renderer* &renderer, int goal_posY );
    void render( SDL_Renderer* &renderer, int screen_width );
};
