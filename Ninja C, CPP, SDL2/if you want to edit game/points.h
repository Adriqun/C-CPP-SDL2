#pragma once

#include "texture.h"
#include "font.h"

using namespace std;

class Points
{
    int howMany;
    Uint8 alpha;

    int x;
    int y;
    int width;
    Texture texture;

    Font font;
    SDL_Color color;

public:

    Points();
    ~Points();
    void free();

    string intToStr( int path );
    int strToInt( string path );
    void counting( int* tab, int n );

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer, bool move );
    void sumUp();

    void add( bool yes );

    void fadeIn();
    void fadeOut();
};
