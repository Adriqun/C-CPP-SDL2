#pragma once

#include <SDL.h>

class Core
{
    int width;
    int height;

    bool quit;

    int frame;
    int FPS;

public:

    Core( int width, int height, int FPS = 60 );
    ~Core();

    bool createWindow( SDL_Window* &window, Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, const char* path = "" );
    bool setWindowIcon( SDL_Window* &window, const char* icon );

    bool createRenderer( SDL_Window* &window, SDL_Renderer* &renderer, Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, int index = -1 );

    void topRender( SDL_Renderer* &renderer );
    void botRender( SDL_Renderer* &renderer );

    int getWidth();
    int getHeight();

    bool getQuit();
    void setQuit();

    int getFrame();
    void setFrame( int frame );

    int getFPS();
    void setFPS( int FPS );
};
