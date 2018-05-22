#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include "storm.h"

class Engine
{
    int frame;
    int width;
    int height;
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;

    Storm storm;

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
