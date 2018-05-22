#ifndef ENGINE_H
#define ENGINE_H

#include "menu.h"
#include "hero.h"
#include "enemy.h"

class Engine
{
    SDL_Rect screen;
    SDL_Event event;
    int8_t frame;
    SDL_Window* window;
    SDL_Renderer* renderer;

    void loadObjects();
    void renderObjects();
    void closeObjects();
    void closeProgram();

    Menu* menu;
    Background* background;
    Hero* hero;
    Enemy* enemy;

public:
    Engine();

    void startProgram();
    void renderProgram();
};

#endif // ENGINE_H
