#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "dot.h"

Dot::Dot()
{
    doot=NULL;
    key=SDL_GetKeyboardState(NULL);
    WIDTH=0;
    HEIGHT=0;
    speed=3;
}
Dot::~Dot()
{
    doot=NULL;
}

SDL_Texture* Dot::loadTexture(std::string path, SDL_Renderer* &renderer)
{
    SDL_Texture* newTexture=NULL;

    SDL_Surface* surface=IMG_Load(path.c_str());
    if(surface==NULL)
    {
        printf("Nie udalo sie wczytac %s, SDL_Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        newTexture=SDL_CreateTextureFromSurface(renderer,surface);
        if(newTexture==NULL)
        {
            printf("Nie utworzono tekstury z %s, SDL Error: %s\n", path.c_str(), IMG_GetError());
        }
        else
        {
            WIDTH=surface->w;
            HEIGHT=surface->h;
        }
        SDL_FreeSurface(surface);
    }

    return newTexture;
}

bool Dot::loadMedia(SDL_Renderer* &renderer)
{
    bool success=true;

    doot=loadTexture("kropka.png", renderer);
    if(doot==NULL)
    {
        printf("Nie udalo sie wczytac kropka.png \n");
        success=false;
    }
    else
    {
        rect.w=WIDTH;
        rect.h=HEIGHT;
    }

    return success;
}

void Dot::present(SDL_Renderer* &renderer)
{
    if(key[SDL_SCANCODE_W])
        rect.y-=speed;
    if(key[SDL_SCANCODE_S])
        rect.y+=speed;

    if(key[SDL_SCANCODE_A])
        rect.x-=speed;
    if(key[SDL_SCANCODE_D])
        rect.x+=speed;

    SDL_RenderCopy(renderer, doot, NULL, &rect);
}

void Dot::close()
{
    SDL_DestroyTexture(doot);
}
