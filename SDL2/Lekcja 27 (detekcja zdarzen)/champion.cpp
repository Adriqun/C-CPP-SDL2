#include "champion.h"

Champion::Champion()
{
    WIDTH = 50;
    HEIGHT = 50;
    VEL = 5;

    velX = 0;
    velY = 0;

    posX = 0;
    posY = 412;

    rect.w = WIDTH;
    rect.h = HEIGHT;
}

bool Champion::checkCollision( SDL_Rect a, SDL_Rect b )
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

void Champion::handleEvent( SDL_Event &e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
        case SDLK_UP:       velY -= VEL;    break;
        case SDLK_DOWN:     velY += VEL;    break;
        case SDLK_LEFT:     velX -= VEL;    break;
        case SDLK_RIGHT:    velX += VEL;    break;
        }
    }

    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
        case SDLK_UP:       velY += VEL;    break;
        case SDLK_DOWN:     velY -= VEL;    break;
        case SDLK_LEFT:     velX += VEL;    break;
        case SDLK_RIGHT:    velX -= VEL;    break;
        }
    }
}

void Champion::move( SDL_Rect &wall )
{
    posX += velX;
    rect.x = posX;

    if( ( posX < 0 ) || ( posX + WIDTH > 800 ) || checkCollision( rect, wall ) )
    {
        posX -= velX;
        rect.x = posX;
    }

    posY += velY;
    rect.y = posY;

    if( ( posY < 0 ) || ( posY + HEIGHT > 600 ) || checkCollision( rect, wall ) )
    {
        posY -= velY;
        rect.y = posY;
    }
}

void Champion::render( SDL_Renderer* &renderer )
{
    texture.render( renderer, posX, posY );
}
