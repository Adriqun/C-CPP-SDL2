#include "texture.h"
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>

Texture::Texture()
{
    pixels = NULL;
    pitch = 0;
    width = 0;
    height = 0;
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

        pixels = NULL;
        pitch = 0;
        width = 0;
        height = 0;
    }
}



int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}



bool Texture::lockTexture()
{
    bool success = true;

    // jesli tekstura jest juz zablokowana
    if( pixels != NULL )
    {
        printf( "Tekstura jest juz zablokowana!\n" );
        success = false;
    }
    else
    {
        if( SDL_LockTexture( texture, NULL, &pixels, &pitch ) != 0 )
        {
            printf( "Nie mozna zablokowac tekstury! Error %s\n", SDL_GetError() );
            success = false;
        }
    }

    return success;
}

bool Texture::unlockTexture()
{
    bool success = true;

    if( pixels == NULL )
    {
        printf( "Tekstura nie jest zablokowana!\n" );
        success = false;
    }
    else
    {
        SDL_UnlockTexture( texture );
        pixels = NULL;
        pitch = 0;
    }

    return success;
}



void* Texture::getPixels()
{
    return pixels;
}

int Texture::getPitch()
{
    return pitch;
}

Uint32 Texture::getPixel32( unsigned int x, unsigned int y )
{
    // konwertowanie pixelu do 32 bitow
    Uint32* newPixels = static_cast< Uint32* > ( pixels );

    return newPixels[ ( y * ( pitch / 4 ) ) + x ];
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



bool Texture::createBlank( SDL_Renderer* &renderer, int _width, int _height, SDL_TextureAccess access )
{
    texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, access, _width, _height );
    if( texture == NULL )
    {
        printf( "Nie utworzono pustej tekstury! Error: %s\n", SDL_GetError() );
    }
    else
    {
        width = _width;
        height = _height;
    }

    return texture != NULL;
}

void Texture::setAsRenderTarget( SDL_Renderer* &renderer )
{
    SDL_SetRenderTarget( renderer, texture );
}



#ifdef _SDL_TTF_H
bool Texture::loadFromRenderedText( TTF_Font* font, std::string textureText, SDL_Color textColor )
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Nie utworzono powierzchni z tekstu Error: %s\n", TTF_GetError() );
    }
    else
    {
        textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( textTexture == NULL )
        {
            printf( "Nie utworzono tekstury z powierzchni tekstu! Error: %s\n", SDL_GetError() );
        }
        else
        {
            width = textSurface->w;
            height = textSurface->h;
        }

        SDL_FreeSurface( textSurface );
    }

    return textTexture;
}
#endif

bool Texture::loadFromFile( SDL_Renderer* &renderer, SDL_Window* &window, std::string path )
{
    free();

    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Nie wczytano obrazu %s, Error %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        SDL_Surface* formattedSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface( window )->format, NULL );
        if( formattedSurface == NULL )
        {
            printf( "Nie sformatowano powierzchni Error %s\n", SDL_GetError() );
        }
        else
        {
            newTexture = SDL_CreateTexture( renderer, SDL_GetWindowPixelFormat( window ), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
            if( newTexture == NULL )
            {
                printf( "Nie utworzono czystej tekstury Error %s\n", SDL_GetError() );
            }
            else
            {
                SDL_SetTextureBlendMode( newTexture, SDL_BLENDMODE_BLEND );
                SDL_LockTexture( newTexture, NULL, &pixels, &pitch ); // blokowanie tekstury dla manipulacji
                memcpy( pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h ); // kopiowanie pixeli z powierzchni

                SDL_UnlockTexture( newTexture ); // odblokowanie tekstury w celu zaktualizowania
                pixels = NULL;

                /*Uint32* newPixels = static_cast< Uint32* >( pixels );
                int pixelCount = ( pitch / 4 ) * height;

                Uint32 colorKey = SDL_MapRGB( formattedSurface->format, 0, 0xFF, 0xFF );
                Uint32 transparent = SDL_MapRGBA( formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00 );

                for( int i = 0; i < pixelCount; ++i )
                {
                    if( newPixels[ i ] == colorKey )
                    {
                        newPixels[ i ] = transparent;
                    }
                }*/

                width = formattedSurface->w;
                height = formattedSurface->h;
            }

            SDL_FreeSurface( formattedSurface );
            formattedSurface = NULL;
        }

        SDL_FreeSurface( loadedSurface );
        loadedSurface = NULL;
    }

    texture = newTexture;
    return newTexture != NULL; // jesli bedzie rozne od NULL'a to zwroci prawde
}

void Texture::render( SDL_Renderer* &renderer, int x, int y, SDL_Rect* srcRect, double angle, SDL_Point* point, SDL_RendererFlip flip )
{
    SDL_Rect rect = { x, y, width, height };

    if( srcRect != NULL )
    {
        rect.w = srcRect->w;
        rect.h = srcRect->h;
    }

    SDL_RenderCopyEx( renderer, texture, srcRect, &rect, angle, point, flip );
}
