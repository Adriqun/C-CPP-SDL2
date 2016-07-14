#include "hero_component.h"
#include <SDL_image.h>

Bullet::Bullet()
{
    width = 0;
    height = 0;
    vel = 3;
    counter = 0;

    texture = NULL;

    rect.w = 0;
    rect.h = 0;
    rect.x = -1000;
    rect.y = -1000;
}

Bullet::~Bullet()
{
    free();
}

void Bullet::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;

        width = 0;
        height = 0;

        counter = 0;

        rect.w = 0;
        rect.h = 0;
        rect.x = -1000;
        rect.y = -1000;
    }
}

SDL_Texture* Bullet::loadTexture( SDL_Renderer *&renderer, std::string path )
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

void Bullet::load( SDL_Renderer *&renderer )
{
    texture = loadTexture( renderer, "bullet.png" );

    if( texture == NULL )
    {
        debugger.setTextureError();
    }
    else
    {
        //dzielimy przez jakas liczbe aby uzyskac mniejsza teksture ;)
        rect.w = width / 7;
        rect.h = height / 7;
    }
}

void Bullet::motion( SDL_Rect _rect, bool blockade = false )
{
    if( blockade == true && counter == 0 )
    {
        counter = 1;

        rect.x = _rect.x + _rect.w / 2 - rect.w / 2;
        rect.y = _rect.y + _rect.h / 2 - rect.h / 2;
    }

    if( counter > 0 && counter < 700 )
    {
        rect.y --;
        counter ++;
    }

    else
    {
        counter = 0;
        rect.x = -1000;
        rect.y = -1000;
    }
}

void Bullet::render( SDL_Renderer *&renderer )
{
    SDL_RenderCopy( renderer, texture, NULL, &rect );
}







Fire::Fire()
{
    width = 0;
    height = 0;

    off_set = 11;
    how_many = 0;
    interlude = false;

    texture = NULL;
    srcrect = NULL;

    dstrect.w = 0;
    dstrect.h = 0;
    dstrect.x = 0;
    dstrect.y = 0;
}

Fire::~Fire()
{
    free();
}

void Fire::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;

        delete [] srcrect;
        srcrect = NULL;

        width = 0;
        height = 0;

        off_set = 11;
        how_many = 0;
        interlude = false;

        dstrect.w = 0;
        dstrect.h = 0;
        dstrect.x = 0;
        dstrect.y = 0;
    }
}

SDL_Texture* Fire::loadTexture( SDL_Renderer *&renderer, std::string path )
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

void Fire::load( SDL_Renderer *&renderer )
{
    texture = loadTexture( renderer, "fire.png" );

    if( texture == NULL )
    {
        debugger.setTextureError();
    }
    else
    {
        dstrect.w = width / 29;
        dstrect.h = height;

        how_many = 29;

        srcrect = new SDL_Rect [ how_many ];
        for( Uint8 i = 0; i < how_many; i++ )
        {
            srcrect[ i ].w = width / 29;
            srcrect[ i ].h = height;
            srcrect[ i ].x = width / 29 * i;
            srcrect[ i ].y = 0;
        }
    }
}

void Fire::motion( SDL_Rect &_rect )
{
    dstrect.x = _rect.x + ( _rect.w / 2 ) - ( dstrect.w / 2 );
    dstrect.y = _rect.y +  _rect.h ;

    if( interlude == false )
    {
        off_set ++;
    }
    else
    {
        off_set --;
    }

    if( off_set == 20 )
        interlude = true;

    if( off_set == 11 )
        interlude = false;
}

void Fire::render( SDL_Renderer *&renderer )
{
    SDL_RenderCopy( renderer, texture, &srcrect[ off_set ], &dstrect );
}

