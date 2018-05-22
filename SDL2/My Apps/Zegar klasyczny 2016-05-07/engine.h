#ifndef ENGINE_H
#define ENGINE_H

#include "core.h"
#include "window.h"
#include "intro.h"
#include "clock.h"

class Engine
{
    SDL_Event event;
    bool quit;
    unsigned int frame;

    Core* core;
    Window* window;
    Intro* intro;
    Clock* clock;


public:

    Engine();
    bool init();
    void loop();
    void close();

    bool load();
    void render();
    void handle();
    void free();
};

#endif // ENGINE_H
