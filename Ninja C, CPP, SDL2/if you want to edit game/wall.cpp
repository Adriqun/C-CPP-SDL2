#include "wall.h"
#include <stdio.h>

string Wall::intToStr( int path )
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

int Wall::strToInt( string path )
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



Wall::Wall()
{
    nr = 0;
    x = NULL;
    y = NULL;
    texture = NULL;

    myx = 0;
    alpha = 0;
}

Wall::~Wall()
{
    free();
}

void Wall::free()
{
    file.close();

    if( x != NULL )
    {
        delete [] x;
        x = NULL;
    }

    if( y != NULL )
    {
        delete [] y;
        y = NULL;
    }

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

    myx = 0;
    music.free();
    alpha = 0;
}



bool Wall::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    // We know how many types of block we have, but we don't know how many this one type block we have
    nr = 15;

    x = new vector <int> [ nr-1 ];
    if( x == NULL )
    {
        printf( "Not created array of vector <int>\n" );
        success = false;
    }

    y = new vector <int> [ nr-1 ];
    if( y == NULL )
    {
        printf( "Not created array of vector <int>\n" );
        success = false;
    }

    texture = new Texture[ nr ];
    if( texture == NULL )
    {
        printf( "Not created array of texture\n" );
        success = false;
    }
    else
    {
        for( int i = 0; i < nr; i ++ )
        {
            texture[ i ].loadFromFile( renderer, window, "wall/" + intToStr( i ) + ".png" );
        }
    }

    file.open( "wall/chart.txt" );
    if( file.bad() )
    {
        success = false;
    }
    else
    {
        int a; // nr in array
        int b; // pos x
        int c; // pos y

        string line;
        while( getline( file, line ) )
        {
            string number = "";
            for( int i = 0; ; i ++ )
            {
                if( line[ i ] == '.' )
                {
                    a = strToInt( number );
                    number = "";
                    i ++;
                    for( int j = i; ; j ++ )
                    {
                        if( line[ j ] == '.' )
                        {
                            b = strToInt( number );
                            number = "";
                            j ++;

                            for( unsigned k = j; k < line.size(); k ++ )
                            {
                                number += line[ k ];
                            }

                            c = strToInt( number );
                            break;
                        }

                        number += line[ j ];
                    }

                    break;
                }

                number += line[ i ];
            }

            // printf( "%d %d %d\n", a, b, c );
            x[ a ].push_back( b );
            y[ a ].push_back( c );
        }
    }

    file.close();


    if( !music.load( "wall/Rayman Legends OST - Babel Tower.mp3", 70 ) )
    {
        success = false;
    }

    return success;
}

void Wall::render( SDL_Renderer* &renderer, bool move )
{
    if( move )
        myx -= 2;
    if( myx < -texture[ nr-1 ].getWidth() )
        myx = 0;

    texture[ nr-1 ].render( renderer, myx, 0 );
    texture[ nr-1 ].render( renderer, myx + texture[ nr-1 ].getWidth(), 0 );

    for( int i = 0; i < nr-1; i ++ )
    {
        for( unsigned j = 0; j < x[ i ].size(); j ++ )
        {
            texture[ i ].render( renderer, x[ i ][ j ], y[ i ][ j ] );

            if( move )
                x[ i ][ j ] -= 5;
        }
    }
}

float Wall::getX()
{
    return myx;
}


using namespace std;

bool Wall::check( SDL_Rect &a, SDL_Rect &b, Uint8 type )
{
    // printf( "->%d %d %d %d\n", a.x, a.y, a.w, a.h );
    // printf( "------->%d %d %d %d\n", b.x, b.y, b.w, b.h );

    // Customize height, We're talking about grass ...
    static Uint8 c = 0;

    if( type == 1 || type == 3 || type == 5 )   c = 0;
    else                                        c = 26;


    if( a.y + a.h <= b.y + c )
        return false;

    if( a.y >= b.y + b.h - c )
        return false;

    if( a.x + a.w <= b.x )
        return false;

    if( a.x >=  b.x + b.w )
        return false;

    return true;
}

int Wall::checkCollision( SDL_Rect a )
{
    SDL_Rect block;

    for( int i = 0; i < nr-1; i ++ )
    {
        for( unsigned j = 0; j < x[ i ].size(); j ++ )
        {
            block.w = texture[ i ].getWidth();
            block.h = texture[ i ].getHeight();
            block.x = x[ i ][ j ];
            block.y = y[ i ][ j ];

            if( check( a, block, i ) )
            {
                return i;
            }
        }
    }

    return -1;
}




void Wall::setMousePosition( int &type, SDL_Point &point )
{
    if( type > 2 )
    {
        for( int i = 1; i < 10; i++ )
        {
            if( point.x < i * 128 )
            {
                point.x = ( i - 1 ) * 128;
                break;
            }
        }

        for( int i = 1; i < 10; i++ )
        {
            if( point.y < i * 128 )
            {
                point.y = ( i - 1 ) * 128;
                break;
            }
        }
    }
}

void Wall::addToFile( int &type, int px, int py, int ax )
{
    file.open( "wall/chart.txt", ios::app );
    if( file.good() )
    {

        string newLine = intToStr( type );
        newLine += '.' + intToStr( px ) + '.' + intToStr( py ) + "\n";

        file << newLine;
    }
    file.close();

    // DELETE OLD
    if( x != NULL )
    {
        delete [] x;
        x = NULL;
    }

    if( y != NULL )
    {
        delete [] y;
        y = NULL;
    }

    // CREATE NEW
    x = new vector <int> [ nr-1 ];
    if( x == NULL )
    {
        printf( "Not created array of vector <int>\n" );
    }

    y = new vector <int> [ nr-1 ];
    if( y == NULL )
    {
        printf( "Not created array of vector <int>\n" );
    }

    // Loading ...
    file.open( "wall/chart.txt" );
    if( file.good() )
    {
        int a; // nr in array
        int b; // pos x
        int c; // pos y

        string line;
        while( getline( file, line ) )
        {
            string number = "";
            for( int i = 0; ; i ++ )
            {
                if( line[ i ] == '.' )
                {
                    a = strToInt( number );
                    number = "";
                    i ++;
                    for( int j = i; ; j ++ )
                    {
                        if( line[ j ] == '.' )
                        {
                            b = strToInt( number );
                            number = "";
                            j ++;

                            for( unsigned k = j; k < line.size(); k ++ )
                            {
                                number += line[ k ];
                            }

                            c = strToInt( number );
                            break;
                        }

                        number += line[ j ];
                    }

                    break;
                }

                number += line[ i ];
            }

            // printf( "%d %d %d\n", a, b, c );
            x[ a ].push_back( b );
            y[ a ].push_back( c );
        }
    }
    file.close();

    for( int i = 0; i < nr-1; i ++ )
    {
        for( unsigned j = 0; j < x[ i ].size(); j ++ )
        {
            x[ i ][ j ] = -ax + x[ i ][ j ];
        }
    }
}

void Wall::addBlock( SDL_Renderer* &renderer, SDL_Event &event )
{
    static SDL_Point point;
    static int type = 0;
    static const Uint8* key = SDL_GetKeyboardState( NULL );
    static Uint8 counter = 0;
    static int actualX = 0;

    if( counter < 10 )
        counter ++;
    else
    {
        if( key[ SDL_SCANCODE_W ] )
        {
            type ++;
            if( type > nr-2 )
                type = 0;
            counter = 0;
        }
        else if( key[ SDL_SCANCODE_S ] )
        {
            type --;
            if( type < 0 )
                type = nr-2;
            counter = 0;
        }

        int liveX = 0;

        if( key[ SDL_SCANCODE_D ] )
        {
            liveX = -texture[ nr-1 ].getWidth();
            counter = 0;
        }
        else if( key[ SDL_SCANCODE_A ] )
        {
            liveX = texture[ nr-1 ].getWidth();
            counter = 0;
        }

        actualX = -liveX + actualX;
        for( int i = 0; i < nr-1; i ++ )
        {
            for( unsigned j = 0; j < x[ i ].size(); j ++ )
            {
                x[ i ][ j ] = liveX + x[ i ][ j ];
            }
        }
    }

    if( event.type == SDL_MOUSEMOTION )
    {
        SDL_GetMouseState( &point.x, &point.y );
        setMousePosition( type, point );
    }
    else if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        SDL_GetMouseState( &point.x, &point.y );
        setMousePosition( type, point );

        if( counter == 10 )
        {
            addToFile( type, point.x + actualX, point.y, actualX );
            counter = 0;

            printf( "Actual x = %d\n", actualX );
            printf( "New block[ %d ] x=%d y=%d\n", type, point.x + actualX, point.y );
        }
    }

    texture[ type ].render( renderer, point.x, point.y );
}

void Wall::renderLive( SDL_Renderer* &renderer )
{
    texture[ nr-1 ].render( renderer, 0, 0 );

    for( int i = 0; i < nr-1; i ++ )
    {
        for( unsigned j = 0; j < x[ i ].size(); j ++ )
        {
            texture[ i ].render( renderer, x[ i ][ j ], y[ i ][ j ] );
        }
    }
}

void Wall::fadeIn()
{
    if( alpha < 250 )
        alpha ++;

    for( int i = 0; i < nr; i ++ )
    {
        texture[ i ].setAlpha( alpha );
    }
}

void Wall::fadeOut()
{
    if( alpha > 0 )
        alpha -= 5;

    for( int i = 0; i < nr; i ++ )
    {
        texture[ i ].setAlpha( alpha );
    }
}

void Wall::play()
{
    music.play();
}

void Wall::pause()
{
    if( Mix_PausedMusic() == 0 )
        Mix_PauseMusic();
}
