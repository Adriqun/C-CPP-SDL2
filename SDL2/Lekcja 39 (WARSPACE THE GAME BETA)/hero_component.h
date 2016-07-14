#ifndef HERO_COMPONENT_H
#define HERO_COMPONENT_H

#include <SDL.h>
#include "debugger.h"

class Bullet
{
    Debugger debugger;

    Uint16 width, height;
    Uint8 vel;
    Uint16 counter;

    SDL_Texture* texture;
    SDL_Rect rect;

public:

    Bullet();
    ~Bullet();
    void free();

    SDL_Texture* loadTexture( SDL_Renderer *&renderer, std::string path );
    void load( SDL_Renderer *&renderer );

    void motion( SDL_Rect _rect, bool blockade );
    void render( SDL_Renderer *&renderer );
};

class Fire
{
    Debugger debugger;

    Uint16 width, height;
    Uint8 off_set, how_many;
    bool interlude;

    SDL_Texture* texture;
    SDL_Rect* srcrect;
    SDL_Rect dstrect;

public:

    Fire();
    ~Fire();
    void free();

    SDL_Texture* loadTexture( SDL_Renderer *&renderer, std::string path );
    void load( SDL_Renderer *&renderer );

    void motion( SDL_Rect &_rect );
    void render( SDL_Renderer *&renderer );
};

#endif // HERO_COMPONENT_H
