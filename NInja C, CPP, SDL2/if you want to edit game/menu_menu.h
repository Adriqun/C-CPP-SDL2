#pragma once

#include "chunk.h"
#include "music.h"
#include "text.h"
#include "image.h"

class Menu
{
    enum
    {
        TITLE = 0,
        PLAY,
        SCORES,
        OPTIONS,
        EXIT,
        AMOUNT_T,

        BACKGROUND = 0,
        ARROW,
        AMOUNT_I
    };

    int state;
    const Uint8* key;

    Text* text;
    Image* image;

    Chunk click;
    Music music;

    int arrow_nr;
    int arrow_offset;
    SDL_Rect** arrow_rect;

public:

    Menu();
    ~Menu();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );
    void play();

    int getState();
    void control();

    // Animation
    void fadeIO( int value );
};

