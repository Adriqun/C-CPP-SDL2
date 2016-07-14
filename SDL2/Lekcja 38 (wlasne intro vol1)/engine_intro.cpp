#include "engine_intro.h"

Intro::Intro()
{
    texture = NULL;
    music =   NULL;
    counter =   1;

    rect.x =    -72;
    rect.y =      0;
    rect.w =   1164;
    rect.h =    720;

    fps = 1000 / 60;
    startTicks = 0;
}

void Intro::get_tex( SDL_Renderer* &renderer, std::string path )
{
    SDL_Surface* surface = IMG_Load( path.c_str() );

    if( surface == NULL )
        printf( "Nie udalo sie wczytac %s Error %s\n", path.c_str(), IMG_GetError() );
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        if( texture == NULL )
            printf( "Nie utworzono textury z %s Error %s\n", path.c_str(), SDL_GetError() );
    }

    SDL_FreeSurface( surface );
}

std::string Intro::int_to_string( int n )
{
    std::string tmp;
    if( n < 0 )
    {
        tmp = "-";
        n = -n;
    }
    if( n > 9 )
        tmp += int_to_string( n / 10 );

    tmp += n % 10 + 48;

    return tmp;
}

void Intro::start()
{
    startTicks = SDL_GetTicks();
}

void Intro::set_fps()
{
    Uint32 time = SDL_GetTicks() - startTicks;

    if( time < fps )
        SDL_Delay( fps - time );
}

void Intro::draw( SDL_Renderer* &renderer )
{
    SDL_Event e;

    music = Mix_LoadMUS( "intro/intro.mp3" );
    if( music == NULL )
    {
        printf( "Blad z intro.mp3! Error %s\n", Mix_GetError() );
    }
    else
    {
        Mix_FadeInMusic( music, 0, 1000 );
        Mix_VolumeMusic( 15 );
    }


    while( counter < 211 )
    {
        start();
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_QUIT )
            {
                Mix_FadeOutMusic( 100 );
                SDL_Quit();
            }


        if( Mix_PlayingMusic() == 0 )
            Mix_PlayMusic( music, -1 );

        name = "intro/0 (";
        name += int_to_string( counter );
        name += ").png";

        get_tex( renderer, name );

        SDL_RenderCopy( renderer, texture, NULL, &rect );

        SDL_DestroyTexture( texture );

        texture = NULL;

        SDL_RenderPresent( renderer );
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );

        counter++;
        set_fps();
    }

    Mix_FadeOutMusic( 2000 );

    Mix_FreeMusic( music );
    music = NULL;
}
