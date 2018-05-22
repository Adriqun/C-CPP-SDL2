#ifndef HERO_H
#define HERO_H

#include "texture.h"

class Hero
{
    int x, y;
    Uint8 counter;
    SDL_Rect* rect;
    Texture* texture;

public:

    Hero();
    ~Hero();

    void load( SDL_Renderer* &renderer, Uint16 w, Uint16 h );
    void event( SDL_Event &e, Uint16 w, Uint16 h );
    void render( SDL_Renderer* &renderer );
};

#endif // HERO_H
