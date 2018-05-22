#include <SDL.h>
#include <stdio.h>
#include <string>

int SCREEN_WIDTH=640;
int SCREEN_HEIGHT=480;
SDL_Surface* screen=NULL;
SDL_Surface* strScreen=NULL;
SDL_Window* window=NULL;
SDL_Rect system;

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* loadedSurface=SDL_LoadBMP(path.c_str());
    SDL_Surface* optimizedSurface=NULL;
    if(loadedSurface==NULL)
    {
        printf("Nie znaleziono %s !, SDL Error: %s\n",path.c_str(),SDL_GetError());
    }
    else
    {
        optimizedSurface=SDL_ConvertSurface(loadedSurface,screen->format,0);
        if(optimizedSurface==NULL)
        {
            printf("Nie skonwertowano obrazka %s ! SDL Error: %s\n",path.c_str(),SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}
bool init()
{
    bool succes=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("Nie zainicjowano SDL'a! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }
    else
    {
        window=SDL_CreateWindow("Lekcja 5", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie mozna utworzyc okna! SDL Error: %s\n",SDL_GetError());
            succes=false;
        }
        else
            screen=SDL_GetWindowSurface(window);
    }
    return succes;
}
bool loadMedia()
{
    bool succes=true;
    strScreen=loadSurface("stretch.bmp");
    if(strScreen==NULL)
    {
        printf("Nie mozna zaladowac obrazka str.bmp! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }
    system.x=0;
    system.y=0;
    system.w=640;
    system.h=480;
    return succes;
}
void update()
{
    bool quit=false;
    SDL_Event e;

    while(!quit)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
                quit=true;
        }
        SDL_BlitScaled(strScreen,NULL,screen,&system);
        SDL_UpdateWindowSurface(window);
    }
}
void close()
{
    SDL_FreeSurface(strScreen);
    SDL_DestroyWindow(window);
    strScreen=NULL;
    window=NULL;
    screen=NULL;
    SDL_Quit();
}
int main(int argc,char* args[])
{
    if(!init())
    {
        printf("Cos poszlo nie tak!(init)\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Cos poszlo nie tak!(loadImage)\n");
        }
        else
            update();
    }
    close();
    return 0;
}
