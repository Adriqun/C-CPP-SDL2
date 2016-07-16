#pragma once

#include "texture.h"
#include "chunk.h"
#include "music.h"

class Menu
{
    enum object
    {
        BACKGROUND = 0,
        TITLE,
        PLAY,
        SCORES,
        OPTIONS,
        EXIT,
        ARROW,
        nr
    };

    int state;
    int alpha;

    int *x;
    int *y;
    Texture* texture;
    const Uint8* key;

    Chunk click;
    Music music;


public:

    Menu();
    ~Menu();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );

    int getState();
    void control();
};

