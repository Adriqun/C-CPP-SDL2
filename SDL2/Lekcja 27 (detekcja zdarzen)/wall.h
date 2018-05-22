#ifndef WALL_H
#define WALL_H

#include "texture.h"
#include <fstream>

class Wall
{
    SDL_Rect* rect;

    int WIDTH;
    int HEIGHT;
    int VEL;

    std::fstream file;
    uint16_t number;

public:
    Texture texture;

    Wall();

    int fast_atoi( std::string path );

    void loadFile( std::string path );

    void move();

    SDL_Rect getRect();

    void render( SDL_Renderer* &renderer );
};

#endif // WALL_H
