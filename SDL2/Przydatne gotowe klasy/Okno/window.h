#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <string>

class Window
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    unsigned int windowID;
    int displayID;

    int width;
    int height;

    //Window focus
    bool mouseFocus;
    bool keyboardFocus;
    bool fullScreen;
    bool minimized;
    bool shown;

public:

    Window( int w, int h );
    void free();

    bool init( std::string path = "window", int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED, Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    void handleEvent( SDL_Event &e );
    void focus();
    void render();

    int getWidth();
    int getHeight();

    bool hasMouseFocus();
    bool hasKeyboardFocus();
    bool isMinimized();
    bool isShown();

};

#endif // WINDOW_H
