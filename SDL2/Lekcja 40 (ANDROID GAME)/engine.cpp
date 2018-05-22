#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <time.h>

#include "engine.h"
#include "intro.h"
#include "timer.h"

Engine::Engine()
{
    frame = -1;
    screen.x = 0;
    screen.y = 0;
    screen.w = 540;
    screen.h = 960;

    renderer = NULL;
    window = NULL;
}

void Engine::loadObjects()
{
    srand( time( NULL ) );
    menu = new Menu;
    background = new Background;
    hero = new Hero;
    enemy = new Enemy;
}

void Engine::renderObjects()
{
    if( frame == -1 )
    {
        Intro* intro = new Intro;
        intro->load( renderer, screen.w, screen.h );
        intro->render( renderer, event );
        delete intro;

        menu->load( renderer, screen.w, screen.h );
        background->load( renderer, screen.w, screen.h );

        frame = 0;
    }
    else if( frame == 0 )
    {
        background->render( renderer );
        menu->render( renderer );
        if( menu->getFrame() == 1 )
        {
            hero->load( renderer, screen.w, screen.h );
            enemy->load( renderer, screen.w );
            frame = 1;
        }
    }
    else if( frame == 1 )
    {
        background->render( renderer );
        hero->render( renderer );
        enemy->render( renderer );
        enemy->motion( screen.w, screen.h );
    }
}

void Engine::closeObjects()
{
    delete menu;
    delete background;
    delete hero;
    delete enemy;
}

void Engine::startProgram()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        SDL_Log( "Nie zainicjowano SDL! Error %s", SDL_GetError() );
    }

    if( !( IMG_Init( IMG_INIT_PNG ) &IMG_INIT_PNG ) )
    {
        SDL_Log( "Nie zainicjowano IMG! Error %s", IMG_GetError() );
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        SDL_Log( "Nie zainicjowano Mix! Error %s", Mix_GetError() );
    }

    if( TTF_Init() < 0 )
    {
        SDL_Log( "Nie zainicjowano TTF! Error %s", TTF_GetError() );
    }

    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        SDL_Log( "Ostrzezenie: Liniowe filtrowanie tekstur jest wylaczone!" );
    }

    SDL_DisplayMode displayMode;
    if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
    {
        screen.w = displayMode.w;
        screen.h = displayMode.h;
        screen.w = 540;
        screen.h = 960;
    }

    window = SDL_CreateWindow( "Defense", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen.w, screen.h, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        SDL_Log( "Nie utworzono okna! Error %s", SDL_GetError() );
    }

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if( renderer == NULL )
    {
        SDL_Log( "Nie utworzono renderera! Error %s", SDL_GetError() );
    }
    else
    {
        SDL_SetRenderDrawColor( renderer, 11, 11, 11, 0xFF );
        SDL_RenderPresent( renderer );
    }

    loadObjects();
}

void Engine::renderProgram()
{
    Timer* timer = new Timer;
    while( frame != 3 )
    {
        timer->start();

        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );

        while( SDL_PollEvent( &event ) != 0 )
        {
            if( event.type == SDL_QUIT )
            {
                frame = 3;
            }
            if( frame == 0 )
            {
                menu->event( renderer, event, screen.w, screen.h );
            }
            if( frame == 1 )
            {
                hero->event( event, screen.w, screen.h );
                enemy->event( event );
            }
        }

        renderObjects();

        SDL_RenderPresent( renderer );
        timer->setFPS();
    }

    delete timer;
    closeProgram();
}

void Engine::closeProgram()
{
    SDL_DestroyRenderer( renderer );
    renderer = NULL;

    SDL_DestroyWindow( window );
    window = NULL;

    closeObjects();

    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
