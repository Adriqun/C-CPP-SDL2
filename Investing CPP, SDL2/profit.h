#pragma once
#include "texture.h"
#include "font.h"

class Profit
{
	Font font;
	SDL_Color color;
	
	int nr;
	Texture* texture;
	string name;
	
	bool renderText;
    string inputText;
	
	long long cost;
	
	bool focus;
	int focus_w;
	
	char c;
	
	int x, y;
	
public:
	
	void sortString();
	long long strToInt( string s );
	
	Profit( char c = 'c', int x = 0, int y = 0 );
	~Profit();
	void free();
	
	bool load( SDL_Renderer* &renderer, SDL_Window* &window );
	void render( SDL_Renderer* &renderer );
};
