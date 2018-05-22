#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;

SDL_Texture* texture[8];
Uint8 backgroundA = 0, cloudA = 0, sunA = 0, treeA = 0;

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
        window=SDL_CreateWindow("Lekcja 13",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
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
    bool success = true;

    texture[0]=loadTexture("tloA.png");
    texture[1]=loadTexture("tloB.png");
    texture[2]=loadTexture("slonceA.png");
    texture[3]=loadTexture("slonceB.png");
    texture[4]=loadTexture("chmuraA.png");
    texture[5]=loadTexture("chmuraB.png");
    texture[6]=loadTexture("drzewoA.png");
    texture[7]=loadTexture("drzewoB.png");

    for(int i=0; i<8; i++)
    {
        if(texture[i]==NULL)
        {
            printf( "Wczytywanie danego PNG nie powiodlo sie!\n" );
            success = false;
        }
        else
            SDL_SetTextureBlendMode( texture[i], SDL_BLENDMODE_BLEND );
    }

    return success;
}
void close()
{

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    for(int i=0; i<8; i++)
    {
        SDL_DestroyTexture( texture[i] );
        texture[i] = NULL;
    }
    IMG_Quit();
    SDL_Quit();
}
void update()
{
    SDL_Event e;
    bool quit=false;


    while(!quit)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
                quit=true;

            else if(e.type==SDL_KEYDOWN)
            {
                if( e.key.keysym.sym == SDLK_q )
                {
                    if(backgroundA+32>255)
                        backgroundA=255;

                    else
                        backgroundA += 32;
                }
                if( e.key.keysym.sym == SDLK_a )
                {
                    if(backgroundA-32<0)
                        backgroundA=0;

                    else
                        backgroundA -= 32;
                }

                if( e.key.keysym.sym == SDLK_w )
                {
                    if(sunA+32>255)
                        sunA=255;

                    else
                        sunA += 32;
                }
                if( e.key.keysym.sym == SDLK_s )
                {
                    if(sunA-32<0)
                        sunA=0;

                    else
                        sunA -= 32;
                }

                if( e.key.keysym.sym == SDLK_e )
                {
                    if(cloudA+32>255)
                        cloudA=255;

                    else
                        cloudA += 32;
                }
                if( e.key.keysym.sym == SDLK_d )
                {
                    if(cloudA-32<0)
                        cloudA=0;

                    else
                        cloudA -= 32;
                }

                if( e.key.keysym.sym == SDLK_r )
                {
                    if(treeA+32>255)
                        treeA=255;

                    else
                        treeA += 32;
                }
                if( e.key.keysym.sym == SDLK_f )
                {
                    if(treeA-32<0)
                        treeA=0;

                    else
                        treeA -= 32;
                }
            }
        }
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        SDL_RenderCopy( renderer, texture[0], NULL, NULL);
        SDL_SetTextureAlphaMod(texture[1], backgroundA);
        SDL_RenderCopy( renderer, texture[1], NULL, NULL);

        SDL_RenderCopy( renderer, texture[2], NULL, NULL);
        SDL_SetTextureAlphaMod(texture[3], sunA);
        SDL_RenderCopy( renderer, texture[3], NULL, NULL);

        SDL_RenderCopy( renderer, texture[4], NULL, NULL);
        SDL_SetTextureAlphaMod(texture[5], cloudA);
        SDL_RenderCopy( renderer, texture[5], NULL, NULL);

        SDL_RenderCopy( renderer, texture[6], NULL, NULL);
        SDL_SetTextureAlphaMod(texture[7], treeA);
        SDL_RenderCopy( renderer, texture[7], NULL, NULL);

        SDL_RenderPresent( renderer );
    }
}
int main(int argc, char *argv[])
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
