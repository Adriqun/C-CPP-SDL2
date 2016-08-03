#pragma once
#include "texture.h"
#include "font.h"

class Goal
{
    Font font;
    SDL_Color color;

    Texture goal;
    Texture number;

    bool renderText;
    string inputText;

    unsigned long long cost;

    bool focus;
    int focus_w;

public:

    void sortString();
    unsigned long long strToInt( string s );

    Goal();
    ~Goal();
    void free();

    bool load( SDL_Renderer* &renderer, int title_bar_posY );
    void render( SDL_Renderer* &renderer, int screen_width );
    void handle( SDL_Event &event );

    int getW();
    int &getH();
    int &getX();
    int &getY();
};
