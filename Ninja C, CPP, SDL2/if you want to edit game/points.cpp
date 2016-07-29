#include "points.h"
#include <stdio.h>
#include <fstream>

using namespace std;

string Points::intToStr( int path )
{
    string tmp;
    if( path < 0 )
    {
        tmp = "-";
        path = -path;
    }
    if( path > 9 )
        tmp += intToStr( path / 10 );

    tmp += path % 10 + 48;

    return tmp;
}

int Points::strToInt( string path )
{
    int num = 0;
    unsigned i = 0;
    bool result = true;

    if( path[ 0 ] == '-' )
    {
        result = false;
        i ++;
    }


    for( ; i < path.size(); i++ )
    {
        int buf = static_cast < int > ( path[ i ] ) - 48;

        for( unsigned j = 1; j < path.size() - i; j ++ )
            buf *= 10;

        num += buf;
    }

    return result ?num :-num;
}

// Counting sort
void Points::counting( int* tab, int n )
{
    int min = 0;
    int max = 0;

    for( int i = 0; i < n; i++ )
    {
        if( tab[ i ] < min ) min = tab[ i ];
        if( tab[ i ] > max ) max = tab[ i ];
    }

    int nr = max - min + 1;
    int bucket[ nr ];

    for( int i = 0; i < nr; i++ )
        bucket[ i ] = 0;

    for( int i = 0; i < n; i++)
        bucket[ tab[ i ] - min ]++;

    int index = 0;
    for( int i = min; i <= max; i++ )
    {
        for( int j = 0; j < bucket[ i - min ]; j++ )
        {
            tab[ index ] = i;
            index++;
        }
    }
}


Points::Points()
{
    howMany = 0;
    alpha = 0;
    x = 0;
    y = 0;
    width = 0;
}

Points::~Points()
{
    free();
}

void Points::free()
{
    texture.free();
    font.free();
    howMany = 0;
    alpha = 0;
    x = 0;
    y = 0;
    width = 0;
}


bool Points::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    if( !font.load( "menu/hulk3d2.ttf", 30 ) )
    {
        success = false;
    }
    else
    {
        color.r = 0xFF;
        color.g = 0xFF;
        color.b = 0xFF;

        if( !texture.loadFromRenderedText( renderer, font.get(), intToStr(howMany) + " scores", color ) )
        {
            success = false;
        }
        else
        {
            int w, h;
            SDL_GetWindowSize( window, &w, &h );

            width = w;
            x = w - texture.getWidth();
            y = 0;
        }
    }

    return success;
}

void Points::render( SDL_Renderer* &renderer, bool move )
{
    if( move )
        howMany ++;

    x = width - texture.getWidth();
    y = 0;

    texture.render( renderer, x, y );

    texture.loadFromRenderedText( renderer, font.get(), intToStr(howMany) + " scores", color );
}

void Points::sumUp()
{
    fstream file;
    int* array = NULL;
    string line;
    int counter = 0;

    file.open( "menu/scores.txt", ios::in | ios::out );
    if( file.bad() )
    {
        printf( "Can't find menu/scores.txt\n" );
    }
    else
    {
        while( getline( file, line ) )
        {
            counter ++;
        }

        array = new int[ counter+1 ];
        counter = 0;
    }
    file.close();


    file.open( "menu/scores.txt", ios::in | ios::out );
    if( file.bad() )
    {
        printf( "Can't find menu/scores.txt\n" );
    }
    else
    {
        while( getline( file, line ) )
        {
            array[ counter ] = strToInt( line );
            counter ++;
        }

        array[ counter ] = howMany;
        counting( array, counter+1 );
    }
    file.close();


    file.open( "menu/scores.txt", ios::in | ios::out );
    for( int i = counter; i > 0; i-- )
    {
        file << intToStr( array[ i ] ) + "\n";
    }
    file.close();

}

void Points::add( bool yes )
{
    if( yes )
    {
        howMany += 10;
    }
}


void Points::fadeIn()
{
    if( alpha < 250 )
        alpha ++;

    texture.setAlpha( alpha );
}

void Points::fadeOut()
{
    if( alpha > 0 )
        alpha -= 5;

    texture.setAlpha( alpha );
}
