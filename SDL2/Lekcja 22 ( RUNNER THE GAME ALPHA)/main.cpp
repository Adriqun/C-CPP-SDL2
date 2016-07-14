#include <SDL.h>
#include <stdio.h>
#include "background.h"
#include "control.h"
#include "character.h"
#include "opponents.h"

int frame=0;
const int SCREEN_WIDTH=1000;
const int SCREEN_HEIGHT=800;
const int SCREEN_FPS = 1000/120;//aktualnie 120

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;

Menu menu;
Play play;
GameOver gameOver;

Control control;
Timer timer;
Meters meters;

Character character;
Enemy enemy;


bool init()
{
    bool success=true;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0)
    {
        printf("Inicjowanie nie powiodlo sie! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    else
    {
        window=SDL_CreateWindow("Runner",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_FULLSCREEN);
        if(window==NULL)
        {
            printf("Nie mozna utworzyc okna! SDL Error: %s\n",SDL_GetError());
            success=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                printf("Nie mozna utworzyc rendera! SDL Error: %s\n",SDL_GetError());
                success=false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
                int imgFlags=IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags))
                {
                    printf("Nie zainicjowana IMG! SDL Error: %s\n",IMG_GetError());
                    success=false;
                }
                if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
                {
                    printf("Nie zainicjowano MIX! SDL Error: %s\n",Mix_GetError());
                    success=false;
                }
                if( TTF_Init() == -1 )
                {
                    printf( "Nie zainicjowano TTF! SDL_ttf Error: %s\n", TTF_GetError() );
                    success=false;
                }
            }
        }
    }

    return success;
}
void loadMedia()
{
    menu.loadMedia(renderer);
    play.loadMedia(renderer);
    gameOver.loadMedia(renderer);
    meters.loadMedia(renderer);

    character.loadMedia(renderer);
    enemy.loadMedia(renderer);
    control.loadCursor(renderer);
}
void present()
{
    for(;;)
    {
        timer.start(renderer);
        control.keysControl(frame);
        control.mouseControl();
        ////////////////////////////////////////////////////
        if(frame==0)
        {
            menu.present(control.mouseMotion,control.mouseDown, renderer);
            frame=menu.frame;
            enemy.frame=menu.frame;
        }
        if(frame==1)
        {
            play.present(renderer,control.map.x,frame);
            character.present(control.character, renderer);
            meters.presentMeters(renderer,control.meters);
            enemy.present(control.character,control.mouseMotion,renderer,control.meters);
            frame=enemy.frame;
            gameOver.frame=enemy.frame;
        }
        if(frame==2)
        {
            gameOver.present(control.mouseMotion,control.mouseDown,renderer);
            meters.presentEndMeters(renderer);

            menu.frame=gameOver.frame;
            enemy.frame=gameOver.frame;
            control.resetMousePosition(frame);
            if(gameOver.frame==1)
                enemy.reload();
            frame=gameOver.frame;
        }
        SDL_RenderCopy(renderer,control.cursor,NULL,&control.coorCursor);
        ////////////////////////////////////////////////////
        SDL_RenderPresent(renderer);
        int ticks=timer.getTicks();
        if(ticks<SCREEN_FPS)
            SDL_Delay(SCREEN_FPS-ticks);
        }

}
void close()
{
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_DestroyRenderer(renderer);
    renderer=NULL;

    menu.close();
    play.close();
    gameOver.close();
    meters.close();
    character.close();
    enemy.close();

    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}
int main(int argc,char** argv)
{
    if(!init())
        printf("Problem z inicjacja biblioteki! \n");

    else
    {
        loadMedia();
        present();
    }
    close();
    return 0;
}
