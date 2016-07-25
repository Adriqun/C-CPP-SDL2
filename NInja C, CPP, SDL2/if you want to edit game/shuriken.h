#pragma once

#include "texture.h"

class Shuriken
{
    /* Position x, position y */
    float x;
    float y;

    /* Texture and angle */
    Texture texture;
    double angle;

    /* Our keyboard */
    const Uint8* key;
    Uint8 alpha;

    bool direction;
    bool state;

public:

    Shuriken();
    ~Shuriken();
    void free();

    void fadeIn();
    void fadeOut();

    bool control( float x, float y, int screen_width );
    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );

    void setState( bool yes );
    SDL_Rect getRect();
};
