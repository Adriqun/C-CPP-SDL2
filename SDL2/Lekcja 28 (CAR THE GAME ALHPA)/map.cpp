#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include <string>
#include <fstream>
#include <math.h>
#include <cstdlib>

#include "map.h"

using namespace std;

Map::Map()
{
    WIDTH=0;
    HEIGHT=0;
    texture=NULL;
    rect=NULL;
    nr_rect=0;
    nr=0;
}

Map::~Map()
{
    texture=NULL;
    rect=NULL;
}

SDL_Texture* Map::loadTexture(string path, SDL_Renderer* &renderer)
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
            WIDTH=surface->w;
            HEIGHT=surface->h;
        }
        SDL_FreeSurface(surface);
    }

    return newTexture;
}

void Map::setPosition(int x, int y)
{
    //otwieranie pliku
    file.open("map.txt", ios::app | ios::out);

    //zapisywanie pozycji
    file<<x<<endl<<y<<endl;

    //zamykanie pliku
    file.close();
///////////////////////////////////////////////////////////////////////

    string line;
    //otwieranie pliku (odczyt)
    file.open("map.txt", ios::in);

    //wczytanie pozycji
    while(getline(file, line))
    {
        //x klocka
        rect[nr].x=atoi(line.c_str());

        //y klocka
        getline(file, line);
        rect[nr].y=atoi(line.c_str());

        //w i h klocka
        rect[nr].w=WIDTH;
        rect[nr].h=HEIGHT;

        //kolejny klocek (licznik)
        nr++;
    }
    nr_rect=nr+1;
    nr=0;

    //zamkniecie pliku
    file.close();
}

bool Map::loadMedia(SDL_Renderer* &renderer)
{
    texture=loadTexture("block.png", renderer);
    if(texture==NULL)
    {
        printf("Blad przy wczytywaniu tekstury block.png! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    else
    {
        rect=new SDL_Rect[40000];

        for(int i=0; i<301; i++)
        {
            setPosition(i, 799);
        }

        for(int i=300; i<1000; i++)
        {
            setPosition(i, 800-(i-300)*0.2);
        }
    }

    return true;
}

void Map::collision(SDL_Rect &champ, SDL_Rect &coor, double &angle)
{
    if( champ.y + champ.h > coor.y && champ.y < coor.y+coor.h && champ.x + champ.w > coor.x && champ.x < coor.x+coor.w)
    {
        champ.y-=champ.y + champ.h-coor.y-25;
        if(champ.y+champ.h<800)
            angle=(atan2(champ.y - coor.y, champ.x - coor.x)*180/M_PI)+150;
        else
        {
            champ.y=700;
            angle=0;
        }
    }

    if( champ.y + champ.h < coor.y && champ.y < coor.y+coor.h && champ.x + champ.w > coor.x && champ.x < coor.x+coor.w)
    {
        champ.y+=coor.y-(champ.y + champ.h)+25;
        if(champ.y+champ.h<800)
            angle=(atan2(champ.y - coor.y, champ.x - coor.x)*180/M_PI)+150;
        else
        {
            champ.y=700;
            angle=0;
        }
    }
}

void Map::render(SDL_Rect &champ, double &angle, SDL_Renderer* &renderer)
{
    for(int i=0; i<nr_rect; i++)
    {
        SDL_RenderCopy(renderer, texture, NULL, &rect[i]);
        collision(champ, rect[i], angle);
    }
}

void Map::close()
{
    SDL_DestroyTexture(texture);
    delete [] rect;
}
