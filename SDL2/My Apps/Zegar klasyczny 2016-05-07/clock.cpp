#include "clock.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <SDL_image.h>

Clock::Clock()
{
    nr = 0;
    rect = NULL;
    texture = NULL;
}

Clock::~Clock()
{
    free();
}



void Clock::free()
{
    if( texture != NULL )
    {
        for( Uint8 i = 0; i < nr; i++ )
        {
            SDL_DestroyTexture( texture[ i ] );
            texture[ i ] = NULL;
        }

        delete [] texture;
        texture = NULL;
    }

    delete [] rect;
    rect = NULL;

    nr = 0;
}

std::string Clock::getTime()
{
    std::string newTime;

    time_t czas;
    struct tm* data;
    char moment[ 7 ];

    time( &czas );
    data = localtime( &czas );

    strftime( moment, 7, "%H%M%S", data );

    newTime = moment;

    return newTime;
}

int Clock::stringToInt( std::string &path )
{
    int num = 0, buf;

    for( Uint8 i = 0 ; i < path.size(); i++ )
    {
        if( path[ i ] == '-' )
            i ++;

        buf = static_cast < int > ( path[ i ] ) - 48;
        for( Uint8 j = 1; j < path.size() - i; j ++ )
            buf *= 10;
        num += buf;
    }

    if( path[ 0 ] == '-')
    {
        num *= -1;
    }

    return num;
}

SDL_Texture* Clock::loadTexture( SDL_Renderer* &renderer, std::string path, SDL_Rect &dstrect )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* surface = IMG_Load( path.c_str() );
    if( surface == NULL )
    {
        printf( "Nie wczytano powierzchni z %s Error %s", path.c_str(), IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, surface );
        if( newTexture == NULL )
        {
            printf( "Nie utworzono tekstury z %s Error %s", path.c_str(), SDL_GetError() );
        }
        else
        {
            dstrect.w = surface ->w;
            dstrect.h = surface ->h;
        }
    }
    SDL_FreeSurface( surface );
    surface = NULL;

    return newTexture;
}


bool Clock::load( SDL_Renderer* renderer, SDL_Window* window )
{
    bool success = true;

    free();

    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    nr = 4;
    texture = new SDL_Texture* [ nr ];
    rect = new SDL_Rect [ nr - 1 ];

    texture[ 0 ] = loadTexture( renderer, "clock/2.png", rect[ 0 ] );
    if( texture[ 0 ] == NULL )
    {
        success = false;
    }

    texture[ 1 ] = loadTexture( renderer, "clock/0.png", rect[ 0 ] );
    if( texture[ 1 ] == NULL )
    {
        success = false;
    }
    else
    {
        rect[ 0 ].x = w / 2 - rect[ 0 ].w / 2;
        rect[ 0 ].y = h / 2 - rect[ 0 ].h / 2;
    }

    texture[ 2 ] = loadTexture( renderer, "clock/1.png", rect[ 1 ] );
    if( texture[ 2 ] == NULL )
    {
        success = false;
    }
    else
    {
        rect[ 1 ].x = w / 2 - rect[ 1 ].w / 2;
        rect[ 1 ].y = h / 2 - rect[ 1 ].h / 2;
    }

    texture[ 3 ] = loadTexture( renderer, "clock/3.png", rect[ 2 ] );
    if( texture[ 3 ] == NULL )
    {
        success = false;
    }
    else
    {
        rect[ 2 ].x = w / 2 - rect[ 2 ].w / 2;
        rect[ 2 ].y = h / 2 - rect[ 2 ].h / 2;
    }


    return success;
}

void Clock::render( SDL_Renderer* renderer )
{
    SDL_RenderCopy( renderer, texture[ 0 ], NULL, NULL );

    std::string path = getTime();
    int nr = ( static_cast< char >( path[ 0 ] ) - 48 ) * 10;
    nr += static_cast< char >( path[ 1 ] ) - 48;
    if( nr >= 12 )  nr -= 12;
    double angle = nr * 30 - 90;
    SDL_RenderCopyEx( renderer, texture[ 1 ], NULL, &rect[ 0 ], angle, NULL, SDL_FLIP_NONE );


    nr = ( static_cast< char >( path[ 2 ] ) - 48 ) * 10;
    nr += static_cast< char >( path[ 3 ] ) - 48;
    angle = nr * 6 - 90;
    SDL_RenderCopyEx( renderer, texture[ 2 ], NULL, &rect[ 1 ], angle, NULL, SDL_FLIP_NONE );


    nr = ( static_cast< char >( path[ 4 ] ) - 48 ) * 10;
    nr += static_cast< char >( path[ 5 ] ) - 48;
    angle = nr * 6 - 90;
    SDL_RenderCopyEx( renderer, texture[ 3 ], NULL, &rect[ 2 ], angle, NULL, SDL_FLIP_NONE );
}
