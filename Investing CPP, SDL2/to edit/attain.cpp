#include "attain.h"
#include <stdio.h>


string Attain::intToStr( unsigned long long n )
{
     string tmp;
	 
     if( n > 9 )
	 {
		 tmp += intToStr( n / 10 );
	 }
	 
     tmp += n % 10 + 48;
	 
     return tmp;
}

Attain::Attain()
{
    // empty
}

Attain::~Attain()
{
    free();
}

void Attain::free()
{
	font.free();
	
	name.free();
	result.free();
}

bool Attain::load( SDL_Renderer* &renderer, int goal_height )
{
    bool success = true;

    free();

    if( !font.load( "data/Chunkfive Ex.ttf", 30 ) )
    {
        success = false;
    }
    else
    {
		SDL_Color color = { 0x58, 0x58, 0x58 };
		if( !name.loadFromRenderedText( renderer, font.get(), "attain ~  ", color ) )
		{
			success = false;
		}
		else
		{
			name.getX() = 10;
			name.getY() = goal_height;
		}
		
		color.r = 0xe8;
		color.g = 0x68;
		color.b = 0x50;
		if( !result.loadFromRenderedText( renderer, font.get(), "never", color ) )
		{
			success = false;
		}
		else
		{
			result.getX() = name.getR();
			result.getY() = goal_height;
		}
		
    }

	//date.setTime();
	
	//printf( "cos3\n" );

    return success;
}

void Attain::render( SDL_Renderer* &renderer, int screen_width )
{
    name.render( renderer );
    result.render( renderer );

    SDL_SetRenderDrawColor( renderer, 0x58, 0x74, 0x98, 0xFF );
    SDL_RenderDrawLine( renderer, 0, name.getB(), screen_width, name.getB() );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

int Attain::getB()
{
	return name.getB();
}

void Attain::setAttain( vector <Tax*> mother, unsigned long long target, SDL_Renderer* &renderer )
{
	/* calendar
	 * 1 - day;
	 * 2 - week
	 * 3 - mounth
	 * 4 - year
	*/
	
	/*
	 * 1 - PLN
	 * 2 - EUR
	 * 3 - USD
	 * 4 - BGP
	*/
	
	int week = 7;
	int mounth = 30;
	int year = 365;

	for( int i = 0; i < mother.size(); i++ )
	{
		if( mother[ i ]->getCalendar() == 2 )
		{
			mother[ i ]->setCalendar( week );
		}
		else if( mother[ i ]->getCalendar() == 3 )
		{
			mother[ i ]->setCalendar( mounth );
		}
		else if( mother[ i ]->getCalendar() == 4 )
		{
			mother[ i ]->setCalendar( year );
		}
	}
	
	// printf( "%d\n", mother.size() );
	
	int TIME = 0;	// in days
	long long positive = 0;
	bool success = true;
	
	while( true )
	{
		TIME ++;
		
		for( int i = 0; i < mother.size(); i++ )
		{
			if(  TIME % mother[ i ]->getCalendar() == 0 )
			{
				if( mother[ i ]->type == 1 )
					positive += mother[ i ]->getCost();
				else
					positive -= mother[ i ]->getCost();
			}
		}
		
		
		
		if( TIME > 36500 )
		{
			success = false;
			break;
		}
		else if( positive >= target )
		{
			break;
		}
	}
	
	// printf( "%d %d %d\n", positive, target, TIME );
	if( !success || positive < static_cast <long long> (target) )
	{
		SDL_Color color = { 0x58, 0x58, 0x58 };
		result.loadFromRenderedText( renderer, font.get(), "never", color );
	}
	else if( success )
	{
		time_t now = time( 0 );
		int myday = localtime( &now )->tm_mday;
		int mymounth = localtime( &now )->tm_mon;
		int myyear = localtime( &now )->tm_year;
		int mon[ 12 ] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		// printf( "%d\n", myyear );
		
		for( int i = 0; i < TIME-1; i++ )
		{
			myday++;
			if( myday > mon[ mymounth ] )
			{
				myday = 1;
				mymounth ++;
			}
			
			if( mymounth > 11 )
			{
				mymounth = 0;
				myyear ++;
			}
		}
		
		string res = intToStr( myday );
		res += '.';
		res += intToStr( mymounth+1 );
		res += '.';
		res += intToStr( myyear+1900 );
	
		SDL_Color color = { 0x58, 0x58, 0x58 };
		result.loadFromRenderedText( renderer, font.get(), res, color );
	}
	
	result.getX() = name.getR();
	result.getY() = 92;
}

/*
void Attain::setAttain( vector <Send*> mother, unsigned long long target, SDL_Renderer* &renderer )
{
	 calendar
	 * 1 - day;
	 * 2 - week
	 * 3 - mounth
	 * 4 - year
	
	
	
	 * 1 - PLN
	 * 2 - EUR
	 * 3 - USD
	 * 4 - BGP
	
	
	int week = 7;
	int mounth = 30;
	int year = 365;

	for( int i = 0; i < mother.size(); i++ )
	{
		if( mother[ i ]->calendar == 2 )
		{
			mother[ i ]->calendar = week;
		}
		else if( mother[ i ]->calendar == 3 )
		{
			mother[ i ]->calendar = mounth;
		}
		else if( mother[ i ]->calendar == 4 )
		{
			mother[ i ]->calendar = year;
		}
	}
	
	
	
	int TIME = 1;	// in days
	long long bug = 0;
	bool success = true;
	
	while( true )
	{
		for( int i = 0; i < mother.size(); i++ )
		{
			if(  TIME % mother[ i ]->calendar == 0 )
			{
				bug += mother[ i ]->cost;
				//printf( "%d", mother[ i ]->cost );
			}
		}
		
		TIME ++;
		
		if( TIME > 36500 )
		{
			success = false;
			break;
		}
		else if( bug >= target )
		{
			break;
		}
	}
	
	if( success )
	{
		SDL_Color color = { 0x58, 0x58, 0x58 };
		if( !result.loadFromRenderedText( renderer, font.get(), intToStr( bug ), color ) )
		{
			success = false;
		}
		else
		{
			result.getX() = label.getR();
			result.getY() = 92;
		}
	}
}
*/