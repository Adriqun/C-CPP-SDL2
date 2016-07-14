#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

int SCREEN_WIDTH=640;
int SCREEN_HEIGHT=480;
SDL_Window* window=NULL;
SDL_Texture* texture=NULL;
SDL_Renderer* renderer=NULL;
SDL_Rect topLeftView;
SDL_Rect topRightView;
SDL_Rect bottomView;

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
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
        {
            printf("Filtrowanie tekstur nie wlaczone!");
        }
        window=SDL_CreateWindow("Lekcja 9",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie utworzono okienka! SDL Error: %s\n",SDL_GetError());
            succes=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                printf("Nie stworzono rendera! SDL Error: %s\n",SDL_GetError());
                succes=false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer,0xFF, 0xFF, 0xFF, 0xFF);
                int f=IMG_INIT_PNG;
                if(!(IMG_Init(f)&f))
                {
                    printf("Nie mozna zainicjowac IMG_INIT_PNG SDL_image Error: %s\n", IMG_GetError());
                    succes=false;
                }
            }
        }
    }
    return succes;
}
SDL_Texture* loadTexture(std::string path)
{
    SDL_Texture* newTexture=NULL;
    SDL_Surface* loadedSurface=IMG_Load(path.c_str());
    if(loadedSurface==NULL)
    {
        printf("Nie mozna zaladowac %s SDL Error: %s\n",path.c_str(),IMG_GetError());
    }
    else
    {
        newTexture=SDL_CreateTextureFromSurface(renderer,loadedSurface);
        if(newTexture==NULL)
        {
            printf("Nie stworzono tekstury z %s SDL Error: %s\n",path.c_str(),SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
bool loadMedia()
{
    bool succes=true;
    texture=loadTexture("viewport.png");
    if(texture==NULL)
    {
        printf("Nie odnaleziono viewport.png ! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }
    topLeftView.x=0;
    topLeftView.y=0;
    topLeftView.w=SCREEN_WIDTH/2;
    topLeftView.h=SCREEN_HEIGHT/2;

    topRightView.x=SCREEN_WIDTH/2;
    topRightView.y=0;
    topRightView.w=SCREEN_WIDTH/2;
    topRightView.h=SCREEN_HEIGHT/2;

    bottomView.x=0;
    bottomView.y=SCREEN_HEIGHT/2;
    bottomView.w=SCREEN_WIDTH;
    bottomView.h=SCREEN_HEIGHT/2;

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
        SDL_SetRenderDrawColor(renderer,0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        SDL_RenderSetViewport(renderer,&topLeftView);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderSetViewport(renderer,&topRightView);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderSetViewport(renderer,&bottomView);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }
}
void close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    renderer=NULL;
    texture=NULL;
    window=NULL;

    SDL_Quit();
    IMG_Quit();
}
int main(int argc,char**args)
{
    if(!init())
    {
        printf("Cos poszlo nie tak! (init)\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Cos poszlo nie tak! (loadMedia)\n");
        }
        else
        {
            update();
        }
    }
    close();
    return 0;
}
