#ifndef FLOWN_H
#define FLOWN_H

#include "life.h"
#include "texture.h"
#include "random.h"

class Flown
{
    int x, y;
    float posX, posY, vel;
    Uint8 slow, hit;
    SDL_Rect* rect;

    Lifebar* lifebar;
    Texture* texture;
    Random* random;

public:

    Flown();
    ~Flown();

    bool isDead();
    void setVel( float v );

    void load( SDL_Renderer* &renderer, Uint16 w );
    bool event( SDL_Event &e );
    void motion( Uint16 w, Uint16 h );
    void render( SDL_Renderer* &renderer );
};

#endif // FLOWN_H
