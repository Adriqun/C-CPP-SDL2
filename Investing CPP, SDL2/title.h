#pragma once
#include "texture.h"
#include "font.h"

class Title
{
    Font font;
    Texture texture;

public:

    ~Title();
    void free();

    bool load( SDL_Renderer* &renderer, int screen_width );
    void render( SDL_Renderer* &renderer );

    int &getW();
    int &getH();
};
