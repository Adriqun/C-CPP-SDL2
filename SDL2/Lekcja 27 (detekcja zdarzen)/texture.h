#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <string>
#include <stdio.h>
#include <SDL_image.h>

class Texture // 2016-02-18 jestem dalej z Ania K.
{
    SDL_Texture* texture;

    uint16_t width;
    uint16_t height;

public:

    Texture();
    ~Texture();

    void loadTexture( SDL_Renderer* &renderer, std::string path );
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );

    uint16_t getWidth();
    uint16_t getHeight();

    void free();
    void render( SDL_Renderer* &renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
};

class Rect
{
public:

    int x;
    int y;

    uint16_t w;
    uint16_t h;

    Rect();
};

#endif // TEXTURE_H
