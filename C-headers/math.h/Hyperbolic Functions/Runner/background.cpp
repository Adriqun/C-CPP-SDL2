#include "background.h"
#include <stdio.h>

Control::Control()
{
    nr = 0;
    state = 0;
    counter = 0;

    x = NULL;
    y = NULL;

    texture = NULL;
    caption = NULL;
    font = NULL;

    delay = 0;
    delay_value = 0;
}

Control::~Control()
{
    free();
}

void Control::free()
{
    nr = 0;
    state = 0;
    counter = 0;

    if( x != NULL )
    {
        delete [] x;
        x = NULL;
    }

    if( y != NULL )
    {
        delete [] y;
        y = NULL;
    }

    if( font != NULL )
    {
        TTF_CloseFont( font );
        font = NULL;
    }

    if( texture != NULL )
    {
        for( Uint8 i = 0; i < nr; i++ )
        {
            texture[ i ].free();
        }

        delete [] texture;
        texture = NULL;
    }

    if( caption != NULL )
    {
        delete [] caption;
        caption = NULL;
    }

    delay = 0;
    delay_value = 0;
}

Uint8 Control::getState()
{
    return state;
}

void Control::control( SDL_Event &event )
{
    if( delay == delay_value )
    {
        if( event.key.keysym.sym == SDLK_p )
        {
            if( state == 1 )        state = 2;
            else if( state == 2 )   state = 1;
            delay = 1;
        }
        else if( event.key.keysym.sym == SDLK_b )
        {
            if( state == 1 )        state = 3;
            delay = 1;
            Mix_HaltMusic();
        }
    }
}

bool Control::load( SDL_Renderer* renderer, SDL_Window* window )
{
    bool success = true;

    free();

    font = TTF_OpenFont( "background/0.ttf", 50 );
    if( font == NULL )
    {
        printf( "Nie wczytano czcionki background/0.ttf! Error %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        nr = 4;
        delay = 1;
        delay_value = 30;

        caption = new std::string [ nr ];
        caption[ 0 ] = "3";
        caption[ 1 ] = "2";
        caption[ 2 ] = "1";
        caption[ 3 ] = "GO!";

        texture = new Texture [ nr ];
        color.r = 0xEB;
        color.g = 0xEB;
        color.b = 0xEB;
        success = texture[ 1 ].loadFromRenderedText( renderer, font, "B-back", color );
        success = texture[ 2 ].loadFromRenderedText( renderer, font, "P-pause", color );
        color.r = 0;
        color.g = 0;
        color.b = 0;
        success = texture[ 0 ].loadFromRenderedText( renderer, font, caption[ 0 ], color );
        success = texture[ 3 ].loadFromRenderedText( renderer, font, "PAUSED", color );

        int w, h;
        SDL_GetWindowSize( window, &w, &h );

        x = new Uint16 [ nr ];
        x[ 0 ] = w / 2;
        x[ 1 ] = 10;
        x[ 2 ] = 50 + texture[ 1 ].getWidth();
        x[ 3 ] = w / 2 - texture[ 3 ].getWidth() / 2;

        y = new Uint16 [ nr ];
        y[ 0 ] = h / 2;
        y[ 1 ] = 10;
        y[ 2 ] = 10;
        y[ 3 ] = h / 2 - texture[ 3 ].getHeight() / 2;
    }

    return success;
}

void Control::render( SDL_Renderer* renderer )
{
    Uint8 frameRate = 60;

    for( Uint8 i = 0; i < nr; i++ )
    {
        if( counter == frameRate * i )
        {
            texture[ 0 ].loadFromRenderedText( renderer, font, caption[ counter / frameRate ], color );
        }
    }

    if( counter < frameRate * nr )
    {
        counter ++;
        texture[ 0 ].render( renderer, x[ 0 ] - texture[ 0 ].getWidth() / 2, y[ 0 ] - texture[ 0 ].getHeight() / 2 );
        if( counter == frameRate * nr )     state = 1;
    }

    if( state == 1 )
    {
        texture[ 1 ].render( renderer, x[ 1 ], y[ 1 ] );
        texture[ 2 ].render( renderer, x[ 2 ], y[ 2 ] );
    }
    else if( state == 2 )
    {
        texture[ 3 ].render( renderer, x[ 3 ], y[ 3 ] );
    }

    if( delay < delay_value )
    {
        delay ++;
    }
}




Ruler::Ruler()
{
    x = 0;
    y = 0;
    number = 0;
    meters = 0;

    font = NULL;
}

Ruler::~Ruler()
{
    free();
}

void Ruler::free()
{
    texture.free();

    x = 0;
    y = 0;
    number = 0;
    meters = 0;

    if( font != NULL )
    {
        TTF_CloseFont( font );
        font = NULL;
    }
}

std::string Ruler::intToString( int path )
{
    std::string tmp;
    if( path < 0 )
    {
        tmp = "-";
        path = -path;
    }
    if( path > 9 )
        tmp += intToString( path / 10 );

    tmp += path % 10 + 48;

    return tmp;
}

bool Ruler::load( SDL_Renderer* renderer, SDL_Window* window )
{
    bool success = true;

    free();

    font = TTF_OpenFont( "background/0.ttf", 30 );
    if( font == NULL )
    {
        printf( "Nie wczytano czcionki background/0.ttf! Error %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        color.r = 0xEB;
        color.g = 0xEB;
        color.b = 0xEB;
        success = texture.loadFromRenderedText( renderer, font, intToString( meters ) + " meters", color );

        int w, h;
        SDL_GetWindowSize( window, &w, &h );

        number = 2;
        x = w;
        y = texture.getHeight() - 25;
    }

    return success;
}

void Ruler::render( SDL_Renderer* renderer, Uint8 value )
{
    if( value == 1 )
    {
        meters += number;
        texture.loadFromRenderedText( renderer, font, intToString( meters ) + " meters", color );
    }

    texture.render( renderer, x - texture.getWidth() - 25, y );
}



Background::Background()
{
    vel = 0;
    x = 0;
    y = 0;
}

Background::~Background()
{
    free();
}

void Background::free()
{
    texture.free();

    if( music != NULL )
    {
        Mix_FreeMusic( music );
        music = NULL;
    }

    vel = 0;
    x = 0;
    y = 0;
}

bool Background::load( SDL_Renderer* renderer, SDL_Window* window )
{
    bool success = true;

    free();

    vel = 2.5;

    success = texture.loadFromFile( renderer, window, "background/0.png" );

    music = Mix_LoadMUS( "background/0.mp3" );
    if( music == NULL )
    {
        printf( "Nie wczytano muzyki background/0.mp3! Error %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void Background::render( SDL_Renderer* renderer, Uint8 value )
{
    if( value == 1 )
    {
        x -= vel;

        if( x <= -texture.getWidth() )
        {
            x = 0;
        }

        if( Mix_PlayingMusic() == 0 )
        {
            Mix_PlayMusic( music, -1 );
        }

        if( Mix_PausedMusic() == 1 )
        {
            Mix_ResumeMusic();
        }
    }
    else
    {
        if( Mix_PausedMusic() == 0 )
        {
            Mix_PauseMusic();
        }
    }

    texture.render( renderer, x, y );
    texture.render( renderer, x + texture.getWidth(), y );
}
