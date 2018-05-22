#include "intro.h"
#include <stdio.h>

Intro::Intro()
{
    nr = 0;
    counter = 0;

    music = NULL;

    font = NULL;

    texture = NULL;
    rect = NULL;
}

Intro::~Intro()
{
    free();
}


void Intro::free()
{
    for( Uint8 i = 0; i < nr; i++ )
    {
        SDL_DestroyTexture( texture[ i ] );
        texture[ i ] = NULL;
    }

    delete [] texture;
    texture = NULL;

    delete [] rect;
    rect = NULL;

    if( music != NULL )
    {
        Mix_FreeMusic( music );
        music = NULL;
    }

    counter = 0;
    nr = 0;
}

bool Intro::isClose()
{
    if( counter < 1 )
    {
        free();
        return true;
    }

    return false;
}


SDL_Texture* Intro::createWithColor( SDL_Renderer* &renderer, int &w, int &h, Uint8 red, Uint8 green, Uint8 blue )
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

SDL_Texture* Intro::loadFromRenderedText( SDL_Renderer* &renderer, std::string textureText, int &a, int &b )
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
        else
        {
            a = textSurface->w;
            b = textSurface->h;
        }

        SDL_FreeSurface( textSurface );
    }

    return newTexture;
}


bool Intro::load( SDL_Renderer* renderer, SDL_Window* window )
{
    bool success = true;

    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    font = TTF_OpenFont( "intro/0.otf", 40 );
    if( font == NULL )
    {
        printf( "Nie wczytano czcionki! Error: %s", TTF_GetError() );
        success = false;
    }
    else
    {
        counter = 360;
        nr = 3;
        texture = new SDL_Texture* [ nr ];
        rect = new SDL_Rect [ nr ];

        int a, b;

        texture[ 0 ] = createWithColor( renderer, w, h, 0x15, 0x15, 0x1D );
        rect[ 0 ].w = w;
        rect[ 0 ].h = h;
        rect[ 0 ].x = 0;
        rect[ 0 ].y = 0;

        color.r = 0xFF;
        color.g = 0xFF;
        color.b = 0xFF;
        texture[ 1 ] = loadFromRenderedText( renderer, "Adrian Michalek", a, b );
        rect[ 1 ].w = a;
        rect[ 1 ].h = b;
        rect[ 1 ].x = w / 2 - a / 2;
        rect[ 1 ].y = h / 2 - b / 2;

        color.r = 0x70;
        color.g = 0xB7;
        color.b = 0x59;
        texture[ 2 ] = loadFromRenderedText( renderer, "author:", a, b );
        rect[ 2 ].w = a;
        rect[ 2 ].h = b;
        rect[ 2 ].x = w / 2 - a / 2;
        rect[ 2 ].y = ( h / 2 ) - ( b / 2 ) - rect[ 1 ].h;

        for( Uint8 i = 0; i < nr; i++ )
        {
            if( texture[ i ] == NULL )
            {
                success = false;
            }
        }

        music = Mix_LoadMUS( "intro/0.mp3" );
        if( music == NULL )
        {
            printf( "Nie znaleziono intro/0.mp3!\n" );
            success = false;
        }
        else
        {
            Mix_FadeInMusic( music, 0, 2000 );
        }

    }

    return success;
}

void Intro::render( SDL_Renderer* renderer )
{
    counter --;

    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( music, -1 );
    }
    Mix_VolumeMusic( counter / 24 );

    for( Uint8 i = 0; i < nr; i ++ )
    {
        SDL_SetTextureAlphaMod( texture[ i ], counter / 1.5 );
        SDL_RenderCopy( renderer, texture[ i ], NULL, &rect[ i ] );
    }
}
