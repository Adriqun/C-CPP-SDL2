#include "menu.h"
#include <SDL_image.h>


Menu::Menu()
{
    rain = NULL;
    rain_counter = 1;

    menu = NULL;
    info = NULL;

    music =   NULL;

    pointer = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 50;
    rect.h = 50;

    alpha_counter = 0;

    state = 0;
    state_counter = 0;

    frame_counter = 0;
    key = SDL_GetKeyboardState( NULL );
}

Menu::~Menu()
{
    free();
}

void Menu::free()
{
    if( rain != NULL )
    {
        SDL_DestroyTexture( rain );
        rain = NULL;
        rain_counter = 1;
    }
    if( menu != NULL )
    {
        SDL_DestroyTexture( menu );
        menu = NULL;
    }
    if( info != NULL )
    {
        SDL_DestroyTexture( info );
        info = NULL;
    }
    if( pointer != NULL )
    {
        SDL_DestroyTexture( pointer );
        pointer = NULL;

        state = 0;
        state_counter = 0;

        frame_counter = 0;
    }
    if( music != NULL )
    {
        Mix_FreeMusic( music );
        music = NULL;
    }

    alpha_counter = 0;
}



std::string Menu::int_to_string( int n )
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

SDL_Texture* Menu::loadTexture( SDL_Renderer* &renderer, std::string path )
{
    SDL_Surface* surface = IMG_Load( path.c_str() );
    SDL_Texture* texture = NULL;

    if( surface == NULL )
        deb::loadingSurfaceError( path );
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, surface );

        if( texture == NULL )
            deb::createTextureFromSurfaceError( path );
    }

    SDL_FreeSurface( surface );

    return texture;
}

void Menu::setAlpha( SDL_Texture *&texture )
{
    if( frame_counter > 0 )
        alpha_counter = 255 - frame_counter * 3;

    else if( alpha_counter < 255 )
        alpha_counter ++;

    SDL_SetTextureAlphaMod( texture, alpha_counter );
}



void Menu::load( SDL_Renderer* &renderer )
{
    free();

    menu = loadTexture( renderer, "menu/menu.png" );
    if( menu == NULL )
    {
        deb::setTextureError();
    }
    else
    {
        info = loadTexture( renderer, "menu/info.png" );
        if( info == NULL )
        {
            deb::setTextureError();
        }
        else
        {
            pointer = loadTexture( renderer, "menu/pointer.png" );
            if( pointer == NULL )
            {
                deb::setTextureError();
            }
        }
    }

    music = Mix_LoadMUS( "menu/menu.mp3" );
    if( music == NULL )
    {
        deb::loadingMusicError( "menu/menu.mp3" );
    }
    else
    {
        Mix_VolumeMusic( 15 );
    }

    chunk = Mix_LoadWAV( "menu/click.wav" );
    if( chunk == NULL )
    {
        deb::loadingChunkError( "menu/click.wav" );
    }
}

void Menu::motion()
{
    if( state_counter == 0 && frame_counter == 0 && alpha_counter > 250 )
    {
        if( key[ SDL_SCANCODE_UP ] && state > 0 && state != 3 )
        {
            state_counter = 1;
            state --;
            Mix_PlayChannel( -1, chunk, 0 );
        }
        else if( key[ SDL_SCANCODE_DOWN ] && state < 2 )
        {
            state_counter = 1;
            state ++;
            Mix_PlayChannel( -1, chunk, 0 );
        }
        else if( key[ SDL_SCANCODE_RETURN ] )
        {
            if( state == 0 )
            {
                frame_counter = 1;
                Mix_FadeOutMusic( 1000 );
            }
            else if( state == 1 )       state = 3;
            else if( state == 2 )       SDL_Quit();
            else if( state == 3 )       state = 1;

            state_counter = 1;
            Mix_PlayChannel( -1, chunk, 0 );
        }
    }
    else if( state_counter < 5 )
        state_counter ++;
    else
        state_counter = 0;

    if( frame_counter > 0 &&  frame_counter < 85 )
    {
        frame_counter ++;
    }
}

void Menu::playingMusic()
{
    if( Mix_PlayingMusic() == 0 && frame_counter < 20 )
        Mix_PlayMusic( music, -1 );
}



void Menu::renderRain( SDL_Renderer* &renderer )
{
    rain_counter ++;

    if( rain_counter == 51 )
        rain_counter = 1;

    rain = loadTexture( renderer, "menu/0 (" + int_to_string( rain_counter ) + ").png" );

    setAlpha( rain );

    SDL_RenderCopy( renderer, rain, NULL, NULL );

    SDL_DestroyTexture( rain );
    rain = NULL;
}

void Menu::renderButtons( SDL_Renderer* &renderer )
{
    setAlpha( menu );
    setAlpha( pointer );
    setAlpha( info );

    if( state != 3 )
    {
        SDL_RenderCopy( renderer, menu, NULL, NULL );

        rect.x = 600;

        if( state == 0 )
        {
            rect.y = 280;
            SDL_RenderCopy( renderer, pointer, NULL, &rect );
        }
        else if( state == 1 )
        {
            rect.y = 410;
            SDL_RenderCopy( renderer, pointer, NULL, &rect );
        }
        else
        {
            rect.y = 530;
            SDL_RenderCopy( renderer, pointer, NULL, &rect );
        }
    }
    else
    {
        rect.x = 200;
        rect.y = 25;
        SDL_RenderCopy( renderer, pointer, NULL, &rect );
        SDL_RenderCopy( renderer, info, NULL, NULL );
    }
}

void Menu::render( SDL_Renderer* &renderer )
{
    motion();

    playingMusic();

    renderRain( renderer );

    renderButtons( renderer );
}

Uint8 Menu::getFrame()
{
   if( frame_counter == 85 )    return 1;
   else                         return 0;
}
