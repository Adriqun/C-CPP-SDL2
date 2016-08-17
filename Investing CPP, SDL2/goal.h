#pragma once
#include "texture.h"
#include "font.h"

class Goal
{
	
protected:
	
    Font font;
	
	string name_s;
	string line_s;

    Texture name;
    Texture line;

    bool renderText;
    string inputText;

    unsigned long long cost;

    bool focus;
	SDL_Rect focusRect;
	
	int bot_scope;
	int top_scope;
	
	bool renderEdges;
	bool space;
	int letters;

public:

    void sortString();	// delete spaces then add
    unsigned long long strToInt( string s );	// Only positive numbers

    Goal( int letters = 16, bool space = true, bool renderEdges = true, string name_s = "", string line_s = "", int bot_scope = 48, int top_scope = 57 );
    ~Goal();
    void free();

    bool load( SDL_Renderer* &renderer, int title_bar_height );
    void render( SDL_Renderer* &renderer, int screen_width );

    void handle( SDL_Event &event );

    int getB();
	
	unsigned long long getCost();
};
