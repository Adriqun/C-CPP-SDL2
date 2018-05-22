#include "background.h"
#include <SDL_image.h>

Background::Background()
{
    vel = 1;
    width = 0;
    height = 0;

    texture = NULL;
    arect = NULL;
    brect = NULL;
}

Background::~Background()
{
    free();
    delete &debugger;
}

void Background::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;

        delete [] arect;
        arect = NULL;

        delete [] brect;
        brect = NULL;

        vel = 1;
        width = 0;
        height = 0;
    }
}

SDL_Texture* Background::loadTexture( SDL_Renderer *&renderer, std::string path )
{
    free();

    SDL_Surface* surface = IMG_Load( path.c_str() );
    SDL_Texture* newTexture = NULL;

    if( surface == NULL )
    {
        debugger.loadingSurfaceError( path );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, surface );
        if( newTexture == NULL )
        {
            debugger.createTextureFromSurfaceError( path );
        }
        else
        {
            width = surface->w/2;
            height = surface->h;
        }
    }

    return newTexture;
}

void Background::load( SDL_Renderer *&renderer )
{
    texture = loadTexture( renderer, "background.png" );

    if( texture == NULL )
    {
        debugger.setTextureError();
    }
    else
    {
        arect = new SDL_Rect [ 2 ];
        arect[ 0 ].w = width;
        arect[ 0 ].h = height;
        arect[ 0 ].x = 0;
        arect[ 0 ].y = 0;
        arect[ 1 ] = arect[ 0 ];
        arect[ 1 ].x = width;

        brect = new SDL_Rect [ 2 ];
        brect[ 0 ].w = width;
        brect[ 0 ].h = height;
        brect[ 0 ].x = 0;
        brect[ 0 ].y = 0;
        brect[ 1 ] = brect[ 0 ];
        brect[ 1 ].y = height * -1;
    }
}

void Background::motion()
{
    brect[ 0 ].y += vel;

    if( brect[ 0 ].y  == height )
    {
        brect[ 0 ].y = height * -1;
    }

    brect[ 1 ].y += vel;

    if( brect[ 1 ].y  == height )
    {
        brect[ 1 ].y = height * -1;
    }
}

void Background::render( SDL_Renderer *&renderer )
{
    motion();

    SDL_RenderCopy( renderer, texture, &arect[ 0 ], &brect[ 0 ] );

    SDL_RenderCopy( renderer, texture, &arect[ 1 ], &brect[ 1 ] );
}
