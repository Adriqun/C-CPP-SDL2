#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <time.h>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
const int NUMBER_OF_BLUE_BALLONS=10;

class Ballon
{
    SDL_Texture* texture;
    SDL_Rect rect;
    Mix_Chunk *chunk;
public:
    SDL_Texture* loadTexture(std::string path);
    bool loadMedia();
    void close();
    void present(int xMouse, int yMouse, int speed);
};
Ballon object[NUMBER_OF_BLUE_BALLONS];

bool init()
{
    bool success=true;
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0)
    {
        printf("Nie udalo sie zainicjowac! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    else
    {
        window=SDL_CreateWindow("Balony",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie udalo sie utworzyc okna! SDL Error: %s\n",SDL_GetError());
            success=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer==NULL)
            {
                printf("Nie udalo sie utworzyc rendera! SDL Error: %s\n",SDL_GetError());
                success=false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);

                int imgFlags=IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags))
                {
                    printf("Nie udalo sie zainicjowac IMG! SDL Error: %s\n",IMG_GetError());
                    success=false;
                }

                if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
                {
                    printf("Nie udalo sie zainicjowac MIXERA! SDL Error: %s\n",Mix_GetError());
                    success=false;
                }

            }
        }
    }
    return success;
}
bool loadMedia()
{
    bool success=true;
    for(int i=0; i<NUMBER_OF_BLUE_BALLONS; i++)
    {
        if(!object[i].loadMedia())
        {
            printf("Nie udalo sie wczytac pliku dla klasy Balon SDL Error: %s\n",SDL_GetError());
            success=false;
        }
    }
    return success;
}
void presentScreen()
{
    bool quit=false;
    SDL_Event e;
    int xMouse=-100, yMouse=-100;

    srand(time(NULL));
    while(!quit)
    {
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(renderer);

        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
                quit=true;

            if(e.type==SDL_MOUSEBUTTONDOWN)
                SDL_GetMouseState(&xMouse,&yMouse);
            if(e.type==SDLK_SPACE)
                SDL_GetMouseState(&xMouse,&yMouse);
            if(e.type==SDL_MOUSEBUTTONUP)
            {
                xMouse=-100;
                yMouse=-100;
            }
        }
        for(int  i=0; i<NUMBER_OF_BLUE_BALLONS; i++)
            object[i].present(xMouse,yMouse,5);

        SDL_RenderPresent(renderer);
    }
}
void close()
{
    for(int i=0; i<NUMBER_OF_BLUE_BALLONS; i++)
        object[i].close();

    SDL_DestroyWindow(window);
    window=NULL;

    SDL_DestroyRenderer(renderer);
    renderer=NULL;

    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

int main(int argc,char**)
{
    if(!init())
    {
        printf("Blad przy inicjowaniu!\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Blad przy ladowaniu plikow!\n");
        }
        else
        {
            presentScreen();
        }
    }
    close();
    return 0;
}

SDL_Texture* Ballon::loadTexture(std::string path)
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
        else
        {
            rect.w=surface->w;
            rect.h=surface->h;

            int yPosition=rand()%1000+100;
            yPosition=yPosition*-1;
            rect.y=yPosition;

            int xPosition=rand()%570;
            rect.x=xPosition;
        }
        SDL_FreeSurface(surface);
    }
    return newTexture;
}
bool Ballon::loadMedia()
{
    bool success=true;

    texture=loadTexture("balon1.png");
    if(texture==NULL)
    {
        printf("Nie mozna wczytac pliku balon.png! SDl Error: %s\n",SDL_GetError());
        success=false;
    }

    chunk=Mix_LoadWAV("scratch.wav");
    if(chunk==NULL)
    {
        printf("Nie udalo sie wczytac scratch.wav! SDL Error: %s\n",SDL_GetError());
        success=false;
    }

    return success;
}
void Ballon::close()
{
    SDL_DestroyTexture(texture);
    texture=NULL;

    Mix_FreeChunk(chunk);
    chunk=NULL;
}
void Ballon::present(int x, int y, int speed)
{
    rect.y+=speed;
    if(x<rect.x+rect.w && x>rect.x  &&  y<rect.y+rect.h && y>rect.y)
    {
        rect.x=rand()%570;
        rect.y=(rand()%1000+100)*-1;
        Mix_PlayChannel(-1,chunk,0);
    }
    if(rect.y>480)
    {
        rect.x=rand()%570;
        rect.y=(rand()%1000+100)*-1;
    }
    SDL_RenderCopy(renderer,texture,NULL,&rect);
}
