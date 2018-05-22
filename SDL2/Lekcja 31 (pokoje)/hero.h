#ifndef HERO_H
#define HERO_H

#include <SDL.h>
#include <string>
#include <stdio.h>
#include <SDL_image.h>

class  Hero // 2016.02.19 jestm z Ania
{
    SDL_Texture* texture;
    SDL_Rect rect;

    int vel;
    float velX, velY;

public:

    Hero();
    ~Hero();

    void free();
    void load( SDL_Renderer* &renderer );

    void render( SDL_Renderer* &renderer );
    void motion();

    SDL_Rect getRect();
};

#endif // HERO_H
