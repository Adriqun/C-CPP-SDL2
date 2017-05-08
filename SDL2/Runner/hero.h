#ifndef HERO_H
#define HERO_H

#include "texture.h"
#include <SDL_mixer.h>

class Hero
{
    Uint8 nr;
    Uint8 jump;
    Uint8 offset;

    Uint16 x, y;
    SDL_Rect** rect;
    Texture texture;

    Mix_Chunk* chunk;

public:

    Hero();
    ~Hero();

    void free();
    void control( SDL_Event &event );
    void jumping( Uint16 &h );

    bool load( SDL_Renderer* renderer, SDL_Window* window );
    void render( SDL_Renderer* renderer, Uint16 h, Uint8 value );

};

#endif // HERO_H
