#include "cloud.h"
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
        nr = 0;
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
        nr = cloud.getWidth() / 10;
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

            drop[ i ].loadFromFile( renderer, window, "wall/storm/drop.png" );
            drop[ i ].setHeight( rand() % 15 + 3 );
            drop[ i ].setAlpha( rand() % 50 + 1 );

            x[ i ] = (division * i) + posX;
            y[ i ] = rand() % cloud.getHeight() + cloud.getHeight() / 2;
        }
    }

    return success;
}

void Cloud::random( int &w, int &h )
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



    for( Uint8 i = 0; i < nr; i ++ )
    {
        if( y[ i ] > h )
            y[ i ] = rand() % cloud.getHeight() + cloud.getHeight() / 2;

        y[ i ] += gravity[ i ];
        x[ i ] += vel;
    }
}

void Cloud::render( SDL_Renderer* &renderer )
{
    if( alpha > 100 )
        alpha --;

    cloud.setAlpha( alpha );

    for( Uint8 i = 0; i < nr; i ++ )
    {
        drop[ i ].render( renderer, x[ i ], y[ i ] );
    }

    cloud.render( renderer, posX, 0 );
}

void Cloud::lightning()
{
    alpha = 255;
}

void Cloud::fadeOut( SDL_Renderer* &renderer )
{
    static Uint8 a = 250;

    if( a > 0 )
        a--;

    cloud.setAlpha( a );
    cloud.render( renderer, posX, posY  );
    for( Uint8 i = 0; i < nr; i ++ )
    {
        drop[ i ].setAlpha( a );
        drop[ i ].render( renderer, x[ i ], y[ i ] );
    }
}
