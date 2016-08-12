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
	
public:
	
	void sortString();
	long long strToInt( string s );
	
	Profit( char c = 'c' );
	~Profit();
	void free();
	
	bool load( SDL_Renderer* &renderer, int attain_pos_y );
	void render( SDL_Renderer* &renderer );
};
