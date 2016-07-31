#pragma once
#include "texture.h"
#include "font.h"

class Goal
{
    Font font;
    SDL_Color color;

    int x, y;
    Texture texture;
    Texture goal_text;

    bool renderText;
    string inputText;

    unsigned long long cost;

    bool focus;

public:

    unsigned long long strToInt( string s );

    Goal();
    ~Goal();
    void free();

    bool load( SDL_Renderer* &renderer );
    void render( SDL_Renderer* &renderer );
    void handle( SDL_Event &event );

    unsigned getWidth();
    unsigned getHeight();
};
