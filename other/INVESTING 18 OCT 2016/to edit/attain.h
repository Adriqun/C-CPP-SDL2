#pragma once
#include "tax.h"
#include "font.h"
#include "texture.h"
#include <vector>

class Attain
{
    Font font;

    Texture name;
    Texture result;
	
	int main_currency;
	float eur;
	float usd;
	float gbp;
	
public:
	
	string intToStr( unsigned long long n );

    Attain();
    ~Attain();
    void free();

    bool load( SDL_Renderer* &renderer, int goal_height );
    void render( SDL_Renderer* &renderer, int screen_width );
	
	int getB();
	void setCurrency( float eur, float usd, float gbp );
	void setMainCurrency( int type );
	void setAttain( vector <Tax*> mother, unsigned long long target, SDL_Renderer* &renderer );
};
