#include "texture.h"
#include <SDL_image.h>
#include <stdio.h>

Texture::Texture( Uint8 c )
{
    cage = c;
    slow = 1;
    offset = 0;
    width = 0;
    height = 0;

    texture = NULL;

    if( c != 0 )
    {
        rect = new SDL_Rect* [ cage ];
        for( Uint8 i = 0; i < cage; i ++ )
        {
            rect[ i ] = NULL;
            rect[ i ] = new SDL_Rect;
        }
    }


    angle = 0;
    center = NULL;
    flip = SDL_FLIP_NONE;
}

Texture::~Texture()
{
    SDL_DestroyTexture( texture );
    texture = NULL;

    if( cage != 0 )
    {
        for( Uint8 i = 0; i < cage; i ++ )
        {
            delete rect[ i ];
            rect[ i ] = NULL;
        }

        delete [] *rect;
        *rect = NULL;
    }
}



Uint16 Texture::getWidth()
{
    return width;
}

Uint16 Texture::getHeight()
{
    return height;
}



void Texture::setSlow( Uint8 s )
{
    slow = s;
}

void Texture::setOffset( Uint8 off )
{
    offset = off;
}

void Texture::runOffset( Uint8 startLoop, Uint8 endLoop )
{
    offset ++;
    if( offset > endLoop * slow )
        offset = startLoop;
}



void Texture::setFlip( SDL_RendererFlip f )
{
    flip = f;
}

void Texture::setAngle( double a )
{
    angle = a;
}

void Texture::setCenter( SDL_Point* c )
{
    center = c;
}



void Texture::setAlpha( Uint8 a )
{
    SDL_SetTextureAlphaMod( texture, a );
}

void Texture::setBlendMode( SDL_BlendMode b )
{
    SDL_SetTextureBlendMode( texture, b );
}

void Texture::setColor( Uint8 r, Uint8 g, Uint8 b )
{
    SDL_SetTextureColorMod( texture, r, g, b );
}

void Texture::setTexture( SDL_Renderer* &renderer, std::string path )
{
    SDL_Surface* surface = IMG_Load( path.c_str() );
    if( surface == NULL )
    {
        SDL_Log( "Nie wczytano %s Error %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_FreeSurface( surface );
        if( texture == NULL )
        {
            SDL_Log( "Nie utworzono tekstury z %s Error %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            if( cage != 0 )
                width = surface->w / cage;
            else
                width = surface->w;

            height = surface->h;

            if( cage != 0 )
            {
                for( Uint8 i = 0; i < cage; i ++ )
                {
                    rect[ i ]->x = i * width;
                    rect[ i ]->y = 0;
                    rect[ i ]->w = width;
                    rect[ i ]->h = height;
                }
            }
        }
    }
}

void Texture::render( SDL_Renderer* &renderer, SDL_Rect* &dstRect )
{
    if( cage != 0 )
        SDL_RenderCopyEx( renderer, texture, rect[ offset / slow ], dstRect, angle, center, flip );
    else
        SDL_RenderCopyEx( renderer, texture, NULL, dstRect, angle, center, flip );
}
