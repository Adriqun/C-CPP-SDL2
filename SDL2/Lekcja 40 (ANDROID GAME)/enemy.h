#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "antic.h"
#include "buble.h"
#include "flown.h"
#include "texture.h"

class Enemy
{
    Texture* texture;
    SDL_Rect* rect;

    Antic antic;
    Buble buble;
    Flown flown;

    std::vector < Antic > anticVector;
    std::vector < Buble > bubleVector;
    std::vector < Flown > flownVector;

public:

    Enemy();
    ~Enemy();

    void load( SDL_Renderer* &renderer, Uint16 w );
    void event( SDL_Event &e );
    void motion( Uint16 w, Uint16 h );
    void render( SDL_Renderer* &renderer );
};

#endif // ENEMY_H
