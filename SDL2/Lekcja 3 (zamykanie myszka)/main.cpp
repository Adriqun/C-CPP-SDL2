#include <SDL.h>
#include <string>
#include <stdio.h>

int SCREEN_WIDTH=640;
int SCREEN_HEIGHT=480;
SDL_Window* window=NULL;
SDL_Surface* screen=NULL;
SDL_Surface* hello=NULL;

bool init()
{
    bool succes=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("SDL nie zainicjowal! SDL Error: %s\n", SDL_GetError());
        succes=false;
    }
    else
    {
        window=SDL_CreateWindow("Lekcja 3",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Okno nie zostalo utworzone! SDL Error: %s\n",SDL_GetError());
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
    hello=SDL_LoadBMP("hello.bmp");
    if(hello==NULL)
    {
        printf("Nie znaleziono hello.bmp SDL Error: %s\n",SDL_GetError());
        succes=false;
    }
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
        SDL_BlitSurface(hello,NULL,screen,NULL);
        SDL_UpdateWindowSurface(window);
    }
}
void close()
{
    SDL_DestroyWindow(window);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(hello);
    window=NULL;
    screen=NULL;
    hello=NULL;

    SDL_Quit();
}
int main(int argc,char* args[])
{
    if(!init())
    {
        printf("Cos poszlo nie tak (init)! \n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Cos poszlo nie tak (loadMedia)! \n");
        }
        else
        {
            update();
        }
    }
    close();
    return 0;
}
