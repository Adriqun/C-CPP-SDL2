#include "enemy.h"

int main( int argc, char **argv )
{
    SDL_Init( SDL_INIT_EVERYTHING );
    IMG_Init( IMG_INIT_PNG );

    SDL_Window* window = SDL_CreateWindow( "Lekcja 38", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

    SDL_Event e;

    Enemy enemy_one;
    Enemy enemy_two;
    Enemy enemy_three;

    enemy_one.load( renderer );
    enemy_two.load( renderer );
    enemy_three.load( renderer );

    enemy_one.setColor( 50, 80, 90 );
    enemy_two.setColor( 200, 0, 200 );
    enemy_three.setColor( 0, 250, 113 );

    for(;;)
    {
        while(SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_QUIT )
                SDL_Quit();

        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

        enemy_one.render( renderer );
        enemy_two.render( renderer );
        enemy_three.render( renderer );

        SDL_Delay( 5 );

        SDL_RenderPresent( renderer );
    }
    return 0;
}
