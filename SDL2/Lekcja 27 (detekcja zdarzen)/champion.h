#ifndef CHAMPION_H
#define CHAMPION_H

#include "texture.h"

class Champion
{
    SDL_Rect rect;

    int WIDTH;
    int HEIGHT;
    int VEL;

    uint8_t velX, velY;
    uint32_t posX, posY;

public:
    Texture texture;

    Champion();

    bool checkCollision( SDL_Rect a, SDL_Rect b );

    void handleEvent( SDL_Event &e );

    void move( SDL_Rect &wall );

    void render( SDL_Renderer* &renderer );

};

#endif // CHAMPION_H
