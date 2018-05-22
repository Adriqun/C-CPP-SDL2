#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* background=NULL;

SDL_Texture* pauza;
SDL_Rect rect;
bool boolPauza=false;

Mix_Music *music = NULL;

TTF_Font *font = NULL;
SDL_Texture* textTexture;
SDL_Rect textRect;

int number,counter=0;
std::string songName[50];

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        window = SDL_CreateWindow( "Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                if( Mix_OpenAudio( 24000, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
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
SDL_Texture* loadFromRenderedText( std::string textureText)
{
    SDL_Color textColor = { 91, 123, 170 };
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );

    if( textSurface == NULL )
        printf( "Nie mozna utworzyc powierzchni tekstu! SDL_ttf Error: %s\n", TTF_GetError() );

    else
    {
        textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( textTexture == NULL )
            printf( "Nie mozna utworzyc tekstury z powierzchni tekstu! SDL Error: %s\n", SDL_GetError() );

        textRect.x=(SCREEN_WIDTH/2)-(textSurface->w/2);
        textRect.y=50;
        textRect.w=textSurface->w;
        textRect.h=textSurface->h;

        SDL_FreeSurface( textSurface );
    }
    return textTexture;
}
bool loadFromNotebook(std::string path)
{
    bool success=true;
    std::fstream file;
    std::string line;
    int nr=0;

    file.open(path.c_str());
    while(getline(file,line))
    {
        songName[nr]=line;
        nr++;
    }
    number=nr-1;
    file.close();

    if(nr==1)
        success=false;
    return success;
}
bool loadMedia()
{
    bool success = true;

    font = TTF_OpenFont( "fonts/BAUHS93.ttf", 15 );
    if( font == NULL )
    {
        printf( "Nie mozna odnalezc BAUHS93.ttf! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        textTexture=loadFromRenderedText( songName[0].c_str());
        if( textTexture==NULL )
        {
            printf( "Blad przy renderowanu tekstu!\n" );
            success = false;
        }
    }

    background=loadTexture( "images/tlo.png" );
    if(background==NULL)
    {
        printf( "Failed to load tlo background!\n" );
        success = false;
    }

    pauza=loadTexture("images/pauza.png");
    if(pauza==NULL)
    {
        printf( "Failed to load pauza.png!\n" );
        success = false;
    }
    else
    {
        rect.x=210;
        rect.y=130;
        rect.w=73;
        rect.h=73;
    }
    return success;
}
void close()
{

    Mix_FreeMusic( music );
    music = NULL;

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_DestroyTexture( background );
    SDL_DestroyTexture(pauza);
    pauza = NULL;
    window = NULL;
    renderer = NULL;
    background = NULL;

    TTF_CloseFont( font );
    font = NULL;

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
int main( int argc, char* args[] )
{
    if( !init() )
        printf( "Failed to initialize!\n" );

    else
    {
        if(!loadFromNotebook("text/pliki.txt"))
            printf("Failed to load notebook\n");

        if( !loadMedia() )
            printf( "Failed to load media!\n" );

        else
        {
            bool quit = false;
            SDL_Event e;

            while( !quit )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                        quit = true;
                    if(e.type==SDL_MOUSEBUTTONDOWN)
                    {
                        int x,y;
                        SDL_GetMouseState(&x,&y);

                        if(x>21&&x<91&&y>130&&y<203)
                        {
                            Mix_HaltMusic();
                            boolPauza=false;

                            counter--;
                            if(counter<0)
                                counter=number;

                            textTexture=loadFromRenderedText( songName[counter].c_str());
                        }

                        if(x>115&&x<188&&y>130&&y<203)
                        {
                            Mix_HaltMusic();
                            boolPauza=false;
                        }

                        if(x>210&&x<283&&y>130&&y<203)
                        {
                            std::string add="songs/";
                            add+=songName[counter];

                            music = Mix_LoadMUS(add.c_str());
                            if( music == NULL )
                                printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );

                            if( Mix_PlayingMusic() == 0 )
                            {
                                Mix_PlayMusic( music, -1 );

                                if(boolPauza==false)
                                    boolPauza=true;
                                else
                                    boolPauza=false;
                            }
                            else
                            {
                                if( Mix_PausedMusic() == 1 )
                                    Mix_ResumeMusic();
                                else
                                    Mix_PauseMusic();

                                if(boolPauza==false)
                                    boolPauza=true;
                                else
                                    boolPauza=false;
                            }
                        }
                        if(x>304&&x<377&&y>130&&y<203)
                        {
                            Mix_HaltMusic();
                            boolPauza=false;

                            counter++;
                            if(counter==number)
                                counter=0;

                            textTexture=loadFromRenderedText( songName[counter].c_str());
                        }
                    }
                }
                //renderowanie textur
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( renderer );
                SDL_RenderCopy(renderer,background,NULL,NULL);
                if(boolPauza==true)
                    SDL_RenderCopy(renderer,pauza,NULL,&rect);
                SDL_RenderCopy(renderer,textTexture,NULL,&textRect);

                SDL_RenderPresent( renderer );
            }
        }
    }
    close();
    return 0;
}
