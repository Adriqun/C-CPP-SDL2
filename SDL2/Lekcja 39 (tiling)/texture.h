#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Texture
{
    SDL_Texture* texture;
    int width;
    int height;

public:
    Texture();
    ~Texture();
    void free();

    bool loadFromFile( SDL_Renderer* &renderer, std::string path );
    void render( SDL_Renderer* &renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
};

#endif // TEXTURE_H
