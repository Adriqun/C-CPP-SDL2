#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>

const int SCREEN_WIDTH=1000;
const int SCREEN_HEIGHT=800;

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;

SDL_Rect AmmoCoor;
SDL_Texture* ammo;

bool init()
{
    bool success=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("Blad przy inicjowaniu video! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    else
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
        {
            printf( "Filtrowanie tekstur nie jest wlaczone!\n" );
        }
        window=SDL_CreateWindow("NONAME",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie mozna utworzyc okienka! SDL Error: %s\n",SDL_GetError());
            success=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                printf("Nie mozna utworzyc rendera! SDL Error: %s\n",SDL_GetError());
                success=false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);

                int imgFlags=IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags))
                {
                    printf("Nie mozna zainicjowac IMG INIT! SDL Error %s\n",IMG_GetError());
                    success=false;
                }
            }
        }
    }
    return success;
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
    bool success = true;

    ammo=loadTexture("ammo.png");
    if(ammo==NULL)
    {
        printf("Brakuje pliku ammo.png!\n");
        success=false;
    }

    AmmoCoor.w=10;
    AmmoCoor.h=5;
    AmmoCoor.x=0;
    AmmoCoor.y=0;

    return success;
}
void close()
{
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_DestroyTexture( ammo );

    ammo = NULL;
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}
void updateScreen()
{
    bool quit=false;
    SDL_Event e;

    int x,y;
    int prog=0,length=0;
    float wx,wy,ammoX,ammoY,speed=0.2;
    double angle;

    while(!quit)
    {
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(renderer);

        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
                quit=true;

            if(e.type==SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&x,&y);

                prog=0;
                angle=atan2(AmmoCoor.y - y, AmmoCoor.x - x)*180/M_PI;
                length = sqrt( pow((AmmoCoor.x-x),2) + pow((AmmoCoor.y-y),2) );
                wx=speed*cos(angle/180*M_PI);
                wy=speed*sin(angle/180*M_PI);
            }

        }
        if( prog<length )
        {
            ammoX-=wx;
            ammoY-=wy;
            AmmoCoor.x=ammoX;
            AmmoCoor.y=ammoY;
            prog+=speed;
        }

        SDL_RenderCopyEx(renderer,ammo,NULL,&AmmoCoor,angle,NULL,SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
    }
}
int main(int argc,char**args)
{
    if(!init())
        printf("Ups\n");

    else
    {
        if(!loadMedia())
            printf("Ups\n");

        else
            updateScreen();
    }
    close();
    return 0;
}
