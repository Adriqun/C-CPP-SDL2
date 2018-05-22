#include <SDL2/SDL.h>
#include <time.h>
#include <cstdlib>

int getRand( int MAX )
{
    return rand() % MAX;
}

int main( int argc, char** argv )
{
    srand( time( NULL ) );

    if( SDL_Init( SDL_INIT_EVERYTHING ) >= 0 )
    {
        SDL_Window* window = SDL_CreateWindow( "", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
        , 500, 500, SDL_WINDOW_SHOWN );

        SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        SDL_Event event;
        bool quit = false;

        const int MAX = 255;

        int randA = getRand( 255 );
        int randB = getRand( 255 );
        int randC = getRand( 255 );
        int randD = getRand( 255 );

        int a = 0;
        int b = 0;
        int c = 0;
        int d = 0;

        while( !quit )
        {
            while( SDL_PollEvent( &event) != 0 )
            {
                if( event.type == SDL_QUIT )
                {
                    quit = true;
                }
            }

            SDL_RenderClear( renderer );
            SDL_SetRenderDrawColor( renderer, a, b, c, d );

            SDL_RenderPresent( renderer );

            if( a < randA )         a++;
            else if( a > randA )    a--;
            else    randA = getRand( MAX );

            if( b < randB )         b++;
            else if( b > randB )    b--;
            else    randB = getRand( MAX );

            if( c < randC )         c++;
            else if( c > randC )    c--;
            else    randC = getRand( MAX );

            if( d < randD )         d++;
            else if( d > randD )    d--;
            else    randD = getRand( MAX );
        }
    }

    return 0;
}
