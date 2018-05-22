#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>

class Window
{
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

    //Window data
    SDL_Window* window;

    int windowID;

    //Window dimensions
    int width;
    int height;

    //Window focus
    bool mouseFocus;
    bool keyboardFocus;
    bool fullScreen;
    bool minimized;
    bool shown;

public:
    SDL_Renderer* renderer;

    Window();
    bool init();
    void handleEvent( SDL_Event& e );
    void focus();
    void render();
    void free();

    int getWidth();
    int getHeight();

    bool hasMouseFocus();
    bool hasKeyboardFocus();
    bool isMinimized();
    bool isShown();
    void renderTexture( SDL_Texture* texture );
};

#endif // WINDOW_H
