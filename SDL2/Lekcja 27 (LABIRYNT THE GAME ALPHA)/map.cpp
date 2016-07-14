#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include "map.h"

Map::Map()
{
    rectangle=NULL;
    block=NULL;

    WIDTH=0;
    HEIGHT=0;
    nr_block=0;
    nr=0;
}

Map::~Map()
{
    rectangle=NULL;
    block=NULL;
}

void Map::collision(SDL_Rect &champ, SDL_Rect &coor)
{
    int top=coor.y;
    int bot=coor.y+coor.h;

    int left=coor.x;
    int right=coor.x+coor.w;

    if(champ.x < 0 )
        champ.x+=3;

    if(champ.x + champ.w > 936 )
        champ.x-=3;

    if(champ.y < 0 )
        champ.y+=3;

    if(champ.y + champ.h> 728 )
        champ.y-=3;

    if( champ.x + champ.w >= left && champ.x < right && champ.y + champ.h > top && champ.y < bot)
        champ.x-=3;

    if( champ.x <= right && champ.x + champ.w > left && champ.y < bot && champ.y + champ.h> top)
        champ.x+=6;

    if( champ.y + champ.h > top && champ.y < bot && champ.x + champ.w > left && champ.x < right)
        champ.y-=3;

    if( champ.y <= bot && champ.y + champ.h > top && champ.x < right && champ.x + champ.w > left)
        champ.y+=6;
}

SDL_Texture* Map::loadTexture(std::string path, SDL_Renderer* &renderer)
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

void Map::setPosition(int x, int y)
{
    std::string line;

    //otwieranie pliku ,zapisywanie pozycji, zamykanie pliku
    file.open("mapa.txt", std::ios::out | std::ios::app);
    file<<x<<std::endl<<y<<std::endl;
    file.close();

    //otwarcie pliku
    file.open("mapa.txt", std::ios::in);

    //wczytanie pozycji
    while(getline(file, line))
    {
        block[nr].x=atoi(line.c_str());

        getline(file, line);
        block[nr].y=atoi(line.c_str());

        block[nr].w=WIDTH;
        block[nr].h=HEIGHT;

        nr++;
    }
    nr_block=nr+1;
    nr=0;

    //zamkniecie pliku
    file.close();
}
/*
void delete_last_position()
{
    std::string line[20000];
    int number=0;

    //otwieramy plik i przepisujemy to co sie w nim znajduje i zamykamy
    file.open("mapa.txt", std::ios::in);

    while(getline(file, line[number]))
        number++;

    file.close();

    //usuwamy ten plik
    system("del mapa.txt ");

    //tworzymy nowy plik o tej samej nazwie i przepisujemy to co bylo bez 2 ostatnich linijek
    file.open("mapa.txt", std::ios::out | std::ios::app);

    for(int i=0; i<number-2; i++)
        file<<line[i]<<std::endl;

    file.close();

    //wyswietlamy zmiany
    file.open("mapa.txt", std::ios::in);

    std::string linee;

    while(getline(file, linee))
    {
        block[nr].x=atoi(linee.c_str());

        getline(file, linee);
        block[nr].y=atoi(linee.c_str());

        block[nr].w=26;
        block[nr].h=26;

        nr++;
    }
    nr_block=nr+1;
    nr=0;

    file.close();

    //celowe opoznienie gdyby komputer byl za szybki i zrobil np 2x te wszystkie wyzej wymienione dzialania
    SDL_Delay(1000);
}
*/

bool Map::loadMedia(SDL_Renderer* &renderer)
{
    bool success=true;

    rectangle=loadTexture("kwadrat.png", renderer);
    if(rectangle==NULL)
    {
        printf("Nie udalo sie wczytac kwadrat.png \n");
        success=false;
    }
    else
    {
        rect.w=WIDTH;
        rect.h=HEIGHT;

        block=new SDL_Rect[30000];
        setPosition(-100,-100);
    }

    return success;
}

void Map::present(SDL_Renderer* &renderer)
{
    SDL_Event e;
    /*const Uint8 *key = SDL_GetKeyboardState(NULL);*/

    for(;;)
    {
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0x4B, 0x22, 0x22, 255);

        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
                SDL_Quit();

            /*if(key[SDL_SCANCODE_Z])
                delete_last_position();*/

            if(e.type==SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&rect.x, &rect.y);

                for(int i=0; i<40; i++)
                    if(rect.x<WIDTH*i)
                    {
                        rect.x=WIDTH*i-WIDTH;
                        break;
                    }

                for(int i=0; i<40; i++)
                    if(rect.y<HEIGHT*i)
                    {
                        rect.y=HEIGHT*i-HEIGHT;
                        break;
                    }
            }
            if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&rect.x, &rect.y);

                for(int i=0; i<40; i++)
                    if(rect.x<WIDTH*i)
                    {
                        rect.x=WIDTH*i-WIDTH;
                        break;
                    }

                for(int i=0; i<40; i++)
                    if(rect.y<HEIGHT*i)
                    {
                        rect.y=HEIGHT*i-HEIGHT;
                        break;
                    }

                setPosition(rect.x, rect.y);
            }
        }
        SDL_RenderCopy(renderer, rectangle, NULL, &rect);

        for(int i=0; i<nr_block; i++)
            SDL_RenderCopy(renderer, rectangle, NULL, &block[i]);

        SDL_RenderPresent(renderer);
    }
}

void Map::show(SDL_Renderer* &renderer, SDL_Rect &champ)
{
    for(int i=0; i<nr_block; i++)
    {
        SDL_RenderCopy(renderer, rectangle, NULL, &block[i]);
        collision(champ, block[i]);
    }
}

void Map::close()
{
    SDL_DestroyTexture(rectangle);
    delete [] block;
}
