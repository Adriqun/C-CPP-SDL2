#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
using namespace std;

class Text
{
    // Font
    TTF_Font* font;
    SDL_Color color;

    // Texture
    SDL_Texture* texture;
    SDL_Rect rect;

    // Alpha
    Uint8 alpha;

public:

    Text();
    ~Text();

    void freeFont();
    void freeTexture();
    void free();

    bool loadFont( string path, int scale, Uint8 red, Uint8 green, Uint8 blue );
    bool createTexture( SDL_Renderer* &renderer, string text );

    void render( SDL_Renderer* &renderer, int* x = NULL, int* y = NULL, double angle = 0.0, SDL_Point* point = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    // Animation
    void fadeIO( int value );

    void setAlpha( Uint8 alpha );
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blendMode );

    int getWidth();
    int getHeight();
    void setWidth( int w );
    void setHeight( int h );

    int getX();
    int getY();
    void setX( int x );
    void setY( int y );
};
