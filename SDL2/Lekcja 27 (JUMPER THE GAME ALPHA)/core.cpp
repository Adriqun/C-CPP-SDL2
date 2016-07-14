#include "core.h"

Core::Core()
{
    SCREEN_WIDTH = 800;
    SCREEN_HEIGHT = 600;

    window = NULL;
    renderer = NULL;
}

void Core::init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Nie zainicjowano SDL'a! Error %s\n", SDL_GetError() );
    }
    else
    {
        createWindow();
        createRenderer();

        if( !( IMG_Init( IMG_INIT_PNG ) &IMG_INIT_PNG ) )
        {
            printf( "Nie zainicjowano IMG! Error %s\n", IMG_GetError() );
        }
    }
}

void Core::close()
{
    delete &wall;
    delete &hero;

    SDL_DestroyWindow( window );
    window = NULL;

    SDL_DestroyRenderer( renderer );
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();
}

void Core::createWindow()
{
    window = SDL_CreateWindow( "2016-02-18", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    if( window == NULL )
    {
        printf( "Nie utworzono okna! Error %s\n", SDL_GetError() );
    }
}

void Core::createRenderer()
{
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    if( renderer == NULL )
    {
        printf( "Nie utworzono renderera! Error %s\n", SDL_GetError() );
    }
}

void Core::load()
{
    wall.load();
    wall.save();

    hero.load( renderer );
}

void Core::render()
{
    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT )
            SDL_Quit();
    }

    SDL_RenderPresent( renderer );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );
    SDL_RenderClear( renderer );
}

void Core::renderAll()
{
    for( ;; )
    {
        hero.setRect( detector.setRect( hero.getRect(), wall.getRect( hero.getRect() ), SCREEN_WIDTH, SCREEN_HEIGHT, hero.getVelX(), hero.getVelY() ) );
        hero.render( renderer );
        hero.motion( wall.getRect( hero.getRect() ) );

        wall.render( renderer );
        //wall.add( renderer, e );

        render();
    }
}
