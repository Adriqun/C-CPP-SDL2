#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

/* Klasa powstala dzieki dokumentacji SDL 2, oraz wielu pomocnych stron */
/* Ze wzgledu na ogromna ( jak dla mnie ) ilosc funkcji, podarowalem sobie poszczegolne ich wyjasnianie */
/* glownie z uwagi na brak uzytku duzej czesci z nich */

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
    void inversion();

    int getPitch();
    void* getPixels();
    void copyPixels( void* _pixels );
    Uint32 getPixel32( unsigned int x, unsigned int y );

    void setAlpha( Uint8 alpha );
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blendMode );

    bool createBlank( SDL_Renderer* &renderer, int w, int h, SDL_TextureAccess access = SDL_TEXTUREACCESS_STREAMING );
    void setAsRenderTarget( SDL_Renderer* &renderer );

    #ifdef _SDL_TTF_H
    bool loadFromRenderedText( SDL_Renderer* &renderer, TTF_Font* font, std::string textureText, SDL_Color textColor );
    #endif

    bool loadFromFile( SDL_Renderer* &renderer, SDL_Window* window, std::string path );
    void render( SDL_Renderer* &renderer, int x, int y, SDL_Rect* srcRect = NULL, double angle = 0.0, SDL_Point* point = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

};

#endif // TEXTURE_H
