#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Error: %s\n", SDL_GetError() );
        success = false;
    }

    if( !( IMG_Init( IMG_INIT_PNG ) &IMG_INIT_PNG ) )
    {
        printf( "Error: %s\n", IMG_GetError() );
        success = false;
    }

    if( TTF_Init() < 0 )
    {
        printf( "Error: %s\n", TTF_GetError() );
        success = false;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "Error: %s\n", Mix_GetError() );
        success = false;
    }

    if( success == false )
    {
        perror( "- nie zainicjowano biblioteki!\n" );
    }

    return success;
}

void draw_basic()
{
    SDL_RenderPresent( renderer );
    SDL_RenderClear( renderer );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );
}

bool create_window()
{
    window = SDL_CreateWindow( "DETEKTOR KOLIZJI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );

    if( window == NULL )
    {
        printf( "Nie utworzono okna! Error: %s\n", SDL_GetError() );
        return false;
    }

    return true;
}

bool create_renderer()
{
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

    if( renderer == NULL )
    {
        printf( "Nie utworzono renderera! Error: %s\n", SDL_GetError() );
        return false;
    }
    else
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );

    return true;
}

SDL_Texture* load_tex( std::string path )
{
    SDL_Surface* surface = IMG_Load( path.c_str() );
    SDL_Texture* newTexture = NULL;

    if( surface == NULL )
    {
        printf( "Nie udalo sie wczytac %s Error %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, surface );
        if( newTexture == NULL )
        {
            printf( "Nie utworzono textury z %s Error %s\n", path.c_str(), SDL_GetError() );
        }
    }

    SDL_FreeSurface( surface );
    return newTexture;
}

SDL_Texture* champion;
SDL_Texture* block;

SDL_Rect rect_champion;
SDL_Rect rect_block;

void check_collision( SDL_Rect &a, SDL_Rect &b ) // a = postac, b = blok, p = precyzja
{
    uint8_t p = 2;

    // po lewej stronie

    if( a.x + a.w >= b.x && a.x + a.w <= b.x + p && a.y + a.h >= b.y && a.y <= b.y + b.h )
        a.x -= ( a.x + a.w - b.x );



    // po prawej stronie

    if( a.x <= b.x + b.w && a.x >= b.x + b.w - p && a.y + a.h >= b.y && a.y <= b.y + b.h )
        a.x += ( b.x + b.w - a.x );



    // od gory

    if( a.y + a.h >= b.y && a.y + a.h <= b.y + p && a.x + a.w >= b.x && a.x <= b.x + b.w )
        a.y -= ( a.y + a.h - b.y );



    // od dolu

    if( a.y <= b.y + b.h && a.y >= b.y + b.h - p && a.x + a.w >= b.x && a.x <= b.x + b.w )
        a.y += ( b.y + b.h - a.y );
}

const Uint8* key = SDL_GetKeyboardState( NULL );

void keyboard()
{

    //else if( key[ SDL_SCANCODE_S ] && rect_champion.y < 600 )
    //{
    rect_champion.y ++;
    //}
    if( key[ SDL_SCANCODE_W ] && rect_champion.y > 0 )
    {
        rect_champion.y -=2;
    }
    if( key[ SDL_SCANCODE_A ] && rect_champion.x > 0 )
    {
        rect_champion.x --;
    }
    if( key[ SDL_SCANCODE_D ] && rect_champion.y < 800 )
    {
        rect_champion.x ++;
    }

}

int main( int argc, char** argv )
{
    if( init() )
    {
        if( create_window() )
        {
            if( create_renderer() )
            {
                champion = load_tex( "rect.png" );
                block = load_tex( "rect2.png" );

                rect_champion.x = 220;
                rect_champion.y = 0;
                rect_champion.w = 40;
                rect_champion.h = 40;

                rect_block.x = 200;
                rect_block.y = 100;
                rect_block.w = 200;
                rect_block.h = 400;

                SDL_Rect rect_block2;
                rect_block2.x = 400;
                rect_block2.y = 100;
                rect_block2.w = 200;
                rect_block2.h = 400;

                SDL_Event e;
                for( ;; )
                {
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        if( e.type == SDL_QUIT )
                            return 0;
                    }

                    check_collision( rect_champion, rect_block );
                    check_collision( rect_champion, rect_block2 );
                    keyboard();
                    SDL_RenderCopy( renderer, champion, NULL, &rect_champion );
                    SDL_RenderCopy( renderer, block, NULL, &rect_block );
                    SDL_RenderCopy( renderer, block, NULL, &rect_block2 );
                    draw_basic();

                    SDL_Delay( 4 );
                }
            }
        }
    }
    return 0;
}
