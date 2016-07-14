#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Window
{
public:

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;


    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;


    Window();
    ~Window();

    void createWindow( std::string title, int w, int h );
    void createRenderer();
    void render();
    void free();
};


#endif // WINDOW_H
