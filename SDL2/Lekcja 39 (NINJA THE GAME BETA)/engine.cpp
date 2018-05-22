#include "engine.h"
#include "timer.h"
#include "debugger.h"
#include "engine_intro.h"

Engine::Engine()
{
    frame = -1;
    renderer = NULL;
    window = NULL;
}

void Engine::renderObjects()
{
    if( frame == -2 )
    {
        chart.controlEditMode( event );
        chart.renderEditMode( renderer );
    }
    else if( frame == -1 )
    {
        Intro intro;
        intro.render( renderer );
        delete &intro;

        menu.load( renderer );
        frame = 0;
    }
    else if( frame == 0 )
    {
        menu.render( renderer );

        if( menu.getFrame() == 1 )
        {
            menu.load( renderer );
            wall.load( renderer );
            hero.load( renderer );
            frame = 1;
        }
    }
    else if( frame == 1 )
    {
        hero.motionX();
        hero.setX( chart.checkCollision( hero.getRect() ) );
        hero.motionY();
        hero.setY( chart.checkCollision( hero.getRect() ) );

        wall.render( renderer, hero.getDimension() );
        hero.render( renderer );
        chart.render( renderer, hero.getPoint() );
    }
    else if( frame == 2 )
    {

    }
}

void Engine::closeObjects()
{
    delete &menu;
    delete &chart;
    delete &wall;
    delete &hero;
}

void Engine::startProgram()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        deb::SDL_InitError();

    if( !( IMG_Init( IMG_INIT_PNG ) &IMG_INIT_PNG ) )
        deb::IMG_InitError();

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        deb::MIX_InitError();

    if( TTF_Init() < 0 )
        deb::TTF_InitError();

    window = SDL_CreateWindow( "NINJA 1.2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN );
    if( window == NULL )
        deb::createWindowError();

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if( renderer == NULL )
        deb::createRendererError();

    //if( frame == -2 ) // gdy uzywamy trybu budowania mapy
        //chart.load( renderer );
}

void Engine::renderProgram()
{
    Timer timer;
    for( ;; )
    {
        timer.start();

        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );

        while( SDL_PollEvent( &event ) != 0 )
        {
           if( event.type == SDL_QUIT )
           {
                closeProgram();
           }
        }

        renderObjects();

        SDL_RenderPresent( renderer );
        timer.setFPS();
    }
    delete &timer;
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
