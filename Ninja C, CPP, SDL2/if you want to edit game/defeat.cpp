#include "defeat.h"
#include <stdio.h>
#include "font.h"

Defeat::Defeat()
{
    nr = 0;

    x = NULL;
    y = NULL;
    texture = NULL;

    alpha = 0;
    state = 1;
}

Defeat::~Defeat()
{
    free();
}

void Defeat::free()
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
    click.free();

    alpha = 0;
    state = 1;
}


bool Defeat::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    Font* font = new Font;
    if( !font->load( "menu/hulk.ttf", 150 ) )
    {
        success = false;
    }
    else
    {
        nr = 4;

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


        int w, h;
        SDL_GetWindowSize( window, &w, &h );


        // BACKGROUND
        if( !texture[ 0 ].createWithColor( renderer, 0x15, 0x15, 0x1D, w, h ) )
        {
            success = false;
        }
        else
        {
            x[ 0 ] = 0;
            y[ 0 ] = 0;
        }

        SDL_Color color = { 0x78, 0x78, 0x78 };
        if( !texture[ 1 ].loadFromRenderedText( renderer, font->get(), "Menu", color ) )
        {
            success = false;
        }
        else
        {
            x[ 1 ] = (w / 2) - (texture[ 1 ].getWidth() / 2);
            y[ 1 ] = (h / 2) - texture[ 1 ].getHeight() - 10;
        }


        if( !texture[ 2 ].loadFromRenderedText( renderer, font->get(), "Replay", color ) )
        {
            success = false;
        }
        else
        {
            x[ 2 ] = (w / 2) - (texture[ 2 ].getWidth() / 2);
            y[ 2 ] = h / 2;
        }

        if( !texture[ 3 ].loadFromFile( renderer, window, "defeat/dead.png" ) )
        {
            success = false;
        }
        else
        {
            x[ 3 ] = x[ 1 ] - texture[ 3 ].getWidth() - 10;
            y[ 3 ] = y[ 1 ] + texture[ 3 ].getHeight() / 2;
        }
    }

    delete font;
    font = NULL;

    if( !click.load( "menu/click.wav", 120 ) )
    {
        success = false;
    }

    return success;
}

void Defeat::render( SDL_Renderer* &renderer )
{
    if( alpha < 250 )
        alpha ++;

    for( int i = 0; i < nr; i ++ )
    {
        texture[ i ].setAlpha( alpha );
        texture[ i ].render( renderer, x[ i ], y[ i ] );
    }
}


int Defeat::control()
{
    static int counter = 0;
    static const Uint8* key = SDL_GetKeyboardState( NULL );

    if( counter < 10 )
    {
        counter ++;
    }
    else
    {
        if( key[ SDL_SCANCODE_UP ] )
        {
            if( state == 2 )
            {
                click.play();
                counter = 0;
                state = 1;
            }
        }
        else if( key[ SDL_SCANCODE_DOWN ] )
        {
            if( state == 1 )
            {
                click.play();
                counter = 0;
                state = 2;
            }
        }
        else if( key[ SDL_SCANCODE_RETURN ] )
        {
            click.play();
            counter = 0;
            state += 2;
        }
    }

    x[ 3 ] = x[ state ] - texture[ 3 ].getWidth() - 10;
    y[ 3 ] = y[ state ] + texture[ 3 ].getHeight() / 2;

    // printf( "%d %d\n", x[ 3 ], y[ 3 ] );

    return state - 3;
}
