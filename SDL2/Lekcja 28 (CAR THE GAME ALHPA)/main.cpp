#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "vehicles.h"
#include "map.h"

const int SCREEN_WIDTH=1000;
const int SCREEN_HEIGHT=800;

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;

Car car;
Map mapp;

bool init()
{
    bool success=true;

    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        success=false;
        printf("Nie zainicjowano biblioteki! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Nie ustawiono filtrowania liniowego!\n");
        }

        window=SDL_CreateWindow("Po nierownej powierzchni", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            success=false;
            printf("Nie utworzono okna! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer==NULL)
            {
                success=false;
                printf("Nie utworzono rendera! SDL Error: %s\n", SDL_GetError());
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 255);

                int imgFlags=IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags))
                {
                    printf("Nie zainicjowano IMG! SDL Error: %s\n", IMG_GetError());
                    success=false;
                }

                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0)
                {
                    printf("Nie zainicjowano Mix! SDL Error: %s\n", Mix_GetError());
                    success=false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    if(!car.loadMedia(renderer))
    {
        printf("Nie wczytano grafiki do obiektu car!\n");
        return false;
    }

    if(!mapp.loadMedia(renderer))
    {
        printf("Nie wczytano grafiki do obiektu map!\n");
        return false;
    }

    return true;
}

void render()
{
    SDL_Event e;

    for(;;)
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 255);
        SDL_RenderClear(renderer);

        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
                SDL_Quit();
        }

        car.render(renderer);
        mapp.render(car.dstRect, car.angle,  renderer);

        SDL_RenderPresent(renderer);
    }
}

void close()
{
    car.close();
    mapp.close();

    SDL_DestroyWindow(window);
    window=NULL;

    SDL_DestroyRenderer(renderer);
    renderer=NULL;

    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
}

int main(int argc, char* args [])
{
    if(!init())
    {
        printf("Cos nie tak w init()!\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Cos nie tak w loadMedia()!\n");
        }
        else
            render();
    }

    close();
    return 0;
}
