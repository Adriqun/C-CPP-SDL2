#include "cloud.h"
#include <time.h>
#include <stdio.h>
#include <cstdlib>

Cloud::Cloud()
{

    nr = 0;
    alpha = 100;
    gravity = NULL;

    x = NULL;
    y = NULL;
    drop = NULL;

    vel = 0;
    posX = 0;
    posY = 0;
}

Cloud::~Cloud()
{
    free();
}

void Cloud::free()
{
    nr = 0;
    alpha = 100;
    vel = 0;
    posX = 0;
    posY = 0;

    if( drop != NULL )
    {
        for( Uint8 i = 0; i < nr; i++ )
        {
            drop[ i ].free();
        }

        delete [] drop;
        drop = NULL;
    }

    if( x != NULL )
    {
        delete [] x;
        x = NULL;
    }

    if( y != NULL )
    {
        delete [] y;
        y = NULL;
    }

    if( gravity != NULL )
    {
        delete [] gravity;
        gravity = NULL;
    }

    cloud.free();
}

bool Cloud::load( SDL_Renderer* &renderer, SDL_Window* &window, std::string path )
{
    bool success = true;

    free();

    if( !cloud.loadFromFile( renderer, window, path ) )
    {
        success = false;
    }
    else
    {
        nr = cloud.getWidth() / 5;
        vel = rand() % 2 + 1;

        int w, h;
        SDL_GetWindowSize( window, &w, &h );

        posX = rand() % w - w;
        posY = rand() % 40;


        gravity = new Uint8 [ nr ];
        x = new int16_t [ nr ];
        y = new int16_t [ nr ];
        drop = new Texture [ nr ];

        int16_t division = cloud.getWidth() / nr;

        for( Uint8 i = 0; i < nr; i ++ )
        {
            gravity[ i ] = rand() % 9 + 7;

            drop[ i ].loadFromFile( renderer, window, "storm/drop.png" );
            drop[ i ].setHeight( rand() % 15 + 3 );
            drop[ i ].setAlpha( rand() % 250 + 1 );

            x[ i ] = (division * i) + posX;
            y[ i ] = rand() % cloud.getHeight() + cloud.getHeight() / 2;
        }
    }

    return success;
}

void Cloud::render( SDL_Renderer* &renderer, int &w, int &h )
{
    posX += vel;

    if( posX > w )
    {
        vel = rand() % 2 + 1;
        posY = rand() % 40 - 40;
        posX -= (w + cloud.getWidth());
        for( Uint8 i = 0; i < nr; i ++ )
        {
            x[ i ] -= (w + cloud.getWidth());
        }
    }

    if( alpha > 100 )
        alpha --;

    for( Uint8 i = 0; i < nr; i ++ )
    {
        drop[ i ].render( renderer, x[ i ], y[ i ] );

        if( y[ i ] > h )
            y[ i ] = rand() % cloud.getHeight() + cloud.getHeight() / 2;

        y[ i ] += gravity[ i ];
        x[ i ] += vel;
    }

    cloud.setAlpha( alpha );
    cloud.render( renderer, posX, 0 );
}

void Cloud::lightning()
{
    alpha = 255;
}
