#include "monster.h"
#include <stdio.h>
#include <cstdlib>

Monster::Monster( int end, int nr, string path )
{
    this->end = end;
    this->nr = nr;
    vel = 0;

    x = 0;
    y = 0;

    rect = NULL;
    flip = SDL_FLIP_NONE;

    direction = 0;
    this->path = path;

    offset = 0;
    delay = 0;

    hit = false;
    alpha = 0;
}

Monster::~Monster()
{
    free();
}

void Monster::free()
{
    x = 0;
    y = 0;

    if( rect != NULL )
    {
        for( int i = 0; i < nr; i ++ )
        {
            delete rect[ i ];
            rect[ i ] = NULL;
        }

        delete [] rect;
        rect = NULL;
    }

    flip = SDL_FLIP_NONE;
    direction = 0;
    texture.free();

    offset = 0;
    delay = 0;
    hit = false;
    alpha = 0;
}


void Monster::faster()
{
    if( alpha == 250 )
        x -= 1;

    x -= ( vel + 2 );
}

void Monster::mechanics()
{
    if( !hit )
    {
        if( direction == 1 )
        {
            x -= vel;
        }
        else
        {
            x += vel;
        }

        if( offset < (end-1) * delay )
            offset ++;
        else
            offset = 0;
    }
    else
    {
        offset = end * delay;
        if( alpha > 0 )
            alpha --;

        texture.setAlpha( alpha );
    }
}

bool Monster::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    if( !texture.loadFromFile( renderer, window, path ) )
    {
        success = false;
    }
    else
    {
        vel = rand() % 3 + 1;

        int w, h;
        SDL_GetWindowSize( window, &w, &h );

        y = rand() % h + 1;
        x = rand() % w + w;

        // printf( "x %d   y %d\n", x, y );

        direction = rand() % 2;

        if( direction == 0 )
        {
            x = -x;
            flip = SDL_FLIP_NONE;
        }
        else
        {
            flip = SDL_FLIP_HORIZONTAL;
        }

        delay = 5;
    }

    rect = new SDL_Rect* [ nr ];
    if( rect == NULL )
    {
        printf( "Not created array of SDL_Rect\n" );
        success = false;
    }
    else
    {
        for( int i = 0; i < nr; i ++ )
        {
            rect[ i ] = new SDL_Rect;
            rect[ i ]->h = texture.getHeight();
            rect[ i ]->w = texture.getWidth() / nr;
            rect[ i ]->x = texture.getWidth() / nr * i;
            rect[ i ]->y = 0;
        }
        alpha = 250;
    }

    return success;
}

void Monster::render( SDL_Renderer* &renderer )
{
    texture.render( renderer, x, y, rect[ offset / delay ], 0.0, NULL, flip );

    // printf( "x %f  y %f\n", x, y );
}

void Monster::setHit()
{
    hit = true;
}

SDL_Rect Monster::getRect()
{
    SDL_Rect r;

    r.w = texture.getWidth() / nr;
    r.h = texture.getHeight();
    r.x = x;
    r.y = y;

    return r;
}

Uint8 Monster::getDirection()
{
    return direction;
}

Uint8 Monster::getAlpha()
{
    return alpha;
}

