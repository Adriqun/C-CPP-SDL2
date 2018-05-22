#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

int SCREEN_WIDTH=640;
int SCREEN_HEIGHT=480;
SDL_Window* window=NULL;
SDL_Surface* screenSurface=NULL;
SDL_Surface* JPGSurface=NULL;
SDL_Surface* TIFSurface=NULL;
SDL_Surface* defaultSurface=NULL;
SDL_Surface* currentSurface=NULL;

bool init()
{
    bool succes=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("Nie zainicjowano SDL VIDEO! SDL Error: %s\n", SDL_GetError());
        succes=false;
    }
    else
    {
        window=SDL_CreateWindow("Lekcja 6",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie mozna utworzyc okienka! SDL Error: %s\n",SDL_GetError());
            succes=false;
        }
        else
        {
            int imgFlags=IMG_INIT_JPG;

            if(!(IMG_Init(imgFlags)&imgFlags))
            {
                printf("Inicjowanie flagi JPG nie dziala!\n");
                succes=false;
            }
            imgFlags=IMG_INIT_TIF;

            if(!(IMG_Init(imgFlags)&imgFlags))
            {
                printf("Inicjowanie flagi TIF nie dziala!\n");
                succes=false;
            }
            else
                screenSurface=SDL_GetWindowSurface(window);
        }
    }
    return succes;
}
SDL_Surface* loadImage(std::string path)
{
    SDL_Surface* loadedImage=IMG_Load(path.c_str());
    SDL_Surface* optimizedSurface=NULL;

    if(loadedImage==NULL)
    {
        printf("Plik o nazwie %s nie istnieje! SDL Error: %s\n",path.c_str(),IMG_GetError());
    }
    else
    {
        optimizedSurface=SDL_ConvertSurface(loadedImage,screenSurface->format,0);
        if(optimizedSurface==NULL)
        {
            printf("Nie mozna skonwerowac pliku %s ! SDL Error: %s\n",path.c_str(), SDL_GetError());
        }
        else
            SDL_FreeSurface(loadedImage);
    }
    return optimizedSurface;
}
bool loadMedia()
{
    bool succes=true;

    JPGSurface=loadImage("loaded.jpg");
    if(JPGSurface==NULL)
    {
        printf("Nie mozna odnalezc pliku loaded.jpg! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }

    TIFSurface=loadImage("loaded.tif");
    if(TIFSurface==NULL)
    {
        printf("Nie mozna odnalezc pliku loaded.tif! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }

    defaultSurface=loadImage("default.jpg");
    if(defaultSurface==NULL)
    {
        printf("Nie mozna odnalezc pliku default.jpg! SDL Error: %s\n",SDL_GetError());
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
            else
                {
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_1: currentSurface=JPGSurface; break;
                        case SDLK_2: currentSurface=TIFSurface; break;
                        default: currentSurface=defaultSurface;
                    }
                }
        }
        SDL_BlitSurface(currentSurface,NULL,screenSurface,NULL);
        SDL_UpdateWindowSurface(window);
    }
}
void close()
{
    SDL_FreeSurface(screenSurface);
    SDL_FreeSurface(JPGSurface);
    SDL_FreeSurface(TIFSurface);
    SDL_FreeSurface(defaultSurface);
    SDL_FreeSurface(currentSurface);

    SDL_DestroyWindow(window);
    screenSurface=NULL;
    JPGSurface=NULL;
    TIFSurface=NULL;
    defaultSurface=NULL;
    currentSurface=NULL;
    window=NULL;

    IMG_Quit();
    SDL_Quit();
}
int main(int argc,char**args)
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
