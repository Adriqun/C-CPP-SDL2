#pragma once
#include "texture.h"
#include "font.h"

class Profit
{
	Font font;
	SDL_Color color;
	
	Texture texture;
	string name;
	
	bool renderText;
    string inputText;
	
	long long cost;
	
	bool focus;
	
public:
	
	void sortString();
	long long strToInt( string s );
	
};
