#include "enemy.h"
#include <algorithm>
#include <cstdlib>
#include <time.h>

Enemy::Enemy()
{
    texture = new Texture( 0 );
    rect = new SDL_Rect;
    rect->x = 0;
    rect->y = 0;
}

Enemy::~Enemy()
{
    delete texture;
    texture = NULL;

    delete rect;
    rect = NULL;
}

void Enemy::load( SDL_Renderer* &renderer, Uint16 w )
{
    texture->setTexture( renderer, "enemy/plus.png" );
    rect->w = texture->getWidth();
    rect->h = texture->getHeight();

    antic.load( renderer, w );
    buble.load( renderer, w );
    flown.load( renderer, w );
}

void Enemy::event( SDL_Event &e )
{
    for( Uint8 i = 0; i < anticVector.size(); i ++ )
    {
        if( anticVector[ i ].event( e ) )
            break;
    }

    for( Uint8 i = 0; i < bubleVector.size(); i ++ )
    {
        if( bubleVector[ i ].event( e ) )
            break;
    }

    for( Uint8 i = 0; i < flownVector.size(); i ++ )
    {
        if( flownVector[ i ].event( e ) )
            break;
    }

    if( e.type == SDL_MOUSEBUTTONDOWN )
    {
        int x, y;
        SDL_GetMouseState( &x, &y );
        if( x > rect->x && x < rect->x + rect->w && y > rect->y && y < rect->y + rect->h )
        {
            Uint8 number = rand()%3 + 1;
            if( number == 1 )
            {
                anticVector.push_back( antic );
            }
            else if( number == 2 )
            {
                bubleVector.push_back( buble );
            }
            else
            {
                flownVector.push_back( flown );
            }
        }
    }
}

void Enemy::motion( Uint16 w, Uint16 h )
{
    for( Uint8 i = 0; i < anticVector.size(); i ++ )
    {
        if( anticVector[ i ].isDead() > 0 )
        {
            anticVector.erase( anticVector.begin() + i );
            break;
        }
    }

    for( Uint8 i = 0; i < bubleVector.size(); i ++ )
    {
        if( bubleVector[ i ].isDead() > 0 )
        {
            bubleVector.erase( bubleVector.begin() + i );
            break;
        }
    }

    for( Uint8 i = 0; i < flownVector.size(); i ++ )
    {
        if( flownVector[ i ].isDead() > 0 )
        {
            flownVector.erase( flownVector.begin() + i );
            break;
        }
    }

    for( Uint8 i = 0; i < anticVector.size(); i ++ )
    {
        anticVector[ i ].motion( w, h );
    }

    for( Uint8 i = 0; i < bubleVector.size(); i ++ )
    {
        bubleVector[ i ].motion( w, h );
    }

    for( Uint8 i = 0; i < flownVector.size(); i ++ )
    {
        flownVector[ i ].motion( w, h );
    }
}

void Enemy::render( SDL_Renderer* &renderer )
{
    for( Uint8 i = 0; i < anticVector.size(); i ++ )
    {
        anticVector[ i ].render( renderer );
    }

    for( Uint8 i = 0; i < bubleVector.size(); i ++ )
    {
        bubleVector[ i ].render( renderer );
    }

    for( Uint8 i = 0; i < flownVector.size(); i ++ )
    {
        flownVector[ i ].render( renderer );
    }

    texture->render( renderer, rect );
}
