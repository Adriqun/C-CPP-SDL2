#include "texture.h"
#include <iostream>
Texture::Texture()
{
    texture = NULL;
    width = 0;
    height = 0;
}

Texture::~Texture()
{
    free();
}

void Texture::loadTexture( SDL_Renderer* &renderer, std::string path )
{
    free();

    SDL_Surface* surface = IMG_Load( path.c_str() );

    if( surface == NULL )
        printf( "Nie wczytano %s Error %s\n", path.c_str(), IMG_GetError() );
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, surface );

        if( texture == NULL )
            printf( "Nie utworzono tekstury z %s Error %s\n", path.c_str(), IMG_GetError() );
        else
        {
            width = surface->w;
            height = surface->h;
        }

        SDL_FreeSurface( surface );
    }
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( texture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( texture, blending );
}

void Texture::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( texture, alpha );
}

uint16_t Texture::getWidth()
{
    return width;
}

uint16_t Texture::getHeight()
{
    return height;
}

void Texture::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void Texture::render( SDL_Renderer* &renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = { x, y, width, height };

    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );
}

Rect::Rect()
{
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}
