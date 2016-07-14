#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <string>
#include "map.h"
#include "dot.h"

const int SCREEN_WIDTH=936;
const int SCREEN_HEIGHT=728;
SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;

Map block;
Dot dot;
int frame=1;

bool init()
{
    bool success=true;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0)
    {
        printf("Nie zainicjowano bibliotek! SDL Error: %s\n", SDL_GetError());
        success=false;
    }
    else
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Liniowe renderowanie tekstur jest wylaczone!\n");
        }

        window=SDL_CreateWindow("Labirynt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie utworzono okna! SDL Error: %s\n", SDL_GetError());
            success=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer==NULL)
            {
                printf("Nie utworzono rendera! SDL Error: %s\n",SDL_GetError());
                success=false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 255);

                int imgFlag=IMG_INIT_PNG;
                if(!(IMG_Init(imgFlag)&imgFlag))
                {
                    printf("Nie zainicjowano biblioteki IMG! SDL Error: %s\n",IMG_GetError());
                    success=false;
                }

                if(Mix_Init(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))<0)
                {
                    printf("Nie zainicjowano biblioteki Mix! SDL Error: %s\n", Mix_GetError());
                    success=false;
                }
            }
        }
    }
    return success;
}
bool loadMedia()
{
    if(!block.loadMedia(renderer))
        return false;

    if(!dot.loadMedia(renderer))
        return false;

    return true;
}
void present()
{
    SDL_Event e;

    for(;;)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
                SDL_Quit();
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0x4B, 0x22, 0x22, 255);

        if(frame==1)
        {
            dot.present(renderer);
            block.show(renderer, dot.rect);
        }
        else
            block.present(renderer);

        SDL_RenderPresent(renderer);
    }
}
void close()
{
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_DestroyRenderer(renderer);
    renderer=NULL;

    block.close();
    dot.close();

    IMG_Quit();
    Mix_Quit();
}

int main(int argc, char* args [])
{
    if(!init())
        printf("Cos poszlo nie tak z init()! \n");

    else
    {
        if(!loadMedia())
            printf("Cos poszlo nie tak z loadMedia()! \n");

        else
            present();
    }

    close();
    return 0;
}
