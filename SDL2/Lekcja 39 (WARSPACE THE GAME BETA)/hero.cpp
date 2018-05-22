#include "hero.h"
#include <SDL_image.h>

Hero::Hero()
{
    width = 0;
    height = 0;

    vel = 1;
    velX = 0;
    velY = 0;

    counter = 0;
    how_many = 20;
    bullet = NULL;

    rect.w = 0;
    rect.h = 0;
    rect.x = 0;
    rect.y = 0;

    texture = NULL;
    key = SDL_GetKeyboardState( NULL );
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

        width = 0;
        height = 0;

        rect.w = 0;
        rect.h = 0;
        rect.x = 0;
        rect.y = 0;

        velX = 0;
        velY = 0;

        counter = 0;
        how_many = 20;

        delete [] bullet;
        bullet = NULL;

        delete &fire;
        delete &debugger;
    }
}

SDL_Texture* Hero::loadTexture( SDL_Renderer *&renderer, std::string path )
{
    free();

    SDL_Surface* surface = IMG_Load( path.c_str() );
    SDL_Texture* newTexture = NULL;

    if( surface == NULL )
    {
        debugger.loadingSurfaceError( path );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, surface );

        if( newTexture == NULL )
        {
            debugger.createTextureFromSurfaceError( path );
        }
        else
        {
            width = surface->w;
            height = surface->h;
        }

        SDL_FreeSurface( surface );
    }

    return newTexture;
}

void Hero::load( SDL_Renderer *&renderer )
{
    texture = loadTexture( renderer, "hero.png" );

    if( texture == NULL )
    {
        debugger.setTextureError();
    }
    else
    {
        fire.load( renderer );

        rect.w = width / 5;
        rect.h = height / 5;

        bullet = new Bullet [ how_many ];

        for( Uint8 i = 0; i < how_many;  i++ )
            bullet[ i ].load( renderer );
    }
}

void Hero::motion()
{
    velX = 0;
    velY = 0;

    if( key[ SDL_SCANCODE_LEFT ] && rect.x > 0 )                       velX = vel * -1;
    if( key[ SDL_SCANCODE_RIGHT ] && rect.x + rect.w < 800  )      velX = vel;

    if( key[ SDL_SCANCODE_UP ] && rect.y > 0  )                      velY = vel * -1;
    if( key[ SDL_SCANCODE_DOWN ] && rect.y + rect.h < 1000 )      velY = vel;

    if( key[ SDL_SCANCODE_SPACE ] )
    {
        counter ++;
        if( counter == how_many * 100 )
            counter = 0;

        bullet[ counter / 100 ].motion( rect, true );
    }

    for( Uint8 i = 0; i < how_many;  i++ )
        bullet[ i ].motion( rect, false );


    rect.x += velX;
    rect.y += velY;

    fire.motion( rect );
}

void Hero::render( SDL_Renderer *&renderer )
{
    motion();

    fire.render( renderer );

    for( Uint8 i = 0; i < how_many; i++ )
        bullet[ i ].render( renderer );

    SDL_RenderCopy( renderer, texture, NULL, &rect );
}
