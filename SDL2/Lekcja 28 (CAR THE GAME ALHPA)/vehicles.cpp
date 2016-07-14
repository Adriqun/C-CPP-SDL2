#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>
#include <string>

#include "vehicles.h"

Car::Car()
{
    nr=0;
    texture=NULL;
    srcRect=NULL;
    key=SDL_GetKeyboardState(NULL);
}

Car::~Car()
{
    texture=NULL;
    srcRect=NULL;
}

SDL_Texture* Car::loadTexture(std::string path, SDL_Renderer* &renderer)
{
    SDL_Texture* newTexture=NULL;
    SDL_Surface* surface=IMG_Load(path.c_str());

    if(surface==NULL)
    {
        printf("Nie wczytano %s SDL Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        newTexture=SDL_CreateTextureFromSurface(renderer, surface);
        if(newTexture==NULL)
        {
            printf("Nie utworzono tekstury z %s SDL Error: %s\n", path.c_str(), IMG_GetError());
        }
        else
        {
            dstRect.w=surface->w/4;
            dstRect.h=surface->h;
        }
        SDL_FreeSurface(surface);
    }

    return newTexture;
}

bool Car::loadMedia(SDL_Renderer* &renderer)
{
    bool success=true;

    texture=loadTexture("car.png", renderer);
    if(texture==NULL)
    {
        printf("Blad przy wczytywaniu tekstury car.png! SDL Error: %s\n", SDL_GetError());
        success=false;
    }
    else
    {
        srcRect=new SDL_Rect [4];
        for(int i=0; i<4; i++)
        {
            srcRect[i].x=dstRect.w*i;
            srcRect[i].y=0;
            srcRect[i].w=dstRect.w;
            srcRect[i].h=dstRect.h;
        }
        dstRect.x=-1;
        dstRect.y=700;
    }

    return success;
}

void Car::render(SDL_Renderer* &renderer)
{
    if(key[SDL_SCANCODE_D])
    {
        dstRect.x+=5;
        nr++;
    }

    if(key[SDL_SCANCODE_A])
    {
        dstRect.x-=5;
        nr++;
    }
    if(nr>=3)
            nr=0;

    SDL_RenderCopyEx(renderer, texture, &srcRect[nr], &dstRect, angle, NULL, SDL_FLIP_NONE);
}

void Car::close()
{
    SDL_DestroyTexture(texture);
    delete [] srcRect;
}
