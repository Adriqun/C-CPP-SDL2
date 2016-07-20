#include "image.h"
#include <SDL_image.h>
#include <stdio.h>

Image::Image()
{
    texture = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;

    alpha = SDL_ALPHA_TRANSPARENT;
}

Image::~Image()
{
    free();
}

void Image::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;

        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = 0;

        alpha = SDL_ALPHA_TRANSPARENT;
    }
}


bool Image::load( SDL_Renderer* &renderer, SDL_Window* &window, string path, int x, int y )
{
    free();

    SDL_Surface* surface = IMG_Load( path.c_str() );
    if( surface == NULL )
    {
        printf( "Not found image %s\n", path.c_str() );
        printf( "Error %s\n", IMG_GetError() );
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        if( texture == NULL )
        {
            printf( "Not converted surface \n" );
            printf( "Error %s\n", SDL_GetError() );
        }
        else
        {
            rect.w = surface->w;
            rect.h = surface->h;
            rect.x = x;
            rect.y = y;
        }

        SDL_FreeSurface( surface );
        surface = NULL;
    }

    return texture != NULL;
}

void Image::render( SDL_Renderer* &renderer, int* x, int* y, SDL_Rect* srcRect, double angle, SDL_Point* point, SDL_RendererFlip flip )
{
    if( x != NULL )
    {
        rect.x = *x;
    }

    if( y != NULL )
    {
        rect.y = *y;
    }

    if( srcRect != NULL )
    {
        rect.w = srcRect->w;
        rect.h = srcRect->h;
    }

    SDL_RenderCopyEx( renderer, texture, srcRect, &rect, angle, point, flip );
}


void Image::fadeIO( int value )
{
    if( value > 0 )
    {
        if( alpha + value < SDL_ALPHA_OPAQUE )
        {
            alpha += value;
        }

        setAlpha( alpha );
    }
    else
    {
        if( alpha - value > SDL_ALPHA_TRANSPARENT )
        {
            alpha += value;
        }

        setAlpha( alpha );
    }
}


void Image::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( texture, alpha );
}

void Image::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( texture, red, green, blue );
}

void Image::setBlendMode( SDL_BlendMode blendMode )
{
    SDL_SetTextureBlendMode( texture, blendMode );
}


int Image::getWidth()
{
    return rect.w;
}

int Image::getHeight()
{
    return rect.h;
}

void Image::setWidth( int w )
{
    rect.w = w;
}

void Image::setHeight( int h )
{
    rect.h = h;
}


int Image::getX()
{
    return rect.x;
}

int Image::getY()
{
    return rect.y;
}

void Image::setX( int x )
{
    rect.x = x;
}

void Image::setY( int y )
{
    rect.y = y;
}

