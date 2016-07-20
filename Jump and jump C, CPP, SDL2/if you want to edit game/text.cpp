#include "text.h"
#include <stdio.h>

Text::Text()
{
    font = NULL;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;

    texture = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;

    alpha = SDL_ALPHA_TRANSPARENT;
}

Text::~Text()
{
    free();
}

void Text::freeFont()
{
    if( font != NULL );
    {
        TTF_CloseFont( font );
        font = NULL;

        color.r = 0xFF;
        color.g = 0xFF;
        color.b = 0xFF;
    }
}

void Text::freeTexture()
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

void Text::free()
{
    freeFont();
    freeTexture();
}


bool Text::loadFont( string path, int scale, Uint8 red, Uint8 green, Uint8 blue )
{
    bool success = true;

    freeFont();

    font = TTF_OpenFont( path.c_str(), scale );
    if( font == NULL )
    {
        printf( "Not found font %s\n", path.c_str() );
        printf( "Error %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        color.r = red;
        color.g = green;
        color.b = blue;
    }

    return success;
}

bool Text::createTexture( SDL_Renderer* &renderer, string text )
{
    freeTexture();

    SDL_Surface* surface = TTF_RenderText_Blended( font, text.c_str(), color );
    if( surface == NULL )
    {
        printf( "Not created surface from text\n" );
        printf( "Error %s\n", TTF_GetError() );
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        if( texture == NULL )
        {
            printf( "Not created texture from surface text\n" );
            printf( "Error %s\n", SDL_GetError() );
        }
        else
        {
            rect.w = surface->w;
            rect.h = surface->h;
        }

        SDL_FreeSurface( surface );
        surface = NULL;
    }

    return texture != NULL;
}

void Text::render( SDL_Renderer* &renderer, int* x, int* y, double angle, SDL_Point* point, SDL_RendererFlip flip )
{
    if( x != NULL )
    {
        rect.x = *x;
    }

    if( y != NULL )
    {
        rect.y = *y;
    }

    SDL_RenderCopyEx( renderer, texture, NULL, &rect, angle, point, flip );
}


void Text::fadeIO( int value )
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


void Text::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( texture, alpha );
}

void Text::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( texture, red, green, blue );
}

void Text::setBlendMode( SDL_BlendMode blendMode )
{
    SDL_SetTextureBlendMode( texture, blendMode );
}


int Text::getWidth()
{
    return rect.w;
}

int Text::getHeight()
{
    return rect.h;
}

void Text::setWidth( int w )
{
    rect.w = w;
}

void Text::setHeight( int h )
{
    rect.h = h;
}

int Text::getX()
{
    return rect.x;
}

int Text::getY()
{
    return rect.y;
}

void Text::setX( int x )
{
    rect.x = x;
}

void Text::setY( int y )
{
    rect.y = y;
}
