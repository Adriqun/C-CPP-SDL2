#ifndef DOT_H
#define DOT_H

#include "texture.h"

class Dot
{
    int DOT_VEL;
    float velX, velY;
    SDL_Rect collider;

public:
    Texture dotTexture;

    Dot();
    bool checkCollision( SDL_Rect a, SDL_Rect b );
    void handleEvent();
    void move( SDL_Rect wall, int scr_wid, int scr_hei );
    void render( SDL_Renderer* &renderer );

};


#endif // DOT_H
