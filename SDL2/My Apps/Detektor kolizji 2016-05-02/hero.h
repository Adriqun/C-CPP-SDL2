#ifndef HERO_H
#define HERO_H

#include "texture.h"

class Hero
{
    float speed;
    float x, y;
    const Uint8* key;   /* Klawisze */

    Texture texture;

public:

    Hero();
    ~Hero();

    bool checkCollision( SDL_Rect rect ); /* Wykryj kolizje */

    void free();
    void motion( SDL_Rect rect ); /* Ruch postaci bez uzycia SDL_Event */

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );

};

#endif // HERO_H
