#include "value.h"

void Value::free()
{
	label.free();
	wallpaper.free();

	click.free();
}

bool Value::load( SDL_Renderer* &renderer, SDL_Window* &window, int goal_height )
{
    bool success = true;
	
    free();
	
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
	old_nr = 0;

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
				
				profitVec.push_back( new Profit( 0, bot ) );
				profitVec[ profitVec.size()-1 ]->load( renderer, window );
			}
			else if( x > label.getX() && x < label.getR() && y > label.getY() && y < label.getB() )
			{
				label.setAlpha( 255 );
				click.play();

				profitVec.push_back( new Profit( 1, bot ) );
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

vector <Tax*> Value::get()
{
	vector <Tax*> mother;
	for( int i = 0; i < profitVec.size(); i ++ )
	{
		mother.push_back( new Tax() );
		mother[ i ]->setCalendar( profitVec[ i ]->getCalendar() );
		mother[ i ]->setCurrency( profitVec[ i ]->getCurrency() );
		
		int type;
		mother[ i ]->setCost( profitVec[ i ]->getCost( type ) );
		mother[ i ]->type = type;
		// printf( "%d %d %d\n", profitVec[ i ]->getCalendar(), profitVec[ i ]->getCurrency(), profitVec[ i ]->getCost() );
	}
	
	return mother;
}

/*int** Value::get()
{
	int** mother = NULL;
	if( old_nr != profitVec.size() )
	{
		old_nr = profitVec.size();
		
		mother = new int* [ old_nr ];
		for( int i = 0; i < old_nr; i ++ )
		{
			mother[ i ] = new int [ 2 ]; // calendar, currency
		}
		
		for( int i = 0; i < old_nr; i ++ )
		{
			mother[ i ][ 0 ] = profitVec[ i ]->getCalendar();
			mother[ i ][ 1 ] = profitVec[ i ]->getCurrency();
			mother[ i ][ 2 ] = profitVec[ i ]->getCost();
		}
		
		return mother;
	}
	
	return NULL;
}
*/