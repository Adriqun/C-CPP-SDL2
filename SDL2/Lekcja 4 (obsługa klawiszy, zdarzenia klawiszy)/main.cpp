#include <SDL.h>
#include <string>
#include <stdio.h>

enum klawisze
{
    KEY_DEFAULT,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_TOTAL
};
int SCREEN_WIDTH=640;
int SCREEN_HEIGHT=480;
SDL_Window* window=NULL;
SDL_Surface* screen=NULL;
SDL_Surface* currentScreen=NULL;
SDL_Surface* key[KEY_TOTAL];

bool init()
{
    bool succes=true;

    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("SDL nie zainicjowal! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }
    else
    {
        window=SDL_CreateWindow("Lekcja 4",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
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
SDL_Surface* loadImage(std::string path)
{
    SDL_Surface* loadedImage=SDL_LoadBMP(path.c_str());

    if(loadedImage==NULL)
        printf("Nie mozna zaladowac %s, SDL Error %s\n",path.c_str(),SDL_GetError());

    return loadedImage;
}
bool loadMedia()
{
    bool succes=true;
    key[KEY_DEFAULT]=loadImage("press.bmp");
    if(key[KEY_DEFAULT]==NULL)
    {
        printf("Nie wczytano press.bmp! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }
    key[KEY_UP]=loadImage("up.bmp");
    if(key[KEY_UP]==NULL)
    {
        printf("Nie wczytano up.bmp! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }
    key[KEY_DOWN]=loadImage("down.bmp");
    if(key[KEY_DOWN]==NULL)
    {
        printf("Nie wczytano down.bmp! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }
    key[KEY_LEFT]=loadImage("left.bmp");
    if(key[KEY_LEFT]==NULL)
    {
        printf("Nie wczytano left.bmp! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }
    key[KEY_RIGHT]=loadImage("right.bmp");
    if(key[KEY_RIGHT]==NULL)
    {
        printf("Nie wczytano right.bmp! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }
    return succes;
}
void update()
{
    bool quit=false;
    SDL_Event e;
    currentScreen=key[KEY_DEFAULT];

    while(!quit)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
                quit=true;
            else
            {
              switch(e.key.keysym.sym)
              {
                  case SDLK_UP: currentScreen=key[KEY_UP]; break;
                  case SDLK_DOWN: currentScreen=key[KEY_DOWN]; break;
                  case SDLK_LEFT: currentScreen=key[KEY_LEFT]; break;
                  case SDLK_RIGHT: currentScreen=key[KEY_RIGHT]; break;
                  default: currentScreen=key[KEY_DEFAULT]; break;
              }
            }
        }
        SDL_BlitSurface(currentScreen,NULL,screen,NULL);
        SDL_UpdateWindowSurface(window);
    }
}
void close()
{
    for(int i=0;i<KEY_TOTAL;++i)
        SDL_FreeSurface(key[i]);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(currentScreen);

    for(int i=0;i<KEY_TOTAL;++i)
        key[i]=NULL;
    window=NULL;
    screen=NULL;
    currentScreen=NULL;

    SDL_Quit();
}
int main(int argc,char*args[])
{
    if(!init())
    {
        printf("Cos poszlo nie tak (init)!\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Cos poszlo nie tak (loadMedia)!\n");
        }
        else
        {
            update();
        }
    }
    close();
    return 0;
}
