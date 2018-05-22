//PROGRAM ZOSTAL ZROBIONY W 1 H, BEZ KOPIOWANIA, WSZYSTKO PISANE NA BIEZACA!!!
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <stdio.h>

const int SCREEN_WIDTH=386;
const int SCREEN_HEIGHT=342;
SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
SDL_Texture* basic=NULL;
SDL_Texture* texture[12];
Mix_Chunk* chunk[12];

SDL_Texture* loadTexture(std::string path)
{
    SDL_Texture* newTexture=NULL;
    SDL_Surface* surface=IMG_Load(path.c_str());
    if(surface==NULL)
        printf("Nie udalo sie wczytac %s, SDL Error: %s\n",path.c_str(), IMG_GetError());
    else
    {
        newTexture=SDL_CreateTextureFromSurface(renderer,surface);
        if(newTexture==NULL)
            printf("Nie utworzono tekstury z powierzchni %s, SDL Error: %s\n",path.c_str(), SDL_GetError());
        SDL_FreeSurface(surface);
    }
    return newTexture;
}

bool init()
{
    bool success=true;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0)
    {
        printf("Nie zainicjowano bibliotek! SDL Error: %s\n", SDL_GetError());
        success=false;
    }
    else
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            printf("Liniowe renderowanie tekstru nie jest wlaczone!\n");

        window=SDL_CreateWindow("Elektrycznie pianino",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie utworzony okna! SDL Error: %s\n",SDL_GetError());
            success=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer==NULL)
            {
                printf("Nie utworzono rendera! SDL Error: %s\n",SDL_GetError());
                success=false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer,0,0,0,255);

                int imgFlags=IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags))
                {
                    printf("Nie wczytano biblioteki z grafika! SDL Error: %s\n",IMG_GetError());
                    success=false;
                }
                if(Mix_Init(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048))<0)
                {
                    printf("Nie wczytano biblioteki z dzwiekami! SDL Error: %s\n",Mix_GetError());
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

    chunk[0]=Mix_LoadWAV("sounds/c.wav");
    chunk[1]=Mix_LoadWAV("sounds/cis.wav");
    chunk[2]=Mix_LoadWAV("sounds/d.wav");
    chunk[3]=Mix_LoadWAV("sounds/dis.wav");
    chunk[4]=Mix_LoadWAV("sounds/e.wav");
    chunk[5]=Mix_LoadWAV("sounds/f.wav");
    chunk[6]=Mix_LoadWAV("sounds/fis.wav");
    chunk[7]=Mix_LoadWAV("sounds/g.wav");
    chunk[8]=Mix_LoadWAV("sounds/gis.wav");
    chunk[9]=Mix_LoadWAV("sounds/a.wav");
    chunk[10]=Mix_LoadWAV("sounds/ais.wav");
    chunk[11]=Mix_LoadWAV("sounds/h.wav");

    texture[0]=loadTexture("c.png");
    texture[1]=loadTexture("cis.png");
    texture[2]=loadTexture("d.png");
    texture[3]=loadTexture("dis.png");
    texture[4]=loadTexture("e.png");
    texture[5]=loadTexture("f.png");
    texture[6]=loadTexture("fis.png");
    texture[7]=loadTexture("g.png");
    texture[8]=loadTexture("gis.png");
    texture[9]=loadTexture("a.png");
    texture[10]=loadTexture("ais.png");
    texture[11]=loadTexture("h.png");

    basic=loadTexture("basic.png");

    return success;
}
void close()
{
    SDL_DestroyTexture(basic);
    basic=NULL;

    SDL_DestroyWindow(window);
    window=NULL;

    SDL_DestroyRenderer(renderer);
    renderer=NULL;

    for(int i=0;i<12;i++)
    {
        Mix_FreeChunk(chunk[i]);
        chunk[i]=NULL;
        SDL_DestroyTexture(texture[i]);
        texture[i]=NULL;
    }

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char* args [])
{
    if(!init())
        printf("Cos poszlo nie z tak z init()!\n");
    else
    {
        if(!loadMedia())
            printf("Cos poszlo nie z tak z loadMedia()!\n");
        else
        {
            const Uint8* keys = SDL_GetKeyboardState( NULL );
            SDL_Event e;
            while(true)
            {
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_RenderCopy(renderer, basic, NULL, NULL);

                while(SDL_PollEvent(&e)!=0)
                {
                    if(e.type==SDL_QUIT)
                        return 0;
                    if(keys[SDL_SCANCODE_W])
                    {
                        Mix_PlayChannel( -1, chunk[0], 0 );
                        SDL_RenderCopy(renderer, texture[0], NULL, NULL);
                    }
                    if(keys[SDL_SCANCODE_3])
                    {
                        Mix_PlayChannel( -1, chunk[1], 0 );
                        SDL_RenderCopy(renderer, texture[1], NULL, NULL);
                    }
                    if(keys[SDL_SCANCODE_E])
                    {
                        Mix_PlayChannel( -1, chunk[2], 0 );
                        SDL_RenderCopy(renderer, texture[2], NULL, NULL);
                    }
                    if(keys[SDL_SCANCODE_4])
                    {
                        Mix_PlayChannel( -1, chunk[3], 0 );
                        SDL_RenderCopy(renderer, texture[3], NULL, NULL);
                    }
                    if(keys[SDL_SCANCODE_R])
                    {
                        Mix_PlayChannel( -1, chunk[4], 0 );
                        SDL_RenderCopy(renderer, texture[4], NULL, NULL);
                    }
                    if(keys[SDL_SCANCODE_T])
                    {
                        Mix_PlayChannel( -1, chunk[5], 0 );
                        SDL_RenderCopy(renderer, texture[5], NULL, NULL);
                    }
                    if(keys[SDL_SCANCODE_6])
                    {
                        Mix_PlayChannel( -1, chunk[6], 0 );
                        SDL_RenderCopy(renderer, texture[6], NULL, NULL);
                    }
                    if(keys[SDL_SCANCODE_Y])
                    {
                        Mix_PlayChannel( -1, chunk[7], 0 );
                        SDL_RenderCopy(renderer, texture[7], NULL, NULL);
                    }
                    if(keys[SDL_SCANCODE_7])
                    {
                        Mix_PlayChannel( -1, chunk[8], 0 );
                        SDL_RenderCopy(renderer, texture[8], NULL, NULL);
                    }
                    if(keys[SDL_SCANCODE_U])
                    {
                        Mix_PlayChannel( -1, chunk[9], 0 );
                        SDL_RenderCopy(renderer, texture[9], NULL, NULL);
                    }
                    if(keys[SDL_SCANCODE_8])
                    {
                        Mix_PlayChannel( -1, chunk[10], 0 );
                        SDL_RenderCopy(renderer, texture[10], NULL, NULL);
                    }
                    if(keys[SDL_SCANCODE_I])
                    {
                        Mix_PlayChannel( -1, chunk[11], 0 );
                        SDL_RenderCopy(renderer, texture[11], NULL, NULL);
                    }
                }
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    return 0;
}
