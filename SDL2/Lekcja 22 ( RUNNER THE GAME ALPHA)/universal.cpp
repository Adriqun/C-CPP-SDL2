#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <math.h>
#include "universal.h"

Universal::Universal()
{
    nr=0;
}
SDL_Texture* Universal::loadTexture(std::string path, SDL_Renderer* &renderer)
{
    SDL_Surface* surface=IMG_Load(path.c_str());
    SDL_Texture* newTexture=NULL;

    if(surface==NULL)
    {
        printf("Nie odnaleziono %s SDL Error: %s\n",path.c_str(),IMG_GetError());
    }

    else
    {
        SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0,0,0));
        newTexture=SDL_CreateTextureFromSurface(renderer,surface);

        if(newTexture==NULL)
        {
            printf("Nie mozna utworzyc tekstury z powierzchni SDL Error: %s\n",SDL_GetError());
        }

        SDL_FreeSurface(surface);
    }

    return newTexture;
}
int Universal::counter(int cage, int fixed)
{
    nr++;
    if(nr>cage*fixed)
        nr=0;
    return nr;
}
SDL_Texture* Universal::loadMenuTexture(std::string path, SDL_Renderer* &renderer)
{
    SDL_Surface* surface=IMG_Load(path.c_str());
    SDL_Texture* newTexture=NULL;
    if(surface==NULL)
    {
        printf("Nie odnaleziono %s SDL Error: %s\n",path.c_str(),IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0,0xFF,0xFF));
        newTexture=SDL_CreateTextureFromSurface(renderer,surface);
        if(newTexture==NULL)
        {
            printf("Nie mozna utworzyc tekstury z powierzchni SDL Error: %s\n",SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }
    return newTexture;
}
SDL_Texture* Universal::loadRunTexture(std::string path, SDL_Renderer* &renderer)
{
    SDL_Surface* surface=IMG_Load(path.c_str());
    SDL_Texture* newTexture=NULL;
    if(surface==NULL)
    {
        printf("Nie odnaleziono %s SDL Error: %s\n",path.c_str(),IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0xFF,0xFF,0xFF));
        newTexture=SDL_CreateTextureFromSurface(renderer,surface);
        if(newTexture==NULL)
        {
            printf("Nie mozna utworzyc tekstury z powierzchni SDL Error: %s\n",SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }
    return newTexture;
}
