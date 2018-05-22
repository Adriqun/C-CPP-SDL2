#ifndef LIFE_H
#define LIFE_H

#include <SDL.h>

class Lifebar
{
    SDL_Rect* rect;
    Uint16 length, life;
    Uint8 red, green, blue, alpha;

public:

    Lifebar();
    ~Lifebar();

    void setAlpha( Uint8 a );
    void setColor( Uint8 r, Uint8 g, Uint8 b );
    void setSizes( Uint16 l, Uint16 w, Uint16 h );
    void setXY( Uint16 x, Uint16 y );

    bool isDead();
    Uint16 getLife();
    void subtraction( Uint16 nr );
    void render( SDL_Renderer* &renderer );
};

#endif // LIFE_H
