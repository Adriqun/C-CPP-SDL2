#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Texture
{
    int width;
    int height;
    SDL_Texture* texture;

public:

    Texture();
    ~Texture();
    void free();

    int getWidth();
    int getHeight();

    void setWidth( int width );
    void setHeight( int height );

    void setAlpha( Uint8 alpha );
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blendMode );

    bool createWithColor( SDL_Renderer* &renderer, Uint8 r, Uint8 g, Uint8 b, int w, int h );
    bool loadFromRenderedText( SDL_Renderer* &renderer, TTF_Font* font, std::string text, SDL_Color color );
    bool loadFromFile( SDL_Renderer* &renderer, SDL_Window* &window, std::string path );

    void render( SDL_Renderer* &renderer, int x, int y, SDL_Rect* srcRect = NULL, double angle = 0.0, SDL_Point* point = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
};
