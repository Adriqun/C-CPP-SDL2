#include "storm.h"
#include <stdio.h>
#include <cstdlib>


Storm::Storm()
{
    nr = 0;
    c_nr = 0;
    counter = 0;

    cloud = NULL;
    chunk = NULL;
}

Storm::~Storm()
{
    free();
}

void Storm::free()
{
    counter = 0;

    if( cloud != NULL)
    {
        for( Uint8 i = 0; i < nr; i ++ )
        {
            cloud[ i ].free();
        }

        delete [] cloud;
        cloud = NULL;
        nr = 0;
    }

    if( chunk != NULL)
    {
        for( Uint8 i = 0; i < c_nr; i ++ )
        {
            chunk[ i ].free();
        }

        delete [] chunk;
        chunk = NULL;
    }

    blank.free();
}

bool Storm::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    nr = 9;
    cloud = new Cloud [ nr ];

    for( Uint8 i = 0; i < nr; i ++ )
    {
        std::string line = "wall/storm/";
        line += static_cast <char> ( i + 48 );
        line += ".png";

        if( !cloud[ i ].load( renderer, window, line ) )
        {
            success = false;
        }
    }

    c_nr = 3;
    chunk = new Chunk [ c_nr ];

    if( !chunk[ 0 ].load( "wall/storm/0.wav", 50 ) )
    {
        success = false;
    }

    if( !chunk[ 1 ].load( "wall/storm/1.wav", 50 ) )
    {
        success = false;
    }

    if( !chunk[ 2 ].load( "wall/storm/2.wav", 50 ) )
    {
        success = false;
    }

    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    if( !blank.createWithColor( renderer, 0xFF, 0xFF, 0xFF, w, h  ) )
    {
        success = false;
    }

    return success;
}

void Storm::render( SDL_Renderer* &renderer )
{
    for( Uint8 i = 0; i < nr; i ++ )
    {
        cloud[ i ].render( renderer );
    }
}

void Storm::fadeOut( SDL_Renderer* &renderer )
{
    for( Uint8 i = 0; i < nr; i ++ )
    {
        cloud[ i ].fadeOut( renderer );
    }
}

void Storm::halt()
{
    static int c = 50;
    for( Uint8 i = 0; i < c_nr; i ++ )
    {
        chunk[ i ].setVolume( c );
    }

    c--;
}

void Storm::random( SDL_Renderer* &renderer, int w, int h )
{
    if( counter == 0 )
    {
        blank.render( renderer, 0, 0 );
        chunk[ rand() % 3 ].play();
        cloud[ rand() % 9 ].lightning();
    }

    counter ++;

    if( counter == 1000 )
    {
        counter = 0;
    }

    for( Uint8 i = 0; i < nr; i ++ )
    {
        cloud[ i ].random( w, h );
    }
}
