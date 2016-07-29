#include "texture.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

Texture::Texture()
{
    rect.w = 0;
    rect.h = 0;
    rect.x = 0;
    rect.y = 0;
    texture = NULL;
}

Texture::~Texture()
{
    free();
}

void Texture::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;

        rect.w = 0;
        rect.h = 0;
        rect.x = 0;
        rect.y = 0;
    }
}



unsigned Texture::getWidth()
{
    return rect.w;
}

unsigned Texture::getHeight()
{
    return rect.h;
}

void Texture::setWidth( unsigned w )
{
    rect.w = w;
}

void Texture::setHeight( unsigned h )
{
    rect.h = h;
}



void Texture::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( texture, alpha );
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( texture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blendMode )
{
    SDL_SetTextureBlendMode( texture, blendMode );
}



bool Texture::createWithColor( SDL_Renderer* &renderer, Uint8 r, Uint8 g, Uint8 b, unsigned w, unsigned h )
{
    free();

    SDL_Surface* surface = SDL_CreateRGBSurface( 0, w, h, 32, 0, 0, 0, 0 );
    if( surface == NULL )
    {
        printf( "Not created blank surface\n" );
        printf( "Error %s\n", SDL_GetError() );
    }
    else
    {
        SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, r, g, b ) );
        texture = SDL_CreateTextureFromSurface( renderer, surface );

        if( texture == NULL )
        {
            printf( "Not created texture from surface\n" );
            printf( "Error %s\n", SDL_GetError() );
        }
        else
        {
            rect.w = w;
            rect.h = h;
        }
    }

    SDL_FreeSurface( surface );
    surface = NULL;

    return texture != NULL;
}

bool Texture::loadFromRenderedText( SDL_Renderer* &renderer, TTF_Font* font, string text, SDL_Color color )
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Blended( font, text.c_str(), color );
    if( textSurface == NULL )
    {
        printf( "Not created surface from text\n" );
        printf( "Error %s\n", TTF_GetError() );
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == NULL )
        {
            printf( "Not created texture from surface text\n" );
            printf( "Error %s\n", SDL_GetError() );
        }
        else
        {
            rect.w = textSurface->w;
            rect.h = textSurface->h;
        }

        SDL_FreeSurface( textSurface );
        textSurface = NULL;
    }

    return texture != NULL;
}

bool Texture::loadFromFile( SDL_Renderer* &renderer, SDL_Window* &window, string path )
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
        }

        SDL_FreeSurface( surface );
        surface = NULL;
    }

    return texture != NULL;
}



void Texture::render( SDL_Renderer* &renderer, int x, int y, SDL_Rect* srcRect, double angle, SDL_Point* point, SDL_RendererFlip flip )
{
    rect.x = x;
    rect.y = y;

    if( srcRect != NULL )
    {
        rect.w = srcRect->w;
        rect.h = srcRect->h;
    }

    SDL_RenderCopyEx( renderer, texture, srcRect, &rect, angle, point, flip );
}
