#include "life.h"

Lifebar::Lifebar()
{
    rect = new SDL_Rect;
    rect->x = 0;
    rect->y = 0;
    rect->w = 0;
    rect->h = 0;

    length = 0;
    life = 0;

    red = 0;
    green = 0;
    blue = 0;
    alpha = 0;
}

Lifebar::~Lifebar()
{
    delete rect;
}

void Lifebar::setAlpha( Uint8 a )
{
    alpha = a;
}

void Lifebar::setColor( Uint8 r, Uint8 g, Uint8 b )
{
    red = r;
    green = g;
    blue = b;
}

void Lifebar::setSizes( Uint16 l, Uint16 w, Uint16 h )
{
    life = l;
    length = w / l;
    rect->w = w;
    rect->h = h;
}

void Lifebar::setXY( Uint16 x, Uint16 y )
{
    rect->x = x;
    rect->y = y;
}

bool Lifebar::isDead()
{
    if( life == 0 )
    {
        return true;
    }

    return false;
}

Uint16 Lifebar::getLife()
{
    return life;
}

void Lifebar::subtraction( Uint16 nr )
{
    life = life - nr;
}

void Lifebar::render( SDL_Renderer* &renderer )
{
    rect->w = life * length;

    SDL_SetRenderDrawColor( renderer, red, green, blue, alpha );
    SDL_RenderFillRect( renderer, rect );
}
