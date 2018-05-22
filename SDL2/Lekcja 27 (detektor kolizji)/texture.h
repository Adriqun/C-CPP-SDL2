#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Texture
{
    SDL_Texture* texture;
    int width;
    int height;

public:
    Texture();
    ~Texture();
    bool loadFromFile( SDL_Renderer* &renderer, std::string path );
    void free();
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );
    void render( SDL_Renderer* &renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    int getWidth();
    int getHeight();

};


#endif // TEXTURE_H
