#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <string>

class Texture
{

protected:

    void* pixels;
    int pitch;

    int width, height;
    SDL_Texture* texture;

public:

    Texture();
    ~Texture();
    void free();

    int getWidth();
    int getHeight();

    bool lockTexture();
    bool unlockTexture();

    int getPitch();
    void* getPixels();
    void copyPixels( void* _pixels );
    Uint32 getPixel32( unsigned int x, unsigned int y );

    void setAlpha( Uint8 alpha );
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blendMode );

    bool createBlank( SDL_Renderer* &renderer, int _width, int _height, SDL_TextureAccess access = SDL_TEXTUREACCESS_STREAMING );
    void setAsRenderTarget( SDL_Renderer* &renderer );
    #ifdef _SDL_TTF_H
    bool loadFromRenderedText( TTF_Font* font, std::string textureText, SDL_Color textColor );
    #endif
    bool loadFromFile( SDL_Renderer* &renderer, SDL_Window* window, std::string path );
    void render( SDL_Renderer* &renderer, int x, int y, SDL_Rect* srcRect = NULL, double angle = 0.0, SDL_Point* point = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

};

#endif // TEXTURE_H
