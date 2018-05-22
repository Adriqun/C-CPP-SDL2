#include "wall.h"
#include <stdio.h>
#include <iostream>
Wall::Wall()
{
    rect = NULL;
    number = 0;
    counter = 0;

    dstrect.x = 0;
    dstrect.y =0;
    dstrect.w = 0;
    dstrect.h = 0;

    point.x = 0;
    point.y =0;
}

Wall::~Wall()
{
    delete [] rect;
    rect = NULL;
}

int Wall::fastAtoi( std::string &path )
{
    int num = 0, buf;
    for( uint8_t i = 0; i < path.length(); i++ )
    {
        buf = ( int ) path[ i ] - 48;
        for( uint8_t j = 1; j < path.length() - i; j++ )    buf *= 10;
        num += buf;
    }
    return num;
}

SDL_Rect Wall::setRect( std::string &path )
{
    SDL_Rect _rect;
    std::string bufor;

    for( Uint8 i = 0; i < path.length(); i++ )
    {
        if( path[ i ] == '.' )
        {
            _rect.x = fastAtoi( bufor );
            bufor.clear();

            for( Uint8 j = i + 1; j < path.length(); j++ )
            {
                if( path[ j ] == '.' )
                {
                    _rect.y = fastAtoi( bufor );
                    bufor.clear();

                    for( Uint8 k = j + 1; k < path.length(); k++ )
                    {
                        if( path[ k ] == '.' )
                        {
                           _rect.w = fastAtoi( bufor );
                            bufor.clear();

                            for( Uint8 l = k + 1; l < path.length(); l++ )
                            {
                                if( path[ l ] == '.' )
                                {
                                    _rect.h = fastAtoi( bufor );
                                    bufor.clear();
                                    break;
                                }
                                bufor += path[ l ];
                            }
                            break;
                        }
                        bufor += path[ k ];
                    }
                    break;
                }
                bufor += path[ j ];
            }
            break;
        }
        bufor += path[ i ];
    }

    return _rect;
}

void Wall::add( SDL_Renderer* &renderer, SDL_Event &e )
{
    const Uint8* key = SDL_GetKeyboardState( NULL );


    if( key[ SDL_SCANCODE_X ] )                         dstrect.w += 2;
    else if( key[ SDL_SCANCODE_Z ] && dstrect.w > 0 )   dstrect.w -= 2;

    if( key[ SDL_SCANCODE_A ] )                         dstrect.h += 2;
    else if( key[ SDL_SCANCODE_Q ] && dstrect.h > 0 )   dstrect.h -= 2;

    if( key[ SDL_SCANCODE_LEFT ] )
    {
        for( Uint16 i = 0; i < number; i++ )
            rect[ i ].x += 800;
        SDL_Delay( 200 );
        point.x -= 800;
    }

    else if( key[ SDL_SCANCODE_RIGHT ] )
    {
        for( Uint16 i = 0; i < number; i++ )
            rect[ i ].x -= 800;
        SDL_Delay( 200 );
        point.x += 800;
    }


    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_MOUSEMOTION )
            SDL_GetMouseState( &dstrect.x, &dstrect.y );

        if( e.type == SDL_MOUSEBUTTONDOWN )
        {
            SDL_GetMouseState( &dstrect.x, &dstrect.y );

            file.open( "file.txt", std::ios::out | std::ios::app );
            file << "\n" << dstrect.x + point.x << '.' << dstrect.y << '.' << dstrect.w << '.' << dstrect.h << '.';
            file.close();
            load();
            save();

            for( Uint16 i = 0; i < number; i++ )
                rect[ i ].x -= point.x;
            SDL_Delay( 200 );
        }
    }

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &dstrect );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );
}

void Wall::load()
{
    file.open( "file.txt", std::ios::in );

    if( !file.good() )
    {
        perror( "Nie wczytano file.txt! \n" );
    }
    else
    {
        std::string line;

        while( getline( file, line ) )
        {
            number ++;
        }
        rect = new SDL_Rect [ number ];
    }

    file.close();
}

void Wall::save()
{
    file.open( "file.txt", std::ios::in );

    if( !file.good() )
    {
        perror( "Nie wczytano file.txt! \n" );
    }
    else
    {
        std::string line;
        number = 0;

        while( getline( file, line ) )
        {
            rect[ number ] = setRect( line );
            number ++;
        }
    }

    file.close();
}

void Wall::render( SDL_Renderer* &renderer )
{
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

    for( Uint16 i = 0; i < number; i++ )
    {
        rect[ i ].x -= 2;
        SDL_RenderDrawRect( renderer, &rect[ i ] );
    }


    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );
}

SDL_Rect Wall::getRect( SDL_Rect _rect )
{
    for( Uint16 i = 0; i < number; i ++ )
    {
        if( _rect.x + _rect.w > rect[ i ].x && _rect.x < rect[ i ].x + rect[ i ].w )
            counter = i;
    }

    return rect[ counter ];
}


