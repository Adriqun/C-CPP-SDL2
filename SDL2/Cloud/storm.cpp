#include "storm.h"
#include <stdio.h>
#include <cstdlib>
#include <time.h>

Storm::Storm()
{
    nr = 0;
    counter = 0;

    cloud = NULL;
}

Storm::~Storm()
{
    free();
}

void Storm::free()
{
    nr = 0;
    counter = 0;

    if( cloud != NULL)
    {
        for( Uint8 i = 0; i < nr; i ++ )
        {
            cloud[ i ].free();
        }

        delete [] cloud;
        cloud = NULL;
    }
}

bool Storm::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    srand( static_cast <int> (time( NULL )) );

    nr = 9;
    cloud = new Cloud [ nr ];

    for( Uint8 i = 0; i < nr; i ++ )
    {
        std::string line = "storm/";
        line += static_cast <char> ( i + 48 );
        line += ".png";

        if( !cloud[ i ].load( renderer, window, line ) )
        {
            success = false;
        }
    }

    return success;
}

void Storm::render( SDL_Renderer* &renderer, int &w, int &h )
{
    if( counter == 0 )
    {
        cloud[ rand() % 9 ].lightning();
    }

    counter ++;

    if( counter == 300 )
        counter = 0;

    for( Uint8 i = 0; i < nr; i ++ )
    {
        cloud[ i ].render( renderer, w, h );
    }
}
