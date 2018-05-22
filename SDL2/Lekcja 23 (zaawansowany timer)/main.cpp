#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "timer.h"

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=640;
SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
TTF_Font* font=NULL;

Texture startTexture;
Texture pauseTexture;
Texture timeTexture;

bool init()
{
    bool success=true;

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)<0)
    {
        printf("Nie udalo sie zainicjowac biblioteki! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    else
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
        {
            printf("Liniowe filtrowanie tekstru nie zostalo wlaczone! \n");
        }

        window=SDL_CreateWindow("Lekcja 23", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie udalo sie utworzyc okna! SDL Error: %s\n", SDL_GetError());
            success=false;
        }
        else
        {
            //render wykorzystuje akceleracje sprzetowa (procesor), renderowanie jest zsynchronizowane z czestotliwoscia odswiezania
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
            if(renderer==NULL)
            {
                printf("Nie udalo sie utworzyc rendera! SDL Error: %s\n", SDL_GetError());
                success=false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                if(!IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG)
                {
                    printf("Nie udalo sie zainicjowac biblioteki IMG! SDL Error: %s\n",IMG_GetError());
                    success=false;
                }

                if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
                {
                    printf("Nie udalo sie zainicjowac biblioteki Mix! SDL Error: %s\n",Mix_GetError());
                    success=false;
                }

                if(TTF_Init()<0)
                {
                    printf("Nie udalo sie zainicjowac biblioteki TTF! SDL Error: %s\n",TTF_GetError());
                    success=false;
                }
            }
        }
    }
    return success;
}
bool loadMedia()
{
    bool success=true;

    font=TTF_OpenFont( "lazy.ttf", 28 );
    if(font==NULL)
    {
        printf("Nie udalo sie wczytac lazy.ttf! SDL Error: %s\n",TTF_GetError());
        success=false;
    }
    else
    {
        SDL_Color textColor= {0,0,0,255};

        if( !startTexture.loadFromRenderedText( "Press S to Start or Stop the Timer", textColor, font, renderer ) )
        {
            printf( "Unable to render start/stop prompt texture!\n" );
            success = false;
        }

        if( !pauseTexture.loadFromRenderedText( "Press P to Pause or Unpause the Timer", textColor, font, renderer ) )
        {
            printf( "Unable to render pause/unpause prompt texture!\n" );
            success = false;
        }
    }

    return success;
}
void close()
{
    timeTexture.free();
    startTexture.free();
    pauseTexture.free();

    TTF_CloseFont( font );
    font = NULL;

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char** args)
{
    if(!init())
    {
        printf("Cos poszlo nie tak w init()! \n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Cos poszlo nie tak w loadMedia()! \n");
        }
        else
        {
            bool quit = false;
            SDL_Event e;

            SDL_Color textColor = { 0, 0, 0, 255 };
            Timer timer;
            std::stringstream timeText;

            while( !quit )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                        quit = true;

                    else if( e.type == SDL_KEYDOWN )
                    {
                        if( e.key.keysym.sym == SDLK_s )
                        {
                            if( timer.isStarted() )
                                timer.stop();

                            else
                                timer.start();
                        }
                        else if( e.key.keysym.sym == SDLK_p )
                        {
                            if( timer.isPaused() )
                                timer.unpause();

                            else
                                timer.pause();
                        }
                    }
                }
                    timeText.str( "" );
                    timeText << "Seconds since start time " << ( timer.getTicks() / 1000.f ) ;//1000.f daje nam dokladnosci i dzieli przez 1000

                    if( !timeTexture.loadFromRenderedText( timeText.str().c_str(), textColor, font, renderer ) )
                        printf( "Unable to render time texture!\n" );


                    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( renderer );

                    //Render textures
                    startTexture.render( ( SCREEN_WIDTH - startTexture.getWidth() ) / 2, 0, renderer );
                    pauseTexture.render( ( SCREEN_WIDTH - pauseTexture.getWidth() ) / 2, startTexture.getHeight(), renderer );
                    timeTexture.render( ( SCREEN_WIDTH - timeTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - timeTexture.getHeight() ) / 2, renderer );

                    SDL_RenderPresent( renderer );
            }
        }
    }
    close();

    return 0;
}
