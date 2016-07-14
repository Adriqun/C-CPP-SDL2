#include "hero.h"
#include <math.h>

Hero::Hero()
{
    counter = 0;

    rect = NULL;
    rect = new SDL_Rect;

    rect->x = 0;
    rect->y = 0;
    rect->w = 0;
    rect->h = 0;

    texture = new Texture( 0 );
}

Hero::~Hero()
{
    delete texture;
    texture = NULL;

    delete rect;
    rect = NULL;
}

void Hero::load( SDL_Renderer* &renderer, Uint16 w, Uint16 h )
{
    texture->setTexture( renderer, "hero/0.png" );
    rect->w = texture->getWidth();
    rect->h = texture->getHeight();

    rect->x = w / 2 - rect->w / 2;
    rect->y = h - rect->h - 100;
}

void Hero::event( SDL_Event &e, Uint16 w, Uint16 h )
{
    if( e.type == SDL_MOUSEBUTTONDOWN ) // SDL_MOUSEBUTTONDOWN SDL_FINGERDOWN
    {
        x = e.tfinger.x * w;
        y = e.tfinger.y * h;
        SDL_GetMouseState( &x, &y );

        texture->setAngle( atan2( static_cast<double>( ( rect->y + rect->h / 2 ) - y ), static_cast<double>( ( rect->x + rect->w / 2 ) - x ) ) * ( 180 / M_PI ) - 90 );
        if( counter == 0 )
        {
            counter = 1;
        }
    }
}

void Hero::render( SDL_Renderer* &renderer )
{
    if( counter > 0 && counter < 5 )      rect->y += 4;
    else if( counter > 4 && counter < 9 ) rect->y -= 4;
    else                                  counter = 0;

    if( counter != 0 )
    {
        counter ++;
        SDL_RenderDrawLine( renderer, rect->x + rect->w / 2, rect->y + rect->h / 2, x, y );
    }

    texture->render( renderer, rect );
}
