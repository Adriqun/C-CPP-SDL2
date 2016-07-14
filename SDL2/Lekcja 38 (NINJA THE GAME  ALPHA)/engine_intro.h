#ifndef ENGINE_INTRO_H
#define ENGINE_INTRO_H

#include <SDL.h>
#include <string>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class Intro
{
    SDL_Texture* texture;
    Mix_Music* music;
    SDL_Rect rect;
    uint8_t counter;

    //klatki na sekunde
    Uint32 fps;
    Uint32 startTicks;

public:
    Intro();

    void get_tex( SDL_Renderer* &renderer, std::string path );
    std::string int_to_string( int n );
    void draw( SDL_Renderer* &renderer );

    void start();
    void set_fps();
};

#endif // ENGINE_INTRO_H
