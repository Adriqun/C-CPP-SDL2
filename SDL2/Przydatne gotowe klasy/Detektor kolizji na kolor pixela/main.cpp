#include "pixel_detector.h"
#include <iostream>
int main( int argc, char** argv )
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init( SDL_INIT_EVERYTHING );
    window = SDL_CreateWindow( "detektor kolizji", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    PixelDetector pd;
    pd.load( renderer, "pixel_detector/", 1 );
    std::cout<< pd.getSeries();

    return 0;
}
