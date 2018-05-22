#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

int SCREEN_WIDTH=640;
int SCREEN_HEIGHT=480;
SDL_Texture* texture=NULL;
SDL_Renderer* renderer=NULL;
SDL_Window* window=NULL;

bool init()
{
    bool succes=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("Nie zainicjowalano SDL VIDEO! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }
    else
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
        window=SDL_CreateWindow("Lekcja 7",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie udalo sie utworzyc okienka! SDL Error: %s\n",SDL_GetError());
            succes=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                printf("Nie utworzono rendera! SDL Error: %s\n",SDL_GetError());
                succes=false;
            }
            else
            {
                //Use this function to set the color used for drawing operations
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int P=IMG_INIT_PNG;
                if(!(IMG_Init(P)&P))
                {
                    printf("SDL_image nie zainicjowal! SDL Error %s\n",SDL_GetError());
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
        printf("Ladowanie pliku %s nie powiodlo sie! SDL Error: %s\n",path.c_str(),IMG_GetError());
    }
    else
    {
        newTexture=SDL_CreateTextureFromSurface(renderer,loadedSurface);
        if(newTexture==NULL)
        {
            printf("Nie stworzono tekstury z %s ! SDL Error: %s\n",path.c_str(),SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
bool loadMedia()
{
    bool succes=true;
    texture=loadTexture("texture.png");
    if(texture==NULL)
    {
        printf("Nie odnaleziono texture.png!\n");
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
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,texture,NULL,NULL);
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
        printf("Cos poszlo nie tak (init)!\n");
    else
    {
        if(!loadMedia())
            printf("Cos poszlo nie tak (loadMedia)!\n");
        else
            update();
    }
    close();
    return 0;
}
