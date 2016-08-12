#include "profit.h"

void Profit::sortString()
{
    for( unsigned i = 0; i < inputText.length(); i ++ )
    {
        if( inputText[ i ] == ' ' )
        {
            inputText.erase( i, 1 );
        }
    }

    string newInputText = "";
    int c = inputText.length()-1;
    for( unsigned i = 0; i < inputText.length(); i ++ )
    {
        newInputText += inputText[ i ];

        if( c%3 == 0 )
        {
            newInputText += ' ';
        }

        c --;
    }
    inputText = newInputText;
}

// Only +numbers
long long Profit::strToInt( string s )
{
    long long tmp = 0;

    for( unsigned i = 0; i < s.size(); i++ )
    {
        if( s[ i ] == ' ' )
            continue;

        tmp = 10 * tmp + s[ i ] - 48;
    }

    return tmp;
}

Profit::Profit( char c )
{
	texture = NULL;
	name = "";
	renderText = false;
	cost = 0;
	inputText = "";
	
	focus = false;
	focus_w = 0;
	
	this->c = c;
	nr = 0;
}

Profit::~Profit()
{
	free();
}

void Profit::free()
{
	font.free();
	
	if( texture != NULL )
	{
		for( int i = 0; i < nr; i ++ )
		{
			texture[ i ].free();
		}
		
		delete [] texture;
		texture = NULL;
		nr = 0;
	}
	
	name = "";
	renderText = false;
	cost = 0;
	inputText = "";
	
	focus = false;
	focus_w = 0;
	
	c = 'c';
	nr = 0;
}

	
bool Profit::load( SDL_Renderer* &renderer, int attain_pos_y )
{
	register bool success = true;
	
	if( !font.load( "data/Chunkfive Ex.ttf", 20 ) )
	{
		success = false;
	}
	
	nr = 
	texture = new Texture [ nr ];
	
	return success;
}

void Profit::render( SDL_Renderer* &renderer )
{
	
}
