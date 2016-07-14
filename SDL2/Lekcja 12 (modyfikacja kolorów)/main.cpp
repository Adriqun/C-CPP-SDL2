#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
SDL_Texture* texture=NULL;

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
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Filtrowanie tekstur nie jest wlaczone!\n" );
        }
        window=SDL_CreateWindow("Lekcja 12",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie mozna utworzyc okienka! SDL Error: %s\n",SDL_GetError());
            succes=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                printf("Nie mozna utworzyc rendera! SDL Error: %s\n",SDL_GetError());
                succes=false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags=IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags))
                {
                    printf("Nie mozna zainicjowac IMG INIT! SDL Error %s\n",IMG_GetError());
                    succes=false;
                }
            }
        }
    }
    return succes;
}
SDL_Texture* loadTexture(std::string path)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if( loadedSurface == NULL )
    {
        printf( "Nie mozna zaladowac %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Nie mozna stworzyc tekstury z %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}
bool loadMedia()
{
    bool succes=true;
    texture=loadTexture("colors.png");
    if(texture==NULL)
    {
        printf( "Blad przy wczytywaniu colors.png!\n" );
        succes = false;
    }
    return succes;
}
void close()
{
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_DestroyTexture( texture );
    window = NULL;
    renderer = NULL;
    texture = NULL;

    IMG_Quit();
    SDL_Quit();
}
void update()
{
    SDL_Event e;
    bool quit=false;
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;

    while(!quit)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
                quit=true;
            else if(e.type==SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                //Increase red
                case SDLK_q:
                    r += 32;
                    break;

                //Increase green
                case SDLK_w:
                    g += 32;
                    break;

                //Increase blue
                case SDLK_e:
                    b += 32;
                    break;

                //Decrease red
                case SDLK_a:
                    r -= 32;
                    break;

                //Decrease green
                case SDLK_s:
                    g -= 32;
                    break;

                //Decrease blue
                case SDLK_d:
                    b -= 32;
                    break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetTextureColorMod(texture,r,g,b);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }
}
int main(int argc,char**args)
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
    return  0;
}
