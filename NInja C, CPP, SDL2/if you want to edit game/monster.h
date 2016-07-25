#pragma once

#include "texture.h"

using namespace std;

class Monster
{
    int nr;
    int end;
    int vel;

    int x;
    int y;
    Texture texture;
    SDL_Rect** rect;
    SDL_RendererFlip flip;

    Uint8 direction;
    string path;

    int offset;
    int delay;

    bool hit;
    Uint8 alpha;

public:

    Monster( int end, int nr, string path );
    ~Monster();
    void free();

    void faster();

    void mechanics();
    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );

    void setHit();

    SDL_Rect getRect();
    Uint8 getDirection();
    Uint8 getAlpha();
};
