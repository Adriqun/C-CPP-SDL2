#include "enemy.h"
#include <stdio.h>
#include <time.h>
#include <cstdlib>

Ant::Ant()
{
    number = 0;
    offset = 0;
    start = 0;
    finish = 0;
    rect = NULL;

    speed = 1;
    x = 0;
    y = 0;
}

Ant::~Ant()
{
    free();
}

void Ant::free()
{
    number = 0;
    offset = 0;
    start = 0;
    finish = 0;

    if( rect != NULL )
    {
        for( Uint8 i = 0; i < number; i++ )
        {
            if( rect[ i ] != NULL )
            {
                delete rect[ i ];
                rect[ i ] = NULL;
            }
        }

        delete [] rect;
        rect = NULL;
    }

    speed = 1;
    x = 0;
    y = 0;
    texture.free();
}

bool Ant::load( SDL_Renderer* &renderer, SDL_Window* &window, std::string path )
{
    free();
    return texture.loadFromFile( renderer, window, path );
}

void Ant::setNOSR( Uint8 nr, Uint8 ffst, Uint8 strt, Uint8 fnsh )
{
    number = nr;
    offset = ffst;
    start = strt;
    finish = fnsh;

    rect = new SDL_Rect* [ number ];
    for( Uint8 i = 0; i < number; i++ )
    {
        rect[ i ] = new SDL_Rect;
    }

    for( Uint8 i = 0; i < number; i++ )
    {
        rect[ i ]->w = texture.getWidth();
        rect[ i ]->h = texture.getHeight();
        rect[ i ]->y = 0;
        rect[ i ]->x = texture.getWidth() * i;
    }
}

void Ant::setXYS( int strtX, int strtY, int spd )
{
    x = strtX;
    y = strtY;
    speed = spd;
}

void Ant::render( SDL_Renderer* &renderer, SDL_RendererFlip flip )
{
    x -= speed;
    if( number != NULL )
    {
        texture.render( renderer, x, y, NULL, 0.0, NULL, flip );
    }
    else
    {
        offset ++;
        if( offset == finish )
        {
            offset = start;
        }

        texture.render( renderer, x, y, rect[ offset ], 0.0, NULL, flip );
    }
}

int Ant::getX()
{
    return x;
}

void Ant::setX( int newX )
{
    x = newX;
}


Enemy::Enemy()
{
    ant_one = NULL;
    ant_two = NULL;
    ant_three = NULL;
    antCounter = 0;
    x = 0;
    y = 0;
}

Enemy::~Enemy()
{
    free();
}

void Enemy::free()
{
    if( antCounter != 0 )
    {
        for( Uint8 i = 0; i < antVector.size(); i++ )
        {
            antVector[ i ]->free();
        }
    }

    if( ant_one != NULL )
    {
        ant_one->free();
        ant_one = NULL;
        delete ant_one;
    }

    if( ant_two != NULL )
    {
        ant_two->free();
        ant_two = NULL;
        delete ant_two;
    }

    if( ant_three != NULL )
    {
        ant_three->free();
        ant_three = NULL;
        delete ant_three;
    }

    antCounter = 0;
    x = 0;
    y = 0;
}

bool Enemy::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    srand( time( NULL ) );

    free();

    antCounter = 30;

    ant_one = new Ant;
    success = ant_one->load( renderer, window, "enemy/0.png" );
    ant_one->setNOSR( 13, 0, 0, 4 );

    if( success )
    {
        ant_two = new Ant;
        success = ant_two->load( renderer, window, "enemy/1.png" );
        ant_two->setNOSR( 25, 0, 0, 9 );

        if( success )
        {
            ant_three = new Ant;
            success = ant_three->load( renderer, window, "enemy/2.png" );
            ant_two->setNOSR( 18, 0, 0, 5 );
        }
    }

    if( success )
    {
        x = -100;
        int w, h;
        SDL_GetWindowSize( window, &w, &h );

        for( Uint8 i = 0; i < antCounter; i++ )
        {
            if( i < antCounter / 3 )
            {
                antVector.push_back( ant_one );
                antVector[ i ]->setXYS( x, 0, 1 );
            }
            else if( i < antCounter / 3 * 2 && i >= antCounter / 3 )
            {
                antVector.push_back( ant_two );
                antVector[ i ]->setXYS( x, 0, 2 );
            }
            else
            {
                y = rand() % w / 5;
                antVector.push_back( ant_three );
                antVector[ i ]->setXYS( x, y, 3 );
            }
        }
    }

    return success;
}

Uint8 Enemy::getNr()
{

}

SDL_Rect* Enemy::getRects()
{

}

void Enemy::render( SDL_Renderer* &renderer )
{

}
