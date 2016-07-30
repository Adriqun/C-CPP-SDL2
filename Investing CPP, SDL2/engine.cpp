#include "engine.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

bool Engine::load()
{
    bool success = true;

    if( !title.load( renderer, window ) )
    {
        success = false;
    }
    else if( !title_bar.createWithColor( renderer, 0x65, 0x99, 0xFF, width, title.getHeight() ) )
    {
        success = false;
    }

    if( !goal.load( renderer ) )
    {
        success = false;
    }

    if( !currency.load( renderer, window ) )
    {
        success = false;
    }

    if( !attain.load( renderer ) )
    {
        success = false;
    }

    return success;
}

void Engine::loop()
{
    SDL_StartTextInput();

    while( !quit )
    {
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

        while( SDL_PollEvent( &event ) != 0 )
        {
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }

            title.handle( event );
            goal.handle( event );
            currency.handle( event );
        }

        title_bar.render( renderer );
        title.render( renderer );

        goal.render( renderer );

        currency.render( renderer );

        attain.render( renderer );

        SDL_RenderPresent( renderer );
    }

    SDL_StopTextInput();
}

void Engine::free()
{
    quit = false;
    width = 0;
    height = 0;

    if( window != NULL )
    {
        SDL_DestroyWindow( window );
        window = NULL;

        SDL_DestroyRenderer( renderer );
        renderer = NULL;
    }

    title_bar.free();
    title.free();

    goal.free();

    currency.free();

    attain.free();

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

Engine::Engine()
{
    quit = false;
    width = 800;
    height = 600;
    window = NULL;
    renderer = NULL;
}

Engine::~Engine()
{
    free();
}

bool Engine::init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL could not initialize! Error %s\n", SDL_GetError() );
        success = false;
    }

    else if( !( IMG_Init( IMG_INIT_PNG )&IMG_INIT_PNG ) )
    {
        printf( "IMG could not initialize! Error %s\n", IMG_GetError() );
        success = false;
    }

    else if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "Mix could not initialize! Error: %s\n", Mix_GetError() );
        success = false;
    }

    else if( TTF_Init() < 0 )
    {
        printf( "TTF could not initialize! Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        window = SDL_CreateWindow( "Investing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Not created window! Error %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( renderer == NULL )
            {
                printf( "Not created renderer! Error %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                load();
            }
        }
    }

    return success;
}
