#ifndef HERO_H
#define HERO_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

class Hero
{
    SDL_Texture* texture;
    SDL_Rect rect;

    float velX, velY;
    int vel, jump;
    int counter;

public:

    Hero();
    ~Hero();

    void load( SDL_Renderer* &renderer );
    void motion( SDL_Rect _rect );
    void render( SDL_Renderer* &renderer );

    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );

    SDL_Rect getRect();
    void setRect( SDL_Rect _rect );

    float getVelX();
    float getVelY();

    void free();
};


#endif // HERO_H
