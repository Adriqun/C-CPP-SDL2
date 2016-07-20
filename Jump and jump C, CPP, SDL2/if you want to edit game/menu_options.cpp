#include "menu_options.h"
#include <stdio.h>

Options::Options()
{
    nr = 0;
    text = NULL;
}

Options::~Options()
{
    free();
}

void Options::free()
{
    if( text != NULL )
    {
        for( int i = 0; i < nr; i++ )
        {
            text[ i ].free();
        }

        delete [] text;
        text = NULL;

        nr = 0;
    }
}

bool Options::load( SDL_Renderer* &renderer,  SDL_Window* &window )
{
    bool success = true;

    free();

    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    nr = 13;
    text = new Text [ nr ];
    if( text == NULL )
    {
        printf( "Not created array of text\n" );
        success = false;
    }
    else
    {
        // short info
        if( !text[ 0 ].loadFont( "menu/[z] Arista.ttf", 30, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ 0 ].createTexture( renderer, "write to me: adrmic98@gmail.com" ) )
        {
            success = false;
        }
        else
        {
            text[ 0 ].setX( w - text[ 0 ].getWidth() );
            text[ 0 ].setY( h - text[ 0 ].getHeight() );
        }


        // short info
        if( !text[ 1 ].loadFont( "menu/[z] Arista.ttf", 30, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ 1 ].createTexture( renderer, "16 July 2016" ) )
        {
            success = false;
        }
        else
        {
            text[ 1 ].setX( 0 );
            text[ 1 ].setY( h - text[ 1 ].getHeight() );
        }


        if( !text[ 2 ].loadFont( "menu/hulk.ttf", 80, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ 2 ].createTexture( renderer, "BEFORE" ) )
        {
            success = false;
        }
        else
        {
            text[ 2 ].setX( 85 );
            text[ 2 ].setY( 88 );
        }


        if( !text[ 3 ].loadFont( "menu/hulk.ttf", 40, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ 3 ].createTexture( renderer, "Go INTO - key [ RETURN ]" ) )
        {
            success = false;
        }
        else
        {
            text[ 3 ].setX( 137 );
            text[ 3 ].setY( text[ 2 ].getY() + text[ 2 ].getHeight() );
        }


        if( !text[ 4 ].loadFont( "menu/hulk.ttf", 40, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ 4 ].createTexture( renderer, "GO UP - KEY [ UP ]" ) )
        {
            success = false;
        }
        else
        {
            text[ 4 ].setX( text[ 3 ].getX() );
            text[ 4 ].setY( text[ 3 ].getY() + text[ 3 ].getHeight() );
        }


        if( !text[ 5 ].loadFont( "menu/hulk.ttf", 40, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ 5 ].createTexture( renderer, "GO DOWN - KEY [ DOWN ]" ) )
        {
            success = false;
        }
        else
        {
            text[ 5 ].setX( text[ 4 ].getX() );
            text[ 5 ].setY( text[ 4 ].getY() + text[ 4 ].getHeight() );
        }


        if( !text[ 6 ].loadFont( "menu/hulk.ttf", 80, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ 6 ].createTexture( renderer, "DURING" ) )
        {
            success = false;
        }
        else
        {
            text[ 6 ].setX( 107 );
            text[ 6 ].setY( 312 );
        }


        if( !text[ 7 ].loadFont( "menu/hulk.ttf", 40, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ 7 ].createTexture( renderer, "idle - key [ null ]" ) )
        {
            success = false;
        }
        else
        {
            text[ 7 ].setX( 169 );
            text[ 7 ].setY( text[ 6 ].getY() + text[ 6 ].getHeight() );
        }


        if( !text[ 8 ].loadFont( "menu/hulk.ttf", 40, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ 8 ].createTexture( renderer, "move left - key [ left || a ]" ) )
        {
            success = false;
        }


        if( !text[ 9 ].loadFont( "menu/hulk.ttf", 40, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ 9 ].createTexture( renderer, "move right - key [ right || d ]" ) )
        {
            success = false;
        }


        if( !text[ 10 ].loadFont( "menu/hulk.ttf", 40, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ 10 ].createTexture( renderer, "jump - key [ up || w ]" ) )
        {
            success = false;
        }


        if( !text[ 11 ].loadFont( "menu/hulk.ttf", 40, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ 11 ].createTexture( renderer, "attack - key [ space || return ]" ) )
        {
            success = false;
        }

        if( !text[ nr-1 ].loadFont( "menu/hulk.ttf", 40, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ nr-1 ].createTexture( renderer, "pause - key [ p ]" ) )
        {
            success = false;
        }

        for( int i = 8; i < nr; i++ )
        {
            text[ i ].setX( text[ i-1 ].getX() );
            text[ i ].setY( text[ i-1 ].getY() + text[ i-1 ].getHeight() );
        }
    }

    return success;
}

void Options::render( SDL_Renderer* &renderer )
{
    for( int i = 0; i < nr; i++ )
    {
        text[ i ].render( renderer );
    }
}


void Options::fadeIO( int value )
{
    for( int i = 0; i < nr; i++ )
    {
        text[ i ].fadeIO( value );
    }
}
