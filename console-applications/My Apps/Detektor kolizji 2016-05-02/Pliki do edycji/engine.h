#ifndef ENGINE_H
#define ENGINE_H

#include "intro.h"
#include "menu.h"
#include "desktop.h"
#include "hero.h"

class Engine
{
    Uint8 frame;    /* Obecny stan gry */
    Uint16 width;
    Uint16 height;
    bool quit;

    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;

    Intro intro;
    Menu menu;
    Desktop desktop;
    Hero hero;

public:

    Engine();
    ~Engine();

    bool load();
    bool init();

    void states();
    void events();
    void render();

    void free();
    void close();
};

#endif // ENGINE_H
