#ifndef HERO_H
#define HERO_H

#include <SDL.h>

class Shuriken
{
    Uint8 width, height;
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_RendererFlip flip;
    int8_t velX, velY, vel;
    Uint16 counter;
    double angle;

public:

    Shuriken();
    ~Shuriken();
    void free();
    void loadTexture( SDL_Renderer* &renderer, char* path );
    void load( SDL_Renderer* &renderer );
    void motion( SDL_Rect &dstRect, SDL_RendererFlip &_flip, const Uint8* &key );
    void render( SDL_Renderer* &renderer );
    Uint16 getCounter();
};

class Hero
{
    SDL_Texture* texture;
    SDL_RendererFlip flip;
    SDL_Rect* srcRect;
    SDL_Rect dstRect;
    Uint16 width;
    Uint8 height;

    int8_t velX, velY, vel;
    Uint8 off_set, jumpCounter, dimension;
    const Uint8* key;
    Shuriken shuriken;
    SDL_Point point;

public:

    Hero();
    ~Hero();
    void free();
    void loadTexture( SDL_Renderer* &renderer, char* path );
    void load( SDL_Renderer* &renderer );

    void motionX();
    void motionY();

    void setX( bool m );
    void setY( bool m );

    void render( SDL_Renderer* &renderer );

    Uint8 getDimension();
    SDL_Point getPoint();
    SDL_Rect getRect();
};

/* STANY POSTACI ( 6 )
    0 - stop
    1 - jump
    2 - attack
    3 - dead
*/

#endif // HERO_H
