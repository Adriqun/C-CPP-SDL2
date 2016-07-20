#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
using namespace std;

class Image
{
    // Texture
    SDL_Texture* texture;
    SDL_Rect rect;

    // Alpha
    Uint8 alpha;

public:

    Image();
    ~Image();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window, string path, int x, int y );
    void render( SDL_Renderer* &renderer, int* x = NULL, int* y = NULL, SDL_Rect* srcRect = NULL, double angle = 0.0, SDL_Point* point = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

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
