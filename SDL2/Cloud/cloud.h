#pragma once

#include "texture.h"

class Cloud
{
    Uint8 nr;
    Uint8 alpha;
    Uint8* gravity;

    int16_t* x;
    int16_t* y;
    Texture* drop;

    Uint8 vel;
    int16_t posX;
    int16_t posY;
    Texture cloud;

public:

    Cloud();
    ~Cloud();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window, std::string path );
    void render( SDL_Renderer* &renderer, int &w, int &h );

    void lightning();
};
