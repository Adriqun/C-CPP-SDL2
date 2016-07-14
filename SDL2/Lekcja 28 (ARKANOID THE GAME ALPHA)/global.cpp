#include "global.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
const Uint16 SCREEN_WIDTH = 800;
const Uint16 SCREEN_HEIGHT = 600;
int FRAME = 0;

bool init()
{

    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "Nie zainicjowano biblioteki! Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        window = SDL_CreateWindow( "Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );

        if( window == NULL )
        {
            printf( "Nie utworzono okna! Error: %s\n", SDL_GetError() );
            success =false;
        }
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

            if( renderer == NULL )
            {
                printf( "Nie utworzono rendera! Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );

                int flag = IMG_INIT_PNG;

                if( !( IMG_Init( flag ) &flag ) )
                {
                    printf( "Nie zainicjowano biblioteki IMG! Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

SDL_Texture* loadTexture( string path, SDL_Rect &rect )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* surface = IMG_Load( path.c_str() );

    if( surface == NULL )
    {
        printf( "Nie zaladowano %s Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, surface );

        if( newTexture == NULL )
        {
            printf( "Nie utworzono textury z %s Error: %s", path.c_str(), IMG_GetError() );
        }
        else
        {
            rect.w = surface -> w;
            rect.h = surface -> h;
        }

        SDL_FreeSurface( surface );
    }

    return newTexture;
}

void shut()
{
    IMG_Quit();
    SDL_Quit();
}
