#pragma once

#include "monster.h"
#include <vector>
#include "chunk.h"

using namespace std;

class Enemy
{
    long long int counter;
    int howMany;

    vector <Monster*> enemy;
    Chunk punch;

public:

    Enemy();
    ~Enemy();
    void free();

    bool load();
    void faster( bool move );

    void mechanics( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );

    bool check( SDL_Rect a, SDL_Rect b );
    bool checkCollision( SDL_Rect a );
};
