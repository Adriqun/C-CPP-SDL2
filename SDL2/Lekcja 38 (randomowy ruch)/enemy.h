#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include <SDL_image.h>

class Enemy
{
    SDL_Texture* texture;
    Uint16 width, height;
    Uint16 posX, posY;
    Uint8 velX, velY;
    SDL_Rect rect;
    double angle, angleC;

public:
    Enemy();
    void load( SDL_Renderer *&renderer );
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void render( SDL_Renderer *&renderer );
};

#endif // ENEMY_H
