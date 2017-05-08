#ifndef DESKTOP_H
#define DESKTOP_H

#include "texture.h"

class Desktop
{
    enum buttons    /* Dla wygody */
    {
        BACK = 6,
        RECT,
        CIRCLE,
        LIGHT
    };

    bool light;     /* Zmienna ktora mowi nam o przycisku LIGHT */
    Uint8 nr, type; /* Ilosc elemetow w tablicy, typ obiektu na ktory uzytownik kliknal */
    Uint8 value;    /* Element z tablicy ktory ma zostac wyswietlony rect/circle */
    Uint16 *x, *y;

    TTF_Font* font;
    Texture* texture;
    std::string name;

public:

    Desktop();
    ~Desktop();

    void free();
    bool isClose();     /* Jesli obiekt skonczyl swoje zadanie */

    void lines( SDL_Renderer* &renderer );      /* Linie ktore rysuje program */
    void events( SDL_Event &event );

    SDL_Rect getFigure();
    bool reloadHero();

    void render( SDL_Renderer* &renderer );
    bool load( SDL_Renderer* &renderer, SDL_Window* &window );          /* Wczytuje wszystkie pliki */

private:

    bool create();                                                      /* Tworzy tablice */
    bool setMedia( SDL_Renderer* &renderer, SDL_Window* &window );      /* Ustawia tekstury */
    bool setCaption( SDL_Renderer* &renderer, SDL_Window* &window );    /* Ustawia napisy */

};

#endif // DESKTOP_H
