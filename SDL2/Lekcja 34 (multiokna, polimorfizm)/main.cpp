#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>

const int MAIN_SCREEN_WIDTH=640;
const int MAIN_SCREEN_HEIGHT=400;
const int SCREEN_WIDTH=400;
const int SCREEN_HEIGHT=300;

SDL_Window* window=NULL;
SDL_Window* mainWindow=NULL;
SDL_Renderer* renderer=NULL;
SDL_Renderer* mainRenderer=NULL;

SDL_Texture* loadTexture(SDL_Renderer* &renderer, std::string path)
{
    SDL_Surface* surface=IMG_Load(path.c_str());
    SDL_Texture* newTexture=NULL;
    if(surface==NULL)
    {
        printf("Nie wczytano %s, Error: %s\n",path.c_str(),IMG_GetError());
    }
    else
    {
        newTexture=SDL_CreateTextureFromSurface(renderer, surface);
        if(newTexture==NULL)
        {
            printf("Nie utworzono tekstury z %s, Error: %s\n",path.c_str(), IMG_GetError());
        }
        SDL_FreeSurface(surface);
    }
    return newTexture;
}

class Transformers
{
public:
    virtual bool loadMedia(std::string path)=0;
    virtual void render()=0;
    virtual void close()=0;
};

class Decepticon :public Transformers
{
public:
    SDL_Texture* texture;
    SDL_Rect rect;

    virtual bool loadMedia(std::string path);
    virtual void render();
    virtual void close();
};

class Autobot :public Decepticon
{
public:
    SDL_Texture* texture;
    SDL_Rect rect;

    virtual bool loadMedia(std::string path);
    virtual void render();
};

class Button:public Decepticon
{
public:
    SDL_Texture* texture;
    SDL_Rect rect;

    virtual bool loadMedia(std::string path, int y);
    virtual void render();
};

bool Decepticon::loadMedia(std::string path)
{
    texture=loadTexture(mainRenderer, path.c_str());
    rect.w=972/3;
    rect.h=1128/3;
    rect.x=0;
    rect.y=0;

    return true;
}
bool Autobot::loadMedia(std::string path)
{
    texture=loadTexture(mainRenderer, path.c_str());
    rect.w=992/3;
    rect.h=967/3;
    rect.x=0;
    rect.y=0;

    return true;
}
bool Button::loadMedia(std::string path, int y)
{
    texture=loadTexture(renderer, path.c_str());
    rect.w=200;
    rect.h=100;
    rect.x=100;
    rect.y=y;

    return true;
}

void Decepticon::render()
{
    SDL_RenderCopy(mainRenderer, texture, NULL, &rect);
}
void Autobot::render()
{
    SDL_RenderCopy(mainRenderer, texture, NULL, &rect);
}
void Button::render()
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void Decepticon::close()
{
    texture=NULL;
}

Decepticon decepticon;
Autobot autobot;
Button one, two;
Transformers* wsk;

bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        printf("Nie zainicjowano bibliotek! Error:%s\n",SDL_GetError());
        return false;
    }
    else
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            printf("Nie ustawiono filtrowania liniowego!\n");

        window=SDL_CreateWindow("Plecak", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie utworzono okno dla plecaka! Error %s\n", SDL_GetError());
            return false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                printf("Nie utworzono rendera dla plecaka! Error %s\n", SDL_GetError());
                return false;
            }
            else
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 255);
        }
        mainWindow=SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAIN_SCREEN_WIDTH, MAIN_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(mainWindow==NULL)
        {
            printf("Nie utworzono glownego okna! Error %s\n", SDL_GetError());
            return false;
        }
        else
        {
            mainRenderer=SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
            if(mainRenderer==NULL)
            {
                printf("Nie utworzono glownego rendera! Error %s\n", SDL_GetError());
                return false;
            }
            else
                SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 255);
        }
        if(!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG))
        {
            printf("Nie zainicjowano IMG! Error: %s\n", IMG_GetError());
            return false;
        }
    }
    return true;
}

bool loadMedia()
{
    if(!one.loadMedia("autobot.png",50))
    {
        printf("Nie wczytano obiektu one!\n");
        return false;
    }

    if(!two.loadMedia("decepticon.png",200))
    {
        printf("Nie wczytano obiektu two!\n");
        return false;
    }

    if(!autobot.loadMedia("a.png"))
    {
        printf("Blad przy wczytywaniu obiekt autobot!\n");
        return false;
    }

    if(!decepticon.loadMedia("b.png"))
    {
        printf("Blad przy wczytywaniu obiekt decepticon!\n");
        return false;
    }

    return true;
}

void render()
{
    SDL_Event e;
    int x,y;
    wsk = &autobot;

    for(;;)
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 255);
        SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 255);

        SDL_RenderClear(renderer);
        SDL_RenderClear(mainRenderer);

        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&x, &y);
                if(x>100 && x<300 && y>50 && y<150)
                    wsk = &autobot;
                if(x>100 && x<300 && y>200 && y<300)
                    wsk = &decepticon;
            }
            else
            {
                x=0;
                y=0;
            }
        }

        one.render();
        two.render();

        wsk -> render();


        SDL_RenderPresent(renderer);
        SDL_RenderPresent(mainRenderer);
    }

}

void close()
{
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_DestroyWindow(mainWindow);
    mainWindow=NULL;

    SDL_DestroyRenderer(renderer);
    renderer=NULL;
    SDL_DestroyRenderer(mainRenderer);
    mainRenderer=NULL;

    one.close();
    two.close();

    decepticon.close();
    autobot.close();


    SDL_Quit();
    IMG_Quit();
}

int main(int argc, char* args [])
{
    if(!init())
    {
        printf("Cos nie tak w init()!\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Cos nie tak w loadMedia()!\n");
        }
        else
            render();
    }

    close();
    return 0;
}
