#include "dataStream.h"
#include <SDL_image.h>
#include <stdio.h>

DataStream::DataStream()
{
    images[ 0 ] = NULL;
    images[ 1 ] = NULL;
    images[ 2 ] = NULL;
    images[ 3 ] = NULL;

    currentImage = 0;
    mDelayFrames = 4;
}

bool DataStream::loadMedia()
{
    bool success = true;

    for( int i = 0; i < 4; ++i )
    {
        char path[ 64 ] = "";
        sprintf( path, "foo_walk_%d.png", i );

        SDL_Surface* loadedSurface = IMG_Load( path );
        if( loadedSurface == NULL )
        {
            printf( "Unable to load %s! SDL_image error: %s\n", path, IMG_GetError() );
            success = false;
        }
        else
        {
            images[ i ] = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL );
        }

        SDL_FreeSurface( loadedSurface );
    }

    return success;
}

void DataStream::free()
{
    for( int i = 0; i < 4; ++i )
    {
        SDL_FreeSurface( images[ i ] );
    }
}

void* DataStream::getBuffer()
{
    --mDelayFrames;
    if( mDelayFrames == 0 )
    {
        ++currentImage;
        mDelayFrames = 4;
    }

    if( currentImage == 4 )
    {
        currentImage = 0;
    }

    return images[ currentImage ]->pixels;
}
