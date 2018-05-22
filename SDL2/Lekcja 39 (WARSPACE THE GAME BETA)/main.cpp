#include "hero.h"
#include "background.h"
#include <SDL_image.h>

int main( int argc, char **argv )
{
    SDL_Init( SDL_INIT_EVERYTHING );

    IMG_Init( IMG_INIT_PNG );

    SDL_Window* window = SDL_CreateWindow( "cos", 100, 200 , 800, 800, SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_Event e;

    Hero hero;
    hero.load( renderer );
    Background bg;
    bg.load( renderer );
    for( ;; )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
                SDL_Quit();
        }
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

        bg.render( renderer );
        hero.render( renderer );


        SDL_RenderPresent( renderer );
    }

    return 0;
}
