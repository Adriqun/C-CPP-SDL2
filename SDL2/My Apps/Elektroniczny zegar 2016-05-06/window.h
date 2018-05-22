#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <string>

class Window
{
    int displayID;
    unsigned int windowID;

    SDL_Window* window;
    SDL_Renderer* renderer;

    int width;
    int height;

    //Window focus
    bool mouseFocus;
    bool keyboardFocus;
    bool fullScreen;
    bool minimized;
    bool shown;

    int stringToInt( std::string &path );
    bool setDimensions( int &x, int &y );

public:
    Window();
    ~Window();
    void free();

    bool createWindow( std::string icon, std::string path = "window", Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    bool createRenderer( int index = -1, Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    void handle( SDL_Event &e );
    void focus();

    void start();
    void present();

    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();

    int getWidth();
    int getHeight();

    bool hasMouseFocus();
    bool hasKeyboardFocus();
    bool isMinimized();
    bool isShown();

};

#endif // WINDOW_H
