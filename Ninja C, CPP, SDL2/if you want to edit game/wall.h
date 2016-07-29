#pragma once

#include "texture.h"
#include "music.h"
#include <fstream>
#include <vector>
using namespace std;

class Wall
{
    int nr;
    fstream file;

    vector <int>* x;
    vector <int>* y;
    Texture* texture;

    float myx;
    Music music;
    Uint8 alpha;

public:

    string intToStr( int path );
    int strToInt( string path );

    Wall();
    ~Wall();
    void free();

    bool load( SDL_Renderer* &renderer, SDL_Window* &window );
    void render( SDL_Renderer* &renderer, bool move = false );

    float getX();

    bool check( SDL_Rect &a, SDL_Rect &b, Uint8 type );
    int checkCollision( SDL_Rect a );

    void setMousePosition( int &type, SDL_Point &point );
    void addToFile( int &type, int px, int py, int ax );
    void addBlock( SDL_Renderer* &renderer, SDL_Event &event );
    void renderLive( SDL_Renderer* &renderer );

    void fadeIn();
    void fadeOut();

    void play();
    void pause();
};
