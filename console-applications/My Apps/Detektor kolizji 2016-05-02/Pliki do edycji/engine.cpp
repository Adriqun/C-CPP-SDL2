#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

#include "engine.h"

/* Laduje wszystkie obiekty */
bool Engine::load()
{
    bool success = true;

    if( !intro.load( renderer, window ) )
    {
        printf( "Nie wczytano obiektu intro!\n" );
        success = false;
    }

    if( !menu.load( renderer, window ) )
    {
        printf( "Nie wczytano obiektu menu!\n" );
        success = false;
    }

    if( !desktop.load( renderer, window ) )
    {
        printf( "Nie wczytano obiektu desktop!\n" );
        success = false;
    }

    if( !hero.load( renderer, window ) )
    {
        printf( "Nie wczytano obiektu hero!\n" );
        success = false;
    }

    return success;
}

/* Przechwytuje wszystkie zdarzenia i przesyla poszczegolnym biektow w okreslonym stanie programu */
void Engine::events()
{
    if( SDL_PollEvent( &event ) != 0 )
    {
        if( frame == 1 )
        {
            menu.events( event );
        }

        else if( frame == 2 )
        {
            desktop.events( event );
        }
    }
}

/* W okreslonych stanach, renderowanie, dynamiczne zwalnianie pamieci oraz dynamiczne ladowanie */
void Engine::states()
{
    if( frame == 0 )
    {
        intro.render( renderer );
        if( intro.isClose() )
        {
            frame = 1;
        }
    }

    else if( frame == 1 )
    {
        menu.render( renderer );
        if( menu.isClose() == 1 )
        {
            menu.load( renderer, window ); // reload
            frame = 2;
        }
        else if( menu.isClose() == 2 )
        {
            quit = true;
        }
    }

    else if( frame == 2 )
    {
        desktop.render( renderer );

        hero.motion( desktop.getFigure() );
        hero.render( renderer );

        if( desktop.isClose() )
        {
            desktop.load( renderer, window ); // reload
            frame = 1;
        }

        if( desktop.reloadHero() )
        {
            hero.load( renderer, window ); // reload
        }
    }
}

/* Czyszczenie obiektow */
void Engine::free()
{
    intro.free();
    menu.free();
    desktop.free();
    hero.free();

    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
}



/* Inicjacja programu wraz z ladowanie obiektow */
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
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Ostrzezenie: Liniowe filtrowanie tekstur jest wylaczone!\n " );
        }

        width = 800;
        height = 600;
        Uint32 flags = SDL_WINDOW_SHOWN;

        window = SDL_CreateWindow( "CD2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags );
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
                SDL_SetRenderDrawColor( renderer, 11, 11, 11, 0xFF );

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

                else if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "Nie zainicjowano MIX Error %s\n", Mix_GetError() );
                    success = false;
                }

                else if( !load() )
                {
                    printf( "Nie wczytano wszystkich obiektow!\n" );
                    success = false;
                }
            }
        }
    }

    return success;
}

/* -----GLOWNA PETLA PROGRAMU----- */
void Engine::render()
{
    while( !quit )
    {
        SDL_RenderClear( renderer );

        events();

        states();

        SDL_RenderPresent( renderer );

        printf( "cos\n" );
    }

    close();
}
/* --------------------------------------------------------- */

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
    quit = false;

    window = NULL;
    renderer = NULL;
}

Engine::~Engine()
{
    renderer = NULL;
    window = NULL;
}
