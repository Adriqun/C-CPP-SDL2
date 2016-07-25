#include "core.h"
#include <stdio.h>

Core::Core( int width, int height, int FPS )
{
    this->width = width;
    this->height = height;

    quit = false;

    frame = -1;
    this->FPS = FPS;
}

Core::~Core()
{
    // nothing to destroy
}


bool Core::createWindow( SDL_Window* &window, Uint32 flags, const char* path )
{
    bool success = true;

    int x = SDL_WINDOWPOS_UNDEFINED;
    int y = SDL_WINDOWPOS_UNDEFINED;

    window = SDL_CreateWindow( path, x, y, width, height, flags );
    if( window == NULL )
    {
        printf( "Not created window\n" );
        printf( "Error %s\n", SDL_GetError() );
        success = false;
    }

    return success;
}

bool Core::setWindowIcon( SDL_Window* &window, const char* icon )
{
    bool success = true;

    if( window != NULL )
    {
        SDL_Surface* surface = SDL_LoadBMP( icon );
        if( surface == NULL )
        {
            printf( "Not found icon window %s\n", icon );
            printf( "Error %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0 ) );
            SDL_SetWindowIcon( window, surface );
        }

        SDL_FreeSurface( surface );
        surface = NULL;
    }

    else
    {
        printf( "Not allowed setting icon, you need to create window before\n" );
        success = false;
    }

    return success;
}

bool Core::createRenderer( SDL_Window* &window, SDL_Renderer* &renderer, Uint32 flags, int index )
{
    bool success = true;

    if( window != NULL )
    {
        renderer = SDL_CreateRenderer( window, index, flags );
        if( renderer == NULL )
        {
            printf( "Not created renderer\n" );
            printf( "Error %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        }
    }

    else
    {
        printf( "Not allowed setting renderer, you need to create window before\n" );
        success = false;
    }

    return success;
}



void Core::topRender( SDL_Renderer* &renderer )
{
    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( renderer );
}

void Core::botRender( SDL_Renderer* &renderer )
{
    SDL_RenderPresent( renderer );
}



int Core::getWidth()
{
    return width;
}

int Core::getHeight()
{
    return height;
}



bool Core::getQuit()
{
    return quit;
}

void Core::setQuit()
{
    quit = true;
}



int Core::getFrame()
{
    return frame;
}

void Core::setFrame( int frame )
{
    this->frame = frame;
}



int Core::getFPS()
{
    return FPS;
}

void Core::setFPS( int FPS )
{
    this->FPS = FPS;
}
