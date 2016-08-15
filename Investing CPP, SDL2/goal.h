#pragma once
#include "texture.h"
#include "font.h"

class Goal
{
    Font* font;
    SDL_Color color;

    Texture* label;
    Texture* number;

    bool renderText;
    string inputText;

    unsigned long long cost;

    bool focus;
	SDL_Rect focusRect;

public:

    void sortString();	// delete spaces and sort
    unsigned long long strToInt( string s );

    Goal();
    ~Goal();
    void free();

    bool load( SDL_Renderer* &renderer, int title_bar_height );
    void render( SDL_Renderer* &renderer, int screen_width );
    void handle( SDL_Event &event );

    int getB();
	
	unsigned long long getCost();
};
