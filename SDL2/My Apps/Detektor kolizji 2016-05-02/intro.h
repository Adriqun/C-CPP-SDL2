#ifndef INTRO_H
#define INTRO_H

#include "texture.h"

class Intro
{
    Uint8 nr;           /* Liczba tekstur, x i y */
    Uint8 counter;      /* Licznik alpha */
    Uint16 *x, *y;      /* X i y danej tekstury */

    TTF_Font* font;
    Texture* texture;

public:

    Intro();
    ~Intro();

    void free();        /* Niszczy tablice jesli to konieczne */
    bool isClose();     /* Przekazuje informacje o zakonczeniu intra */

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer );

};

#endif // INTRO_H
