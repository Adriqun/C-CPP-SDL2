#include "core.h"
#include <stdio.h>
#include <windows.h>

bool Core::initSDL( Uint32 flags )
{
    bool success = true;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Nie zainicjowano SDL! Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 15 );
        printf( "Zainicjowano biblioteke SDL!\n" );
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
    }

    return success;
}

bool Core::initIMG( int flags )
{
    bool success = true;

    if( !(IMG_Init( flags )&flags ) )
    {
        printf( "Nie zainicjowano IMG! Error: %s\n", IMG_GetError() );
        success = false;
    }
    else
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 15 );
        printf( "Zainicjowano biblioteke SDL_image!\n" );
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
    }

    return success;
}

bool Core::initMIX( int frequency, Uint16 format, int channels, int chunksize )
{
    bool success = true;

    if( Mix_OpenAudio( frequency, format, channels, chunksize ) < 0 )
    {
        printf( "Nie zainicjowano MIX! Error: %s\n", Mix_GetError() );
        success = false;
    }
    else
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 15 );
        printf( "Zainicjowano biblioteke SDL_mixer!\n" );
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
    }

    return success;
}

bool Core::initTTF()
{
    bool success = true;

    if( TTF_Init() < 0 )
    {
        printf( "Nie zainicjowano TTF! Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 15 );
        printf( "Zainicjowano biblioteke SDL_ttf!\n" );
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
    }

    return success;
}
