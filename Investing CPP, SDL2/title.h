#pragma once
#include "texture.h"
#include "font.h"

class Title
{

protected:

    Font font;

    int x, y;
    Texture texture;

public:

    Title();
    ~Title();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );
    void handle( SDL_Event &event );

    unsigned getWidth();
    unsigned getHeight();
};
