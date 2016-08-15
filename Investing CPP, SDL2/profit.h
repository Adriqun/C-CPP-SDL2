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
	
	bool focus_v, focus_n;
	int focus_w_v, focus_w_n;
	
	char c;
	
	int x, y;
	
	bool thrash;
	
public:
	
	void sortString();
	long long strToInt( string s );
	
	Profit( char c = 'c', int x = 0, int y = 0 );
	~Profit();
	void free();
	
	bool load( SDL_Renderer* &renderer, SDL_Window* &window );
	void render( SDL_Renderer* &renderer );
	void handle( SDL_Event &event ); 
	
	bool isThrash();
};
