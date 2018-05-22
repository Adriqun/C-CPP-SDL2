#ifndef INTRO_H
#define INTRO_H

#include <SDL.h>
#include <string>

class Intro
{
    Uint8 counter;
    SDL_Rect* rect;
    SDL_Texture* texture;

    Uint32 fps;
    Uint32 startTicks;

public:

    Intro();
    ~Intro();
    SDL_Texture* loadTexture( SDL_Renderer* &renderer, std::string path );
    void load( SDL_Renderer* &renderer, Uint16 w, Uint16 h );
    void render( SDL_Renderer* &renderer, SDL_Event &event );
};

#endif // INTRO_H
