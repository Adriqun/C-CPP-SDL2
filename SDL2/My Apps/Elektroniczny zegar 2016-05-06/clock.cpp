#include "clock.h"
#include <stdio.h>
#include <time.h>

Clock::Clock()
{
    nr = 0;
    state = 0;

    font = NULL;
    texture = NULL;
}

Clock::~Clock()
{
    free();
}



void Clock::free()
{
    for( Uint8 i = 0; i < nr; i++ )
    {
        SDL_DestroyTexture( texture[ i ] );
        texture[ i ] = NULL;
    }

    delete [] texture;
    texture = NULL;

    nr = 0;
    state = 0;
}

std::string Clock::getTime()
{
    std::string newTime;

    time_t czas;
    struct tm* data;
    char moment[ 9 ];

    time( &czas );
    data = localtime( &czas );

    strftime( moment, 9, "%H:%M:%S", data );

    newTime = moment;

    return newTime;
}



SDL_Texture* Clock::createWithColor( SDL_Renderer* &renderer, int &w, int &h, Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* surface = SDL_CreateRGBSurface( 0, w, h, 32, 0, 0, 0, 0 );
    if( surface == NULL )
    {
        printf( "Nie utworzono pustej powierzchni!\n" );
    }
    else
    {
        SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, red, green, blue ) );
        newTexture = SDL_CreateTextureFromSurface( renderer, surface );

        if( newTexture == NULL )
        {
            printf( "Nie utworzono tekstury z powierzchni!\n" );
        }
    }

    SDL_FreeSurface( surface );
    surface = NULL;

    return newTexture;
}

SDL_Texture* Clock::loadFromRenderedText( SDL_Renderer* &renderer, std::string textureText )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* textSurface = TTF_RenderText_Blended( font, textureText.c_str(), color );
    if( textSurface == NULL )
    {
        printf( "Nie utworzono powierzchni z tekstu Error: %s\n", TTF_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( newTexture == NULL )
        {
            printf( "Nie utworzono tekstury z powierzchni tekstu! Error: %s\n", SDL_GetError() );
        }

        SDL_FreeSurface( textSurface );
    }

    return newTexture;
}

bool Clock::load( SDL_Renderer* renderer )
{
    bool success = true;

    width = 300;
    height = 75;

    font = TTF_OpenFont( "clock/0.ttf", 100 );
    if( font == NULL )
    {
        printf( "Nie wczytano czcionki! Error: %s", TTF_GetError() );
        success = false;
    }
    else
    {
        nr = 2;
        texture = new SDL_Texture* [ nr ];

        texture[ 0 ] = createWithColor( renderer, width, height, 0x00, 0x93, 0xD1 );

        color.r = 0xF2;
        color.g = 0x63;
        color.b = 0x5F;
        texture[ 1 ] = loadFromRenderedText( renderer, "00:00:00" );

        for( Uint8 i = 0; i < nr; i++ )
        {
            if( texture[ i ] == NULL )
            {
                success = false;
            }
        }
    }

    return success;
}

void Clock::render( SDL_Renderer* renderer, SDL_Window* window )
{
    if( state == 0 )
    {
        SDL_SetWindowSize( window, width, height );
        state = 1;
    }

    SDL_DestroyTexture( texture[ 1 ] );
    texture[ 1 ] = loadFromRenderedText( renderer, getTime());

    for( Uint8 i = 0; i < nr; i ++ )
    {
        SDL_RenderCopy( renderer, texture[ i ], NULL, NULL );
    }
}
