#ifndef ENEMY_H
#define ENEMY_H

#include "texture.h"
#include <vector>

class Ant
{
    Uint8 number;
    Uint8 offset;
    Uint8 start;
    Uint8 finish;
    SDL_Rect** rect;

    int speed;
    int x, y;
    Texture texture;

public:

    Ant();
    ~Ant();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window, std::string path );
    void setNOSR( Uint8 nr, Uint8 ffst, Uint8 strt, Uint8 fnsh );
    void setXYS( int strtX, int strtY, int spd );

    void render( SDL_Renderer* &renderer, SDL_RendererFlip flip = SDL_FLIP_NONE );
    int getX();
    void setX( int newX );
};

class Enemy
{
    Ant* ant_one;
    Ant* ant_two;
    Ant* ant_three;

    Uint8 antCounter;
    int x, y;
    std::vector < Ant* > antVector;

public:

    Enemy();
    ~Enemy();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    Uint8 getNr();
    SDL_Rect* getRects();

    void render( SDL_Renderer* &renderer );

};

#endif // ENEMY_H
