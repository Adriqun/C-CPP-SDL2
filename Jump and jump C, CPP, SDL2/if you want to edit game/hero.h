#pragma once

#include "texture.h"
#include "chunk.h"
#include <vector>

class Hero
{
    enum
    {
        RUN_START = 0,
        RUN_END =  3,
        IDLE,
        JUMP,
        ATTACK,
        DEAD,
        AMOUNT
    };

    /* position x and position y, velocity */
    float x;
    float y;
    float vel;

    /* Offset and delay for offset */
    int offset;
    double delay;

    /* Texture, rectangle and flip */
    Texture texture;
    SDL_Rect** rect;
    SDL_RendererFlip flip;

    /* Our keyboard */
    const Uint8* key;

    /* state for jump */
    int jump_state;

    /* Chunk for attack */
    Chunk woosh;

    bool dead;
    Uint8 alpha;

    Texture score;

public:

    Hero();
    ~Hero();
    void free();

    void idle();
    void jump();
    bool run();
    void gravitation();
    void attack( bool shot );
    bool getDead( int h );
    void setDead( bool yes );

    void backX( int back );
    void backY( int back );

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );

    float getX();
    float getY();
    SDL_Rect getRect();

    void fadeIn();
    void fadeOut();

    void render10( SDL_Renderer* &renderer, bool yes );
};
