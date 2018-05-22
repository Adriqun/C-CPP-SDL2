#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

int SCREEN_WIDTH=640;
int SCREEN_HEIGHT=480;
SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
SDL_Texture* texture=NULL;

bool init()
{
    bool sukces=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("Nie udalo sie zainicjowac! SDL Error: %s\n",SDL_GetError());
        sukces=false;
    }
    else
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
        {
            printf("Filtrowanie textur nie jest wlaczone!");
        }
        window=SDL_CreateWindow("SDL Tutorial",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie udalo sie utworzyc okienka! SDL Error: %s\n",SDL_GetError());
            sukces=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                printf("Blad przy tworzeniu rendera! SDL");
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlag=IMG_INIT_PNG;
                if(!(IMG_Init(imgFlag)&imgFlag))
                {
                    printf("SDL nie zainicjowal PNG! SDL Error %s\n",SDL_GetError());
                    sukces=false;
                }
            }
        }
    }
    return sukces;
}
void drawing()
{
    SDL_Rect outlineRuad= {SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH*2/3, SCREEN_HEIGHT*2/3};
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderFillRect(renderer,&outlineRuad);

    //pozycja x, pozycja y, szerokosc, wysokosc
    SDL_Rect fillRect= {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
    //koloruje prostokat, czerowony,zielony,niebieski,alpha do przezroczystosci
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    //rysuje prostokat
    SDL_RenderFillRect(renderer,&fillRect);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);

    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
    for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
        SDL_RenderDrawPoint( renderer, SCREEN_WIDTH / 2, i );

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
    for( int i = 1; i < 300; i++ )
    {
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH/2+i-1, SCREEN_HEIGHT/2-(i-1)*(i-1), SCREEN_WIDTH/2+i, SCREEN_HEIGHT/2-i*i);
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH/2+i-1, SCREEN_HEIGHT/2+(i-1)*(i-1), SCREEN_WIDTH/2+i, SCREEN_HEIGHT/2+i*i);
    }

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
        drawing();
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

    IMG_Quit();
    SDL_Quit();
}
int main(int argc,char**args)
{
    if(!init())
        printf("Cos poszlo nie tak (init)!\n");

    else
        update();

    close();

    return 0;
}
