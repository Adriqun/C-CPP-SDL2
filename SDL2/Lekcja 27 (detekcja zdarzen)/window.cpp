#include "window.h"

Window::Window()
{
    SCREEN_WIDTH = 0;
    SCREEN_HEIGHT = 0;

    window = NULL;
    renderer = NULL;
}

Window::~Window()
{
    free();
}

void Window::createWindow( std::string title, int w, int h )
{
    SCREEN_WIDTH = w;
    SCREEN_HEIGHT = h;

    window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN );

    if( window == NULL )
    {
        printf( "Nie utworzono okna! Error %s\n", SDL_GetError() );
    }
}

void Window::createRenderer()
{
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    if( renderer == NULL )
    {
        printf( "Nie utworzono renderera! Error %s\n", SDL_GetError() );
    }
    else
    {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }
}

void Window::render()
{
    SDL_RenderClear( renderer );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderPresent( renderer );

    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT )
            SDL_Quit();
    }
}

void Window::free()
{
    if( renderer != NULL )
    {
        SDL_DestroyRenderer( renderer );
        renderer = NULL;
    }

    if( window != NULL )
    {
        SDL_DestroyWindow( window );
        window = NULL;

        SCREEN_WIDTH = 0;
        SCREEN_HEIGHT = 0;
    }
}
