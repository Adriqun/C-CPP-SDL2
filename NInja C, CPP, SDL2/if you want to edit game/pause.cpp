#include "pause.h"
#include <stdio.h>

Pause::Pause()
{
    nr = 0;
    state = 0;
    alpha = 0;

    x = NULL;
    y = NULL;
    texture = NULL;
}

Pause::~Pause()
{
    free();
}

void Pause::free()
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
    state = 0;
    alpha = 0;
}


bool Pause::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    nr = 2;

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
        if( !texture[ 0 ].loadFromFile( renderer, window, "pause/0.png" ) )
        {
            success = false;
        }
        else
        {
            y[ 0 ] = 0;
            x[ 0 ] = 0;
        }

        if( !texture[ 1 ].loadFromFile( renderer, window, "pause/1.png" ) )
        {
            success = false;
        }
        else
        {
            y[ 1 ] = 0;
            x[ 1 ] = 0;
        }
    }

    return success;
}

void Pause::render( SDL_Renderer* &renderer )
{
    texture[ state ].render( renderer, x[ state ], y[ state ] );
}

void Pause::control()
{
    static const Uint8* key = SDL_GetKeyboardState( NULL );
    static int counter = 0;

    if( counter < 10 )
        counter ++;
    else
    {
        if( key[ SDL_SCANCODE_P ] )
        {
            if( state < 1 )
                state ++;
            else
                state --;
            counter = 0;
        }
    }
}


void Pause::fadeIn()
{
    if( alpha < 250 )
    {
        alpha ++;
    }

    for( int i = 0; i < nr; i ++ )
    {
        texture[ i ].setAlpha( alpha );
    }
}

void Pause::fadeOut()
{
    if( alpha > 0 )
    {
        alpha --;
    }

    for( int i = 0; i < nr; i ++ )
    {
        texture[ i ].setAlpha( alpha );
    }
}

int Pause::getState()
{
    return state;
}
