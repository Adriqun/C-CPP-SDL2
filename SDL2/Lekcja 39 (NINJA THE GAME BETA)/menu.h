#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "debugger.h"

class Menu
{
    SDL_Texture* rain;
    Uint16 rain_counter;

    SDL_Texture* menu;
    SDL_Texture* info;

    Mix_Music* music;
    Mix_Chunk* chunk;

    SDL_Texture* pointer;
    SDL_Rect rect;

    Uint8 alpha_counter;
    Uint8 state, state_counter;
    Uint8 frame_counter;
    const Uint8 *key;

public:

    Menu();
    ~Menu();
    void free();

    std::string int_to_string( int n );
    SDL_Texture* loadTexture( SDL_Renderer* &renderer, std::string path );
    void setAlpha( SDL_Texture *&texture );

    void load( SDL_Renderer* &renderer );
    void motion();
    void playingMusic();

    void renderRain( SDL_Renderer* &renderer );
    void renderButtons( SDL_Renderer* &renderer );
    void render( SDL_Renderer* &renderer );

    Uint8 getFrame();
};

#endif // MENU_H
