#include "title.h"
#include "font.h"
#include <stdio.h>

Title::Title()
{
	// empty
}

Title::~Title()
{
    free();
}

void Title::free()
{
	label.free();
	wallpaper.free();
}

bool Title::load( SDL_Renderer* &renderer, int screen_width )
{
    bool success = true;
	
    free();
	
	Font font;
    if( !font.load( "data/ShadedLarch_PERSONAL_USE.ttf", 50 ) )
    {
        success = false;
    }
    else
    {

		SDL_Color color = { 0xA4, 0xA4, 0xA4 };
		if( !label.loadFromRenderedText( renderer, font.get(), "investing", color ) )
		{
			success = false;
		}
		else
		{
			label.getX() = ( screen_width/2 ) - ( label.getW()/2 );
			label.getY() = 0;
		}
    }
	font.free();
	
	if( !wallpaper.createWithColor( renderer, 0x58, 0x74, 0x98, screen_width, label.getH() ) )
	{
		success = false;
	}

    return success;
}

void Title::render( SDL_Renderer* &renderer, int screen_width, int screen_height )
{
	wallpaper.render( renderer );
    label.render( renderer );
	
	//Edges
	SDL_SetRenderDrawColor( renderer, 0x58, 0x74, 0x98, 0xFF );
		
	SDL_RenderDrawLine( renderer, 0, 0, 0, screen_height );
	SDL_RenderDrawLine( renderer, 1, 0, 1, screen_height );
	SDL_RenderDrawLine( renderer, 2, 0, 2, screen_height );
		
	SDL_RenderDrawLine( renderer, screen_width-1, 0, screen_width-1, screen_height );
	SDL_RenderDrawLine( renderer, screen_width-2, 0, screen_width-2, screen_height );
	SDL_RenderDrawLine( renderer, screen_width-3, 0, screen_width-3, screen_height );
		
	SDL_RenderDrawLine( renderer, 0, screen_height-1, screen_width, screen_height-1 );
	SDL_RenderDrawLine( renderer, 0, screen_height-2, screen_width, screen_height-2 );
	SDL_RenderDrawLine( renderer, 0, screen_height-3, screen_width, screen_height-3 );
		
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

int &Title::getH()
{
    return label.getH();
}


void Value::free()
{
	label.free();
	wallpaper.free();
	type = 0;
	click.free();
}

bool Value::load( SDL_Renderer* &renderer, SDL_Window* &window, int goal_height )
{
    bool success = true;
	
    free();
	type = 0;
	
	int w, h;
	SDL_GetWindowSize( window, &w, &h );
	
	Font font;
    if( !font.load( "data/Chunkfive Ex.ttf", 35 ) )
    {
        success = false;
    }
    else
    {
		SDL_Color green = { 0x58, 0x70, 0x58 };
		if( !label.loadFromRenderedText( renderer, font.get(), "+", green ) )
		{
			success = false;
		}
		else
		{
			label.setAlpha( 100 );
			label.getX() = ( w/2 ) - ( label.getW()/2 ) - 5;
			label.getY() = goal_height;
		}
		
		font.setStyle( 1 );
		
		SDL_Color red = { 0xE8, 0x68, 0x50 };
		if( !wallpaper.loadFromRenderedText( renderer, font.get(), "-", red ) )
		{
			success = false;
		}
		else
		{
			wallpaper.setAlpha( 100 );
			wallpaper.getX() = ( w/2 ) + ( wallpaper.getW()/2 ) + 5;
			wallpaper.getY() = goal_height - 3;
		}
    }
	font.free();
	
	if( !click.load( "data/click.wav", 40 ) )
    {
        success = false;
    }
	
	startY = label.getB();

    return success;
}

void Value::render( SDL_Renderer* &renderer )
{
	wallpaper.render( renderer );
    label.render( renderer );
	
	for( int i = 0; i < profitVec.size(); i++ )
	{
		profitVec[ i ]->render( renderer );
	}
	
	SDL_SetRenderDrawColor( renderer, 0x58, 0x74, 0x98, 0xFF );
	
    SDL_RenderDrawLine( renderer, label.getX() -5, label.getY()-1, label.getX() -5, label.getB()-5 );
	SDL_RenderDrawLine( renderer, wallpaper.getR() +5, wallpaper.getY() +2, wallpaper.getR() +5, wallpaper.getB()-2 );
	
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

void Value::handle( SDL_Event &event, SDL_Renderer* &renderer, SDL_Window* &window )
{
	int x = -1, y = -1;
	label.setAlpha( 100 );
	wallpaper.setAlpha( 100 );
	
	if( event.type == SDL_MOUSEBUTTONDOWN )
    {
		int bot = label.getB()-4;
		for( int i = 0; i < profitVec.size(); i++ )
		{
			bot += profitVec[ i ]->getH();
		}
			
        SDL_GetMouseState( &x, &y );
		
		if( profitVec.size() < 24 )
		{
			if( x > wallpaper.getX() && x < wallpaper.getR() && y > wallpaper.getY() && y < wallpaper.getB() )
			{
				wallpaper.setAlpha( 255 );
				click.play();
				
				profitVec.push_back( new Profit( 0, 0, bot ) );
				profitVec[ profitVec.size()-1 ]->load( renderer, window );
			}
			else if( x > label.getX() && x < label.getR() && y > label.getY() && y < label.getB() )
			{
				label.setAlpha( 255 );
				click.play();

				profitVec.push_back( new Profit( 1, 0, bot ) );
				profitVec[ profitVec.size()-1 ]->load( renderer, window );
			}
		}
    }

    else if( event.type == SDL_MOUSEMOTION )
    {
        SDL_GetMouseState( &x, &y );

		if( x > wallpaper.getX() && x < wallpaper.getR() && y > wallpaper.getY() && y < wallpaper.getB() )
		{
			wallpaper.setAlpha( 255 );
		}
		else if( x > label.getX() && x < label.getR() && y > label.getY() && y < label.getB() )
		{
			label.setAlpha( 255 );
		}
    }
	
	for( int i = 0; i < profitVec.size(); i++ )
	{
		profitVec[ i ]->handle( event );
		
		if( profitVec[ i ]->isThrash() )
		{
			profitVec.erase( profitVec.begin() + i );
			int bot2 = label.getB()-4;
			for( int i = 0; i < profitVec.size(); i++ )
			{
				profitVec[ i ]->setY( bot2 );
				bot2 += profitVec[ i ]->getH();
			}
			break;
		}
	}
}

int Value::get()
{
	return type;
}
