#include "antic.h"

Antic::Antic()
{
    posX = 0;
    posY = 0;
    vel = 0.3;
    slow = 7;
    hit = 7 * slow;

    rect = NULL;
    rect = new SDL_Rect;

    rect->x = 0;
    rect->y = 0;
    rect->w = 0;
    rect->h = 0;

    lifebar = new Lifebar;
    texture = new Texture( 25 );
    random = new Random;
}

Antic::~Antic()
{
    delete lifebar;
    lifebar = NULL;

    delete texture;
    texture = NULL;

    delete random;
    random = NULL;

    delete rect;
    rect = NULL;
}

void Antic::load( SDL_Renderer* &renderer, Uint16 w )
{
    texture->setTexture( renderer, "enemy/1.png" );
    texture->setSlow( slow );
    rect->w = texture->getWidth() * 2;
    rect->h = texture->getHeight() * 2;

    lifebar->setAlpha( 0xFF );
    lifebar->setColor( 0xFF, 0x00, 0x00 );
    lifebar->setSizes( 5, rect->w, 15 );
    lifebar->setXY( rect->x, rect->y - 10 );

    random->randomX( 1, ( w - rect->w ) );
    random->randomY( -50, -100 );
    posX = random->getX();
    posY = random->getY();
    rect->x = posX;
    rect->y = posY;
}

bool Antic::event( SDL_Event &e )
{
    bool success = false;
    x = -100;
    y = -100;

    if( e.type == SDL_MOUSEBUTTONDOWN ) // SDL_MOUSEBUTTONDOWN SDL_FINGERDOWN
    {
        // x = e.tfinger.x * w;
        // y = e.tfinger.y * h;
        SDL_GetMouseState( &x, &y );

        if( x > rect->x && x < rect->x + rect->w && y > rect->y && y < rect->y + rect->h )
        {
            success = true;
            if( lifebar->getLife() > 0 )
            {
                lifebar->subtraction( 1 );
            }
            if( lifebar->isDead() && hit == 7 * slow )
            {
                hit = 0;
            }
            else if( hit == 7 * slow )
            {
                hit = 8 * slow;
            }
            else if( hit >= 24 * slow )
            {
                hit = 25 * slow;
            }
        }
    }

    return success;
}

void Antic::motion( Uint16 w, Uint16 h )
{
    if( hit >= 19 * slow && hit < 24 * slow )
    {
        texture->setOffset( hit );
        hit ++;
    }
    else if( hit >= 24 * slow )
    {
        texture->setOffset( hit );
    }
    else if( hit == 7 * slow )
    {
        texture->runOffset( 4, 7 );
    }
    else if( hit > 7 * slow && hit < 19 * slow )
    {
        texture->setOffset( hit + 5 * slow );
        hit ++;
        if( hit == 10 * slow )
            hit = 7 * slow;
    }
    else if( hit < 7 * slow )
    {
        texture->setOffset( hit + 13 * slow );
        hit ++;
    }

    if( rect->x < random->getX() )
    {
        posX += vel;
        texture->setFlip( SDL_FLIP_NONE );
    }
    else if( rect->x > random->getX() )
    {
        posX -= vel;
        texture->setFlip( SDL_FLIP_HORIZONTAL );
    }

    if( rect->x <= random->getX() + 5 && rect->x > random->getX() - 5 )
    {
        random->randomX( 1, ( w - rect->w ) );
    }

    posY += vel;
    rect->x = posX;
    rect->y = posY;

    if( hit == 6 * slow )
    {
        lifebar->setSizes( 1, rect->w / 2, 15 );
        hit = 19 * slow;
    }

    if( rect->y > h )
    {
        hit = 25.1 * slow;
    }
}

void Antic::render( SDL_Renderer* &renderer )
{
    lifebar->setXY( rect->x, rect->y - 10 );
    lifebar->render( renderer );
    texture->render( renderer, rect );
}

Uint8 Antic::isDead()
{
    if( hit == 25 * slow )  return 1;
    else if( hit > 25 * slow )  return 2;
    return 0;
}

void Antic::setVel( float v )
{
    vel = v;
}
