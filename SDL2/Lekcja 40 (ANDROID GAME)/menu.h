#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <string>

class Menu
{
    int8_t state;
    SDL_Texture* texture;
    SDL_Rect* rect;

public:

    Menu();
    ~Menu();

    SDL_Texture* loadTexture( SDL_Renderer* &renderer, std::string path );
    void load( SDL_Renderer* &renderer, Uint16 w, Uint16 h );
    void event( SDL_Renderer* &renderer, SDL_Event &e, Uint16 w, Uint16 h );
    void render( SDL_Renderer* &renderer );

    int8_t getFrame();
};

/*  NAME.  X.  Y.  W.  H.
    MENU. 146 451 218 124
    INFO. 136 607 253 102
    EXIT. 130 757 280 104
    BACK.  0   0  303 124
*/

class Background
{
    SDL_Rect* rect;
    SDL_Texture* texture;

public:

    Background();
    ~Background();

    SDL_Texture* loadTexture( SDL_Renderer* &renderer, std::string path );
    void load( SDL_Renderer* &renderer, Uint16 w, Uint16 h );
    void render( SDL_Renderer* &renderer );
};

#endif // MENU_H
