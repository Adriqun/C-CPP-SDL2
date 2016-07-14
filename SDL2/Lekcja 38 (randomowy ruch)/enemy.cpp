#include "enemy.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
using namespace std;

Enemy::Enemy()
{
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;

    angle = 0;
    srand( time( NULL ) );

    width = rand() % 200;
    height = rand() % 200;

    posX = ( rand() % ( 799 - width ) ) + 1;
    posY = ( rand() % ( 799 - height ) ) + 1;

    angleC = rand() % 360;
}

void Enemy::load( SDL_Renderer *&renderer )
{
    SDL_Surface *surface = IMG_Load( "surface.png" );
    texture = SDL_CreateTextureFromSurface( renderer, surface );
    SDL_FreeSurface( surface );
}

void Enemy::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( texture, red, green, blue );
}

void Enemy::render( SDL_Renderer *&renderer )
{
    if( rect.x < posX )
        rect.x ++;
    else if( rect.x > posX )
        rect.x --;
    else
        posX = ( rand() % ( 799 - width ) ) + 1;


    if( rect.y < posY )
        rect.y ++;
    else if( rect.y > posY )
        rect.y --;
    else
        posY = ( rand() % ( 799 - height ) ) + 1;


    if( rect.w < width )
        rect.w ++;
    else if( rect.w > width )
        rect.w --;
    else
        width = rand() % 200;

    if( rect.h < height )
        rect.h ++;
    else if( rect.h > height )
        rect.h --;
    else
        height = rand() % 200;

    if( angle < angleC )
        angle ++;
    else if( angle > angleC )
        angle --;
    else
        angleC = rand() % 360;

    SDL_RenderCopyEx( renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE );
}
