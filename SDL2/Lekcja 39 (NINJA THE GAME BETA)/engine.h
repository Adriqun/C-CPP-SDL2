#ifndef ENGINE_H
#define ENGINE_H

#include <SDL_ttf.h>
#include <SDL_image.h>

#include "menu.h"
#include "chart.h"
#include "hero.h"

class Engine
{
    int8_t frame;
    SDL_Event event;
    SDL_Renderer* renderer;
    SDL_Window* window;

    void renderObjects();
    void closeObjects();

    Menu menu;
    Chart chart;
    Wall wall;
    Hero hero;

public:
    Engine();

    void startProgram();
    void renderProgram();
    void closeProgram();
};

#endif // ENGINE_H
