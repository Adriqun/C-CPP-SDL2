#include "hero.h"
#include <stdio.h>

Hero::Hero()
{
    nr = 0;
    jump = 0;
    offset = 0;

    x = 0;
    y = 0;

    rect = NULL;
    chunk = NULL;
}

Hero::~Hero()
{
    free();
}

void Hero::free()
{
    nr = 0;
    jump = 0;
    offset = 0;

    x = 0;
    y = 0;

    if( rect != NULL )
    {
        for( Uint8 i = 0; i < nr; i++ )
        {
            if( rect[ i ] != NULL )
            {
                delete rect[ i ];
                rect[ i ] = NULL;
            }
        }

        delete [] rect;
        rect = NULL;
    }

    texture.free();

    if( chunk != NULL )
    {
        Mix_FreeChunk( chunk );
        chunk = NULL;
    }
}

void Hero::control( SDL_Event &event )
{
    if( event.key.keysym.sym == SDLK_SPACE )
    {
        if( jump == 0 )
        {
            jump = 1;
        }
    }
}

void Hero::jumping( Uint16 &h )
{
    Uint8 jumpScope = 250;

    if( jump == 1 )
    {
        if( y > h - jumpScope )
        {
            y -= 7;
        }
        else
        {
            jump = 2;
        }
    }
    else if( jump == 2 )
    {
        if( y + texture.getHeight() < h - 2 )
        {
            y += 7;
        }
        else
        {
            y = h - texture.getHeight();
            jump = 0;
        }
    }

    if( jump != 0 )
    {
        offset = 5;
    }
}

bool Hero::load( SDL_Renderer* renderer, SDL_Window* window )
{
    bool success = true;

    free();

    success = texture.loadFromFile( renderer, window, "images/ninja.png" );

    nr = 8;
    rect = new SDL_Rect* [ nr ];
    for( Uint8 i = 0; i < nr; i++ )
    {
        rect[ i ] = new SDL_Rect;
    }

    for( Uint8 i = 0; i < nr; i++ )
    {
        rect[ i ]->x = texture.getWidth() / nr * i;
        rect[ i ]->y = 0;
        rect[ i ]->w = texture.getWidth() / nr;
        rect[ i ]->h = texture.getHeight();
    }

    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    x = 120;
    y = h - texture.getHeight();

    return success;
}

void Hero::render( SDL_Renderer* renderer, Uint16 h, Uint8 value )
{
    if( value == 1 )
    {
        offset ++;
        if( offset >= 3 )
        {
            offset = 0;
        }

        jumping( h );
    }

    if( value == 2 )
    {
        offset = 4;
    }

    texture.render( renderer, x, y, rect[ offset ] );
}
