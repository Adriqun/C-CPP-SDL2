#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Rect
{
public:
    uint16_t w, h;
    float x, y;
};

int main( int argc, char **arg )
{
    SDL_Init( SDL_INIT_EVERYTHING );
    IMG_Init( IMG_INIT_PNG );

    SDL_Window* window = SDL_CreateWindow( "Lekcja 26", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_Event e;

    SDL_Surface* surface = IMG_Load( "1.png" );
    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
    const Uint8* key = SDL_GetKeyboardState( NULL );

    Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 50;
    rect.h = 50;

    float posX = 0, posY = 0;
    float vel = 1;

    for(;;)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
                SDL_Quit();
        }
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

        if( key[ SDL_SCANCODE_UP ] && rect.y > 0 )
        {
            posY -= vel;

        }
        if( key[ SDL_SCANCODE_DOWN ] && rect.y + rect.h < 700 )
        {
            posY += vel;
        }
        if( key[ SDL_SCANCODE_LEFT ] && rect.x > 0 )
        {
            posX -= vel;
        }
        if( key[ SDL_SCANCODE_RIGHT ] && rect.x + rect.w < 700 )
        {
            posX += vel;
        }

        rect.y += posY;
        rect.x += posX;

        SDL_RenderCopy( renderer, texture, NULL, &rect );

        SDL_RenderPresent( renderer );
    }

    return 0;
}
