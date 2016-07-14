#include "pixel_detector.h"
#include <stdio.h>
#include <string.h>
#include <SDL_image.h>

std::string PixelDetector::intToString( int path )
{
    std::string tmp;
    if( path < 0 )
    {
        tmp = "-";
        path = -path;
    }
    if( path > 9 )
        tmp += intToString( path / 10 );

    tmp += path % 10 + 48;
    return tmp;
}

int PixelDetector::stringToInt( std::string path )
{
    int tmp = 0;
    for( int i = 0; i < path.size(); i ++ )
    {
        if( path[ i ] == '-' )
            i ++;
        tmp = 10 * tmp + path[ i ] -48;
    }
    return path[ 0 ] == '-' ? -tmp : tmp;
}

void PixelDetector::addToFile( SDL_Texture* &t, SDL_Surface* &s )
{
    void* pixels = NULL;
    int pitch;
    int posX = 0, posY = 0;

    SDL_SetTextureBlendMode( t, SDL_BLENDMODE_BLEND );
    SDL_LockTexture( t, &s->clip_rect, &pixels, &pitch );
    memcpy( pixels, s->pixels, s->pitch * s->h );

    Uint32* newPixels = static_cast< Uint32* > ( pixels );
    int pixelCount = ( pitch / 4 ) * s->h;

    Uint32 red = SDL_MapRGB( s->format, 0xFF, 0, 0 );
    Uint32 green = SDL_MapRGB( s->format, 0, 0xFF, 0 );
    Uint32 black = SDL_MapRGB( s->format, 0, 0, 0 );


    for( int i = 0; i < pixelCount; ++i )
    {
        if( newPixels[ i ] == red )
        {
            posX += s->w;
        }
        else if( newPixels[ i ] == green )
        {
            posY += s->h;
        }
    }
    // X Y W H
    for( int i = 0; i < pixelCount; ++i )
    {
        if( newPixels[ i ] == black )
        {
            series += intToString( i % ( pitch / 4 ) ) + ".";
            series += intToString( i / ( pitch / 4 ) ) + ".";
            series += "1.1.\n";
        }
    }

    SDL_UnlockTexture( t );
    pixels = NULL;
}

bool PixelDetector::loadTexture( SDL_Renderer* &renderer, std::string path )
{
    SDL_Texture* texture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Nie wczytano obrazu %s, Error %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL );
        if( formattedSurface == NULL )
        {
            printf( "Nie skonwertowano powierzchni Error %s\n", SDL_GetError() );
        }
        else
        {
            texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
            if( texture == NULL )
            {
                printf( "Nie utworzono czystej tekstury Error %s\n", SDL_GetError() );
            }
            else
            {
                addToFile( texture, formattedSurface );
            }

            SDL_FreeSurface( formattedSurface );
            formattedSurface = NULL;
        }

        SDL_FreeSurface( loadedSurface );
        loadedSurface = NULL;
    }

    return texture != NULL;
}

void PixelDetector::load( SDL_Renderer* &renderer, std::string path, int range )
{
    std::string name = "pixel_detector.txt";
    // czyszczenie pliku
    file.open( name.c_str(), std::ios::in | std::ios::trunc );
    file.close();
    file.open( name.c_str(), std::ios::out | std::ios::app );
    if( !file.good() )
    {
        printf( "Nie mozna otworzyc pliku %s!\n", name.c_str() );
    }
    else
    {
        series = "";
        for( int i = 0; i < range; i++ )
        {
            loadTexture( renderer, path + intToString( i ) + ".png" );
        }
    }

    file.close();
}

std::string PixelDetector::getSeries()
{
    return series;
}
