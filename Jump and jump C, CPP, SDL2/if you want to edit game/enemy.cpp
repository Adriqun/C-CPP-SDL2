#include "enemy.h"
#include <stdio.h>
#include <cstdlib>

Enemy::Enemy()
{
    counter = 0;
    howMany = 0;
}

Enemy::~Enemy()
{
    free();
}

void Enemy::free()
{
    counter = 0;

    for( unsigned i = 0; i < enemy.size(); i ++ )
    {
        enemy[ i ]->free();
    }

    enemy.clear();
    punch.free();
}

bool Enemy::load()
{
    bool success = true;

    if( !punch.load( "enemy/punch.wav", 60 ) )
        success = false;

    return success;
}

void Enemy::faster( bool move )
{
    if( move )
    {
        for( unsigned i = 0; i < enemy.size(); i ++ )
        {
            enemy[ i ]->faster();
        }
    }
}

void Enemy::mechanics( SDL_Renderer* &renderer, SDL_Window* &window )
{
    counter ++;

    for( unsigned i = 0; i < enemy.size(); i ++ )
    {
        enemy[ i ]->mechanics();
    }

    if( counter % 400 == 0 )
    {
        howMany ++;

        int number;

        for( int i = 0; i < howMany; i ++ )
        {
            number = rand() % 3;

            if( number == 0 )
                enemy.push_back( new Monster( 8, 10, "enemy/1.png" ) );
            if( number == 1 )
                enemy.push_back( new Monster( 2, 3, "enemy/0.png" ) );
            if( number == 2 )
                enemy.push_back( new Monster( 4, 6, "enemy/2.png" ) );

            enemy[ enemy.size()-1 ]->load( renderer, window );
        }
    }

    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    for( unsigned i = 0; i < enemy.size(); i ++ )
    {
        if( enemy[ i ]->getAlpha() < 10 )
        {
            enemy.erase( enemy.begin() + i );
        }

        if( enemy[ i ]->getDirection() == 0 )
        {
            if( enemy[ i ]->getRect().x > w + 100 )
            {
                enemy.erase( enemy.begin() + i );
            }
        }
        else
        {
            if( enemy[ i ]->getRect().x < -100 )
            {
                enemy.erase( enemy.begin() + i );
            }
        }
    }
}

void Enemy::render( SDL_Renderer* &renderer )
{
    for( unsigned i = 0; i < enemy.size(); i ++ )
    {
        enemy[ i ]->render( renderer );
    }
}

bool Enemy::check( SDL_Rect a, SDL_Rect b )
{
    if( a.y + a.h <= b.y )
        return false;

    if( a.y >= b.y + b.h )
        return false;

    if( a.x + a.w <= b.x )
        return false;

    if( a.x >=  b.x + b.w )
        return false;

    return true;
}

bool Enemy::checkCollision( SDL_Rect a )
{
    for( unsigned i = 0; i < enemy.size(); i ++ )
    {
        if( enemy[ i ]->getAlpha() == 250 )
        {
            if( check( a, enemy[ i ]->getRect() ) )
            {
                enemy[ i ]->setHit();
                punch.play();
                return true;
            }
        }
    }

    return false;
}
