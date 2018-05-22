#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>
#include "debugger.h"

class Background
{
    Debugger debugger;

    Uint8 vel;
    Uint16 width, height;
    SDL_Texture* texture;
    SDL_Rect* arect;
    SDL_Rect* brect;

public:

    Background();
    ~Background();
    void free();

    SDL_Texture* loadTexture( SDL_Renderer *&renderer, std::string path );
    void load( SDL_Renderer *&renderer );

    void motion();
    void render( SDL_Renderer *&renderer );
};

#endif // BACKGROUND_H
