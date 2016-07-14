#include "engine.h"
#include <stdio.h>
#include <windows.h>

bool Engine::load()
{
    bool success = true;

    if( !intro->load( window->getRenderer(), window->getWindow() ) )
    {
        printf( "Nie wczytano obiektu intro!\n" );
        success = false;
    }

    if( !clock->load( window->getRenderer() ) )
    {
        printf( "Nie wczytano obiektu clock!\n" );
        success = false;
    }


    if( success )
    {
        printf( "LOAD: " );
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 10 );
        printf( "pomyslnie wczytano wszystkie obiekty!\n" );
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
    }

    return success;
}

void Engine::render()
{
    if( frame == 0 )
    {
        intro->render( window->getRenderer() );
        if( intro->isClose() )
        {
            intro->free();
            delete intro;
            frame = 1;
        }
    }
    else if( frame == 1 )
    {
        clock->render( window->getRenderer(), window->getWindow() );
    }
}

void Engine::handle()
{
    while( SDL_PollEvent( &event ) != 0 )
    {
        if( event.type == SDL_QUIT )
        {
            quit = true;
        }

        window->handle( event );
    }
}

void Engine::free()
{
    delete window;
    delete clock;
}

/*
BLACK 0 -
BLUE 1 BLUE
GREEN 2 GREEN
CYAN 3 BLUE + GREEN
RED 4 RED
MAGENTA 5 BLUE + RED
BROWN 6 GREEN + RED
LIGHTGRAY 7 BLUE + GREEN + RED
DARKGRAY 8 INTENSITY
LIGHTBLUE 9 BLUE + INTENSITY
LIGHTGREEN 10 GREEN + INTENSITY
LIGHTCYAN 11 BLUE + GREEN + INTENSITY
LIGHTRED 12 RED + INTENSITY
LIGHTMAGENTA 13 BLUE + RED + INTENSITY
YELLOW 14 GREEN + RED + INTENSITY
WHITE 15 BLUE + GREEN + RED + INTENSITY
*/
