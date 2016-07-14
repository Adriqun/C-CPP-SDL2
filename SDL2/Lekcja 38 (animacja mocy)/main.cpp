#include "power.h"

int main( int argc, char ** argv )
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer= NULL;
    SDL_Event event;

    SDL_Init( SDL_INIT_EVERYTHING );
    window = SDL_CreateWindow( "Lekcja 38", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 256, SDL_WINDOW_SHOWN );
    renderer= SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    IMG_Init( IMG_INIT_PNG );

    Power blue( 25, "effects/blue.png" );
    Power green( 25, "effects/green.png" );
    Power red( 25, "effects/red.png" );
    Power orange( 26, "effects/orange.png" );
    Power violet( 25, "effects/violet.png" );
    Power blue2( 28, "effects/blue2.png" );
    Power green2( 29, "effects/green2.png" );
    Power red2( 28, "effects/red2.png" );
    Power orange2( 29, "effects/orange2.png" );
    Power violet2( 29, "effects/violet2.png" );

    blue.load( renderer );
    green.load( renderer );
    red.load( renderer );
    orange.load( renderer );
    violet.load( renderer );
    blue2.load( renderer );
    green2.load( renderer );
    red2.load( renderer );
    orange2.load( renderer );
    violet2.load( renderer );

    while( true )
    {
        while( SDL_PollEvent( &event ) != 0 )
        {
            if( event.type == SDL_QUIT )
                SDL_Quit();
        }
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

        blue.render( renderer, true, 0 );
        green.render( renderer, true, 128 );
        red.render( renderer, true, 256 );
        orange.render( renderer, true, 384 );
        violet.render( renderer, true, 512 );
        blue2.render( renderer, true, 0, 128 );
        green2.render( renderer, true, 128, 128 );
        red2.render( renderer, true, 256, 128 );
        orange2.render( renderer, true, 384, 128 );
        violet2.render( renderer, true, 512, 128 );

        SDL_RenderPresent( renderer );
    }

    blue.close();
    green.close();
    red.close();
    orange.close();
    violet.close();
    blue2.close();
    green2.close();
    red2.close();
    orange2.close();
    violet2.close();

    return 0;
}
