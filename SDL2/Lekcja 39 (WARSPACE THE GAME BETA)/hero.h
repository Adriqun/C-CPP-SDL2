#ifndef HERO_H
#define HERO_H

#include "debugger.h"
#include "hero_component.h"
#include "vector"

class Hero
{
    Debugger debugger;
    Bullet* bullet;
    Fire fire;

    Uint16 width, height;
    int vel;
    int velX, velY;
    int counter, how_many;

    const Uint8* key;
    SDL_Texture* texture;
    SDL_Rect rect;

public:

    Hero();
    ~Hero();
    void free();

    SDL_Texture* loadTexture( SDL_Renderer *&renderer, std::string path );
    void load( SDL_Renderer *&renderer );

    void motion();
    void render( SDL_Renderer *&renderer );
};

#endif // HERO_H
