#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

class Engine
{
    Uint16 frame;
    Uint16 width;
    Uint16 height;
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;

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
