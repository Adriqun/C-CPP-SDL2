#ifndef MENU_H
#define MENU_H

#include "texture.h"

class Menu
{
    Uint8 nr, key; /* Liczba tekstur, x i y oraz dane polozenie strzalki */
    Uint8 counter; /* Licznik alpha */
    Uint16 *x, *y;

    TTF_Font* font;
    Texture* texture;

public:

    Menu();
    ~Menu();

    void free();
    Uint8 isClose();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void events( SDL_Event &event ); /* Przechwyc zdarzenia */
    void render( SDL_Renderer* &renderer );
};

#endif // MENU_H
