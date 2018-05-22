#include "engine.h"
#include "timer.h"
#include <stdio.h>

Engine::Engine()
{
    frame = 0;
    quit = false;

    core = new Core;
    window = new Window;
    intro = new Intro;
    clock = new Clock;
}

bool Engine::init()
{
    bool success = true;

    if( !core->initSDL() )
    {
        success = false;
    }
    else
    {
        if( !window->createWindow( "window/icon.bmp", "Clock", SDL_WINDOW_SHOWN ) )
        {
            success = false;
        }
        else if( !window->createRenderer( -1, SDL_RENDERER_ACCELERATED ) )
        {
            success = false;
        }

        if( !core->initIMG() )
        {
            success = false;
        }
        else if( !core->initMIX() )
        {
            success = false;
        }
        else if( !core->initTTF() )
        {
            success = false;
        }
        else if( !load() )
        {
            printf( "Nie wczytano wszystkich obiektow! \n" );
            success = false;
        }
        else
        {
            delete core;
            core = NULL;
        }
    }

    return success;
}

void Engine::loop()
{
    Timer timer( 60 );

    while( !quit )
    {
        timer.start();
        window->start();
        //SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
        //SDL_RenderClear( renderer );

        handle();
        render();

        //SDL_RenderPresent( renderer );
        window->present();
        timer.present();
    }
}

void Engine::close()
{
    free();

    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}
