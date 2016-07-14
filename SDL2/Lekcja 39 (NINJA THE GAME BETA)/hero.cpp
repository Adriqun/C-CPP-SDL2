#include "hero.h"
#include "debugger.h"
#include <SDL_image.h>
#include <stdio.h>

Shuriken::Shuriken()
{
    width = 0;
    height = 0;

    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;

    vel = 10;
    velX = 0;
    velY = 0;
    angle = 0;
    counter = 0;
    texture = NULL;
}

Shuriken::~Shuriken()
{
    free();
}

void Shuriken::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;

        width = 0;
        height = 0;

        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = 0;
    }

    counter = 0;
    angle = 0;
    velX = 0;
    velY = 0;
}

void Shuriken::loadTexture( SDL_Renderer* &renderer, char* path )
{
    SDL_Surface* surface = IMG_Load( path );
    if( surface == NULL )
    {
        deb::loadingSurfaceError( path );
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        if( texture == NULL )
        {
            deb::createTextureFromSurfaceError( path );
        }
        else
        {
            width = surface->w;
            height = surface->h;
        }

        SDL_FreeSurface( surface );
    }
}

void Shuriken::load( SDL_Renderer* &renderer )
{
    free();
    loadTexture( renderer, "hero/shuriken.png" );
    if( texture == NULL )
    {
        deb::setTextureError();
    }
    else
    {
        rect.w = width;
        rect.h = height;
    }
}

void Shuriken::motion( SDL_Rect &dstRect, SDL_RendererFlip &_flip, const Uint8* &key )
{
    velX = 0;
    velY = 0;

    if( _flip == SDL_FLIP_NONE )
    {
        if( counter == 0 )
        {
            rect.x = dstRect.x - 22;
            rect.y = dstRect.y + 25;
            flip = SDL_FLIP_NONE;
        }
    }
    else
    {
        if( counter == 0 )
        {
            rect.x = dstRect.x + 66;
            rect.y = dstRect.y + 25;
            flip = SDL_FLIP_HORIZONTAL;
        }

    }

    if( key[ SDL_SCANCODE_SPACE ] )
    {
        if( counter == 0 )
        {
            counter = 1;
        }
    }

    if( counter > 0 && counter < 1000 / vel )
    {
        if( flip == SDL_FLIP_NONE )
        {
            velX = vel;

            angle += 25;
            if( angle >= 360 )
                angle = 0;
        }
        else
        {
            velX = vel * -1;

            angle -= 25;
            if( angle <= -360 )
                angle = 0;
        }

        counter ++;
    }
    else
    {
        counter = 0;
    }

    rect.x += velX;
    rect.y += velY;
}

void Shuriken::render( SDL_Renderer* &renderer )
{
    SDL_RenderCopyEx( renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE );
}

Uint16 Shuriken::getCounter()
{
    return counter;
}



Hero::Hero()
{
    dstRect.w = 0;
    dstRect.h = 0;
    dstRect.x = 548;
    dstRect.y = 550;

    vel = 5;
    velX = 0;
    velY = 0;
    off_set = 0;
    jumpCounter = 0;
    dimension = 0;

    srcRect = NULL;
    texture = NULL;
    flip = SDL_FLIP_NONE;
    key = SDL_GetKeyboardState( NULL );

    point.x = 0;
    point.y = 0;
}

Hero::~Hero()
{
    free();
}

void Hero::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;

        dstRect.w = 0;
        dstRect.h = 0;
        dstRect.x = 548;
        dstRect.y = 550;

        velX = 0;
        velY = 0;
        off_set = 0;
        dimension = 0;

        flip = SDL_FLIP_NONE;
        key = SDL_GetKeyboardState( NULL );
    }

    if( srcRect != NULL )
    {
        delete [] srcRect;
        srcRect = NULL;
    }

    point.x = 0;
    point.y = 0;
}

void Hero::loadTexture( SDL_Renderer* &renderer, char* path )
{
    SDL_Surface* surface = IMG_Load( path );
    if( surface == NULL )
    {
        deb::loadingSurfaceError( path );
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        if( texture == NULL )
        {
            deb::createTextureFromSurfaceError( path );
        }
        else
        {
            width = surface->w;
            height = surface->h;
        }

        SDL_FreeSurface( surface );
    }
}

void Hero::load( SDL_Renderer* &renderer )
{
    free();

    loadTexture( renderer, "hero/ninja.png" );
    if( texture == NULL )
    {
        deb::setTextureError();
    }
    else
    {
        Uint8 total = 8;

        dstRect.w = width / total;
        dstRect.h = height;

        srcRect = new SDL_Rect [ total ];
        for( Uint8 i = 0; i < total; i++ )
        {
            srcRect[ i ].w = width / total;
            srcRect[ i ].h = height;
            srcRect[ i ].y = 0;
            srcRect[ i ].x = i * ( width / total );
        }

        shuriken.load( renderer );
    }
}

void Hero::motionX()
{
    velX = 0;
    dimension = 0;
    if( key[ SDL_SCANCODE_LEFT ] )     // ruch w lewo
    {
        off_set ++;
        if( off_set > 3 )
            off_set = 0;

        if( dstRect.x > 356 )
        {
            velX = vel * -1;
            velY = -1;
        }
        else if( point.x < 500 )
        {
            dimension = 1;
            point.x += vel;
        }

        flip = SDL_FLIP_HORIZONTAL;
    }
    else if( key[ SDL_SCANCODE_RIGHT ] )    // ruch w prawo
    {
        off_set ++;
        if( off_set > 3 )
            off_set = 0;

        if( dstRect.x < 596 )
        {
            velX = vel;
            velY = -1;
        }
        else
        {
            dimension = 2;
            point.x -= vel;
        }

        flip = SDL_FLIP_NONE;
    }
    else    // gdy postac stoi
    {
        off_set = 4;
    }

    dstRect.x += velX;
}

void Hero::setX( bool m )
{
    if( m  )
    {
        dstRect.x -= velX;
    }
}

void Hero::motionY()
{
    if( key[ SDL_SCANCODE_UP ] )            // skok
    {
        if( jumpCounter == 0 )
        {
            jumpCounter = 1;
        }
    }
    // wykonywanie skoku
    if( jumpCounter > 0 && jumpCounter <= 30 )
    {
        velY = -7;
        off_set = 5;
        jumpCounter ++;
    }
    else if( jumpCounter > 30 && jumpCounter <= 60 )
    {
        velY = 7;
        off_set = 5;
        jumpCounter ++;
    }
    else
    {
        velY = 7;
    }

    if( shuriken.getCounter() > 0 && shuriken.getCounter() < 10 )
    {
        off_set = 6;
    }

    shuriken.motion( dstRect, flip, key );
    dstRect.y += velY;
}

void Hero::setY( bool m )
{
    if( m )
    {
        dstRect.y -= velY;
        jumpCounter = 0;
    }
}

void Hero::render( SDL_Renderer* &renderer )
{
    shuriken.render( renderer );
    SDL_RenderCopyEx( renderer, texture, &srcRect[ off_set ], &dstRect, 0, NULL, flip );
}

Uint8 Hero::getDimension()
{
    return dimension;
}

SDL_Point Hero::getPoint()
{
    return point;
}

SDL_Rect Hero::getRect()
{
    return dstRect;
}
