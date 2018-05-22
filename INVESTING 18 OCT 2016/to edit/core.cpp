#include "core.h"
#include <stdio.h>

Core::Core()
{
    quit = false;
    width = 800;
    height = 600;
	
    window = NULL;
    renderer = NULL;
}

void Core::init()
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL could not initialize! Error %s\n", SDL_GetError() );
    }

    else if( !( IMG_Init( IMG_INIT_PNG )&IMG_INIT_PNG ) )
    {
        printf( "IMG could not initialize! Error %s\n", IMG_GetError() );
    }

    else if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "Mix could not initialize! Error: %s\n", Mix_GetError() );
    }

    else if( TTF_Init() < 0 )
    {
        printf( "TTF could not initialize! Error: %s\n", TTF_GetError() );
    }
    else
    {
        window = SDL_CreateWindow( "Investing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Not created window! Error %s\n", SDL_GetError() );
        }
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( renderer == NULL )
            {
                printf( "Not created renderer! Error %s\n", SDL_GetError() );
            }
        }
    }
}

void Core::top_render()
{
	SDL_RenderClear( renderer );
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

void Core::bot_render()
{
	SDL_RenderPresent( renderer );
}

void Core::free()
{
	SDL_DestroyWindow( window );
	window = NULL;

	SDL_DestroyRenderer( renderer );
	renderer = NULL;
	
	Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}




bool &Core::isQuit()
{
	return quit;
}

int Core::getWidth()
{
	return width;
}

int Core::getHeight()
{
	return height;
}

SDL_Event &Core::getEvent()
{
	return event;
}

SDL_Window* &Core::getWindow()
{
	return window;
}

SDL_Renderer* &Core::getRenderer()
{
	return renderer;
}
