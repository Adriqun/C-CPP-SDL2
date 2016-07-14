#ifndef ENGINE_H
#define ENGINE_H

#include "texture.h"
#include <vector>

class Engine
{
    Uint16 frame;
    Uint16 width;
    Uint16 height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event* event;

    std::vector <Texture> textureVector;

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
