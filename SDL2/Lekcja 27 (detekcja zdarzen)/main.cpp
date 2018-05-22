#include "champion.h"
#include "wall.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event e;

Champion champion;
Wall wall;

void init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Nie zainicjowano video! Error %s\n", SDL_GetError() );
    }
    else
    {
        window = SDL_CreateWindow( "2016-02-18", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

        if( window == NULL )
        {
            printf( "Nie utworzono okna! Error %s\n", SDL_GetError() );
        }
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

            if( renderer == NULL )
            {
                printf( "Nie utworzono renderera! Error %s\n", SDL_GetError() );
            }
            else
            {
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                if( !( IMG_Init( IMG_INIT_PNG ) &IMG_INIT_PNG ) )
                {
                    printf( "Nie zainicjowano IMG! Error %s\n", IMG_GetError() );
                }
            }
        }
    }

}

void loadMedia()
{
    champion.texture.loadTexture( renderer, "champion.png" );
    wall.texture.loadTexture( renderer, "crank.png" );
    wall.loadFile( "file.txt" );
}

SDL_Rect crank;


void render()
{
    crank.w = 400;
    crank.h = 50;
    crank.x = 0;
    crank.y = 550;

    for( ;; )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
                SDL_Quit();
        }

        //wall.render( renderer );
        //wall.move();

        champion.render( renderer );
        champion.move( crank );
        champion.handleEvent( e );

        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );
        SDL_RenderDrawRect( renderer, &crank );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

        SDL_RenderPresent( renderer );
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }
}

int main( int argc, char** argv )
{
    init();
    loadMedia();
    render();

    return 0;
}
