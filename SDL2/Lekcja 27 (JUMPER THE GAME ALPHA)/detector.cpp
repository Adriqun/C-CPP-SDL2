#include "detector.h"

bool Detector::checkCollision( SDL_Rect &a, SDL_Rect &b )
{
    if( a.y + a.h - 5 <= b.y )
        return false;

    if( a.y + 5 >= b.y + b.h )
        return false;

    if( a.x + a.w - 5 <= b.x )
        return false;

    if( a.x + 5 >=  b.x + b.w )
        return false;

    return true;
}

SDL_Rect Detector::setRect( SDL_Rect a, SDL_Rect b, Uint16 &w, Uint16 &h, float velX, float velY )
{
    if( ( a.y < 0 ) || ( a.y + a.h > h ) || checkCollision( a, b ) )
        a.y -= velY;

    if( ( a.x < 0 ) || ( a.x + a.w > w ) || checkCollision( a, b ) )
        a.x -= velX;

    return a;
}
