#include "dot.h"
#include "wall.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

Dot dot;
Wall wall;

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        window = SDL_CreateWindow( "Lekcja 27", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;

    if( !dot.dotTexture.loadFromFile( renderer, "dot.bmp" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }

    wall.texture.loadFromFile( renderer, "crank.png" );
    wall.loadFile( "file.txt" );
    return success;
}

void close()
{
    dot.dotTexture.free();

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    if( !init() )
        printf( "Failed to initialize!\n" );
    else
    {
        if( !loadMedia() )
            printf( "Failed to load media!\n" );
        else
        {
            SDL_Event e;


            while( true )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                        SDL_Quit();
                }
                wall.render( renderer );
                //wall.move();
                dot.handleEvent();
                dot.move( wall.getRect(), SCREEN_WIDTH, SCREEN_HEIGHT );

                dot.render( renderer );


                SDL_RenderPresent( renderer );
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( renderer );
            }
        }
    }

    close();
    return 0;
}
