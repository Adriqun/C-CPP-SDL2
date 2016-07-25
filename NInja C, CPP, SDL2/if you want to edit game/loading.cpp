#include "loading.h"
#include "font.h"
#include <stdio.h>

Loading::Loading()
{
    counter = 1;

    x = NULL;
    y = NULL;
    texture = NULL;
}

Loading::~Loading()
{
    free();
}

void Loading::free()
{
    counter = 1;

    if( texture != NULL )
    {
        for( int i = 0; i < nr; i++ )
        {
            texture[ i ].free();
        }

        delete [] texture;
        texture = NULL;
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
}

bool Loading::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    Font* font = new Font;
    if( !font->load( "intro/Jaapokki-Regular.otf", 40 ) )
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
        if( !texture[ BACKGROUND ].createWithColor( renderer, 0x15, 0x15, 0x1D, w, h ) )
        {
            success = false;
        }
        else
        {
            y[ BACKGROUND ] = 0;
            x[ BACKGROUND ] = 0;
        }


        // Our text loading
        SDL_Color white = { 0xFF, 0xFF, 0xFF };
        if( !texture[ LOADING ].loadFromRenderedText( renderer, font->get(), "Loading", white ) )
        {
            success = false;
        }
        else
        {
            x[ LOADING ] = (w / 2) - (texture[ LOADING ].getWidth() / 2);
            y[ LOADING ] = (h / 2) - (texture[ LOADING ].getHeight() / 2);
        }


        // Our white bar
        if( !texture[ WHITE_BAR ].createWithColor( renderer, 0xFF, 0xFF, 0xFF, 300, 50 ) )
        {
            success = false;
        }
        else
        {
            x[ WHITE_BAR ] = (w / 2) - (texture[ WHITE_BAR ].getWidth() / 2);
            y[ WHITE_BAR ] = y[ LOADING ] + texture[ LOADING ].getHeight() + 10;
        }


        // Our green bar
        if( !texture[ GREEN_BAR ].createWithColor( renderer, 0x70, 0xB7, 0x59, 1, 50 ) )
        {
            success = false;
        }
        else
        {
            x[ GREEN_BAR ] = x[ WHITE_BAR ];
            y[ GREEN_BAR ] = y[ WHITE_BAR ];
        }
    }

    // Free font
    delete font;
    font = NULL;

    return success;
}

void Loading::render( SDL_Renderer* &renderer, int state )
{
    texture[ GREEN_BAR ].setWidth( texture[ WHITE_BAR ].getWidth() *  counter / state );

    for( Uint8 i = 0; i < nr; i++ )
    {
        texture[ i ].render( renderer, x[ i ], y[ i ] );
    }

    counter ++;
}
