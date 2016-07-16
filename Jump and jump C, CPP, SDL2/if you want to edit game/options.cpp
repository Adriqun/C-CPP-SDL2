#include "options.h"
#include <stdio.h>
#include "font.h"

using namespace std;

Options::Options()
{
    nr = 0;

    x = NULL;
    y = NULL;
    texture = NULL;
}

Options::~Options()
{
    free();
}

void Options::free()
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
        nr = 0;
    }
}


bool Options::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    nr = 3;

    Font* font = new Font;
    if( !font->load( "menu/[z] Arista.ttf", 30 ) )
    {
        success = false;
    }
    else
    {
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

        // Our background texture
        if( !texture[ 0 ].loadFromFile( renderer, window, "menu/options.png" ) )
        {
            success = false;
        }
        else
        {
            y[ 0 ] = 0;
            x[ 0 ] = 0;
        }

        int w, h;
        SDL_GetWindowSize( window, &w, &h );

        // special info
        SDL_Color gray = { 0x78, 0x78, 0x78 };
        if( !texture[ 1 ].loadFromRenderedText( renderer, font->get(), "write to me: adrmic98@gmail.com", gray ) )
        {
            success = false;
        }
        else
        {
            y[ 1 ] = h - texture[ 1 ].getHeight();
            x[ 1 ] = w - texture[ 1 ].getWidth();
        }

        // special info also
        if( !texture[ 2 ].loadFromRenderedText( renderer, font->get(), "16 July 2016", gray ) )
        {
            success = false;
        }
        else
        {
            y[ 2 ] = h - texture[ 2 ].getHeight();
            x[ 2 ] = 0;
        }

        delete font;
        font = NULL;

    }

    return success;
}

void Options::render( SDL_Renderer* &renderer )
{
    for( int i = 0; i < nr; i++ )
    {
        texture[ i ].render( renderer, x[ i ], y[ i ] );
    }
}
