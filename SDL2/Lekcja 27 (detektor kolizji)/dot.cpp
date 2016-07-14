#include "dot.h"

Dot::Dot()
{
    DOT_VEL = 3;

    collider.w = 20;
    collider.h = 20;

    velX = 0;
    velY = 0;
};

bool Dot::checkCollision( SDL_Rect a, SDL_Rect b )
{
    if( a.y + a.h <= b.y )
        return false;

    if( a.y >= b.y + b.h )
        return false;

    if( a.x + a.w <= b.x )
        return false;

    if( a.x >=  b.x + b.w )
        return false;

    return true;
}

void Dot::handleEvent()
{
    const Uint8* key = SDL_GetKeyboardState( NULL );

    if( key[ SDL_SCANCODE_D ] )         velX = DOT_VEL;
    else if( key[ SDL_SCANCODE_A ] )    velX = DOT_VEL * -1;
    else                                velX = 0;

    if( key[ SDL_SCANCODE_W ] )         velY = DOT_VEL * -1;
    else if( key[ SDL_SCANCODE_S ] )    velY = DOT_VEL;
    else                                velY = 0;

    collider.x += velX;
    collider.y += velY;
}

void Dot::move( SDL_Rect wall, int scr_wid, int scr_hei )
{
    if( ( collider.y < 0 ) || ( collider.y + collider.h > scr_hei ) || checkCollision( collider, wall ) )
        collider.y -= velY;

    if( ( collider.x < 0 ) || ( collider.x + collider.w > scr_wid ) || checkCollision( collider, wall ) )
        collider.x -= velX;
}

void Dot::render( SDL_Renderer* &renderer )
{
    dotTexture.render( renderer, collider.x, collider.y );
}
