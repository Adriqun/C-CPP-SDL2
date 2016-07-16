#include "heart.h"
#include <stdio.h>

Hearts::Hearts()
{
    nr = 0;
    actual_nr = 0;
    alpha = 0;

    x = NULL;
    y = NULL;
    texture = NULL;
}

Hearts::~Hearts()
{
    free();
}

void Hearts::free()
{
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

    if( texture != NULL )
    {
        for( int i = 0; i < nr; i++ )
        {
            texture[ i ].free();
        }

        delete [] texture;
        texture = NULL;
    }

    nr = 0;
    actual_nr = 0;
    alpha = 0;
}


bool Hearts::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    nr = 3;
    actual_nr = 3;

    x = new int [ nr ];
    if( x == NULL )
    {
        printf( "Not created array of int\n" );
        success = false;
    }

    y = new int [ nr ];
    if( y == NULL )
    {
        printf( "Not created array of int\n" );
        success = false;
    }

    texture = new Texture[ nr ];
    if( texture == NULL )
    {
        printf( "Not created array of texture\n" );
        success = false;
    }
    else
    {
        int w, h;
        SDL_GetWindowSize( window, &w, &h );

        if( !texture[ 0 ].loadFromFile( renderer, window, "heart/1.png" ) )
        {
            success = false;
        }

        if( !texture[ 1 ].loadFromFile( renderer, window, "heart/1.png" ) )
        {
            success = false;
        }

        if( !texture[ 2 ].loadFromFile( renderer, window, "heart/1.png" ) )
        {
            success = false;
        }
    }

    return success;
}

void Hearts::render( SDL_Renderer* &renderer )
{
    for( int i = 0; i < actual_nr; i ++ )
    {
        texture[ i ].render( renderer, x[ i ], y[ i ] );
    }
}

void Hearts::set( float x, float y )
{
    this->x[ 0 ] = x - texture[ 0 ].getWidth() / 2 - 2;
    this->y[ 0 ] = y - texture[ 0 ].getHeight() - 10;

    this->x[ 1 ] = this->x[ 0 ] + texture[ 0 ].getWidth() + 2;
    this->y[ 1 ] = this->y[ 0 ];

    this->x[ 2 ] = this->x[ 1 ] + texture[ 1 ].getWidth() + 2;
    this->y[ 2 ] = this->y[ 1 ];
}

void Hearts::lose( bool yes )
{
    static int c = 0;
    c++; // :)

    if( c > 10 )
    {
        if( yes )
        {
            actual_nr --;
            c = 0;
        }
    }
}

bool Hearts::dead()
{
    if( actual_nr == 0 )
        return true;
    return false;
}

void Hearts::fadeIn()
{
    if( alpha < 250 )
    {
        alpha ++;
    }

    for( int i = 0; i < actual_nr; i ++ )
    {
        texture[ i ].setAlpha( alpha );
    }
}

void Hearts::fadeOut()
{
    if( alpha > 0 )
    {
        alpha --;
    }

    for( int i = 0; i < actual_nr; i ++ )
    {
        texture[ i ].setAlpha( alpha );
    }
}
