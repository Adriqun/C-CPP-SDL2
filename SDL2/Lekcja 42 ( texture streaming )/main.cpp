#include <SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include "dataStream.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

Texture texture;
DataStream dataStream;

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

        srand( SDL_GetTicks() );

        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

                if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
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

    if( !texture.createBlank( renderer, 64, 205 ) )
    {
        printf( "Failed to create streaming texture!\n" );
        success = false;
    }

    if( !dataStream.loadMedia() )
    {
        printf( "Unable to load data stream!\n" );
        success = false;
    }

    return success;
}

void close()
{
    texture.free();
    dataStream.free();

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
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            bool quit = false;
            SDL_Event e;

            while( !quit )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }

                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( renderer );

                //Copy frame from buffer
                texture.lockTexture();
                texture.copyPixels( dataStream.getBuffer() );
                texture.unlockTexture();

                texture.render( renderer, ( SCREEN_WIDTH - texture.getWidth() ) / 2, ( SCREEN_HEIGHT - texture.getHeight() ) / 2 );

                SDL_RenderPresent( renderer );
            }
        }
    }

    close();

    return 0;
}
