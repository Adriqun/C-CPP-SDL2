#ifndef CORE_H
#define CORE_H

#include "detector.h"
#include "wall.h"
#include "hero.h"

class Core
{
    Uint16 SCREEN_WIDTH;
    Uint16 SCREEN_HEIGHT;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;

    Detector detector;
    Wall wall;
    Hero hero;

public:

    Core();

    void init();
    void close();

    void createWindow();
    void createRenderer();

    void load();
    void render();
    void renderAll();

};

#endif // CORE_H
