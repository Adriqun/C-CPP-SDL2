#include "intro.h"
#include <SDL_image.h>

Intro::Intro()
{
    rect = new SDL_Rect;
    rect->x = 0;
    rect->y = 0;
    rect->w = 0;
    rect->h = 0;

    counter = 0;
    fps = 1000 / 60;
    startTicks = 0;
    texture = NULL;
}

Intro::~Intro()
{
    SDL_DestroyTexture( texture );
    texture = NULL;

    delete rect;
    rect = NULL;
}

SDL_Texture* Intro::loadTexture( SDL_Renderer* &renderer, std::string path )
{
    SDL_Surface* surface = IMG_Load( path.c_str() );
    if( surface == NULL )
    {
        SDL_Log( "Nie wczytano %s Error %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_FreeSurface( surface );
        if( texture == NULL )
        {
            SDL_Log( "Nie utworzono tekstury z %s Error %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            return texture;
        }
    }
    return NULL;
}

void Intro::load( SDL_Renderer* &renderer, Uint16 w, Uint16 h )
{
    texture = loadTexture( renderer, "intro/0.png" );

    rect->w = w;
    rect->h = h;
}

void Intro::render( SDL_Renderer* &renderer, SDL_Event &event )
{
    for( ;; )
    {
        // pobieranie chwili
        startTicks = SDL_GetTicks();

        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );

        while( SDL_PollEvent( &event ) != 0 )
        {

        }

        if( counter == 100 )
        {
            SDL_DestroyTexture( texture );
            texture = NULL;
            texture = loadTexture( renderer, "intro/1.png" );
        }

        SDL_RenderCopy( renderer, texture, NULL, rect );

        SDL_RenderPresent( renderer );

        if( counter > 200 )
            break;
        counter ++;

        // ustawianie opoznienia jesli konieczne
        Uint32 time = SDL_GetTicks() - startTicks;
        if( time < fps )
            SDL_Delay( fps - time );
    }
}
