#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

#include "engine.h"

bool Engine::load()
{
    bool success = true;

    return success;
}

bool Engine::init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Nie zainicjowano SDL Error %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        width = 800;
        height = 600;
        int x = SDL_WINDOWPOS_CENTERED;
        int y = SDL_WINDOWPOS_CENTERED;
        Uint32 flags = SDL_WINDOW_SHOWN;

        window = SDL_CreateWindow( "Engine", x, y, width, height, flags );
        if( window == NULL )
        {
            printf( "Nie utworzono okna! Error %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            int index = -1;
            Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

            renderer = SDL_CreateRenderer( window, index, flags );
            if( renderer == NULL )
            {
                printf( "Nie utworzono renderera! Error %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            }

            if( !load() )
            {
                printf( "Nie wczytano obiektow!\n" );
                success = false;
            }
        }
    }

    if( !( IMG_Init( IMG_INIT_PNG )&IMG_INIT_PNG ) )
    {
        printf( "Nie zainicjowano IMG Error %s\n", IMG_GetError() );
        success = false;
    }

    if( TTF_Init() < 0 )
    {
        printf( "Nie zainicjowano TTF Error %s\n", TTF_GetError() );
        success = false;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "Nie zainicjowano MIX Error %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void Engine::events()
{
    if( SDL_PollEvent( &event ) != 0 )
    {
        if( event.type == SDL_QUIT )
        {
            close();
        }
    }
}

void Engine::states()
{

}

void Engine::free()
{

}

void Engine::render()
{
    for( ;; )
    {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        events();

        states();

        SDL_RenderPresent( renderer );
    }
}

void Engine::close()
{
    free();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

Engine::Engine()
{
    frame = 0;
    width = 0;
    height = 0;
    window = NULL;
    renderer = NULL;
}

Engine::~Engine()
{
    // void
}
