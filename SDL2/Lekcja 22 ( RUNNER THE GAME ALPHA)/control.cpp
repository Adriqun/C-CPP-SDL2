#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <sstream>
#include "control.h"
#include "universal.h"

Control::Control()
{
    character.x=-400;
    character.y=621;
    jump=false;
    jumpUp=false;

    mouseDown.x=0;
    mouseDown.y=0;
    mouseMotion.x=0;
    mouseMotion.y=0;

    map.x=0;
    map.y=0;
    meters=0;
    state=SDL_GetKeyboardState(NULL);
    cursor=NULL;
}
void Control::loadCursor(SDL_Renderer* &renderer)
{
    cursor=uni.loadTexture("images/kursor.png",renderer);
}
void Control::mouseControl()
{
    while(SDL_PollEvent(&event)!=0)
    {
        //gdy klikniemy X
        if(event.type==SDL_QUIT)
            SDL_Quit();

        //gdy ruszamy mysza
        if(event.type==SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&mouseMotion.x,&mouseMotion.y);
            coorCursor.x=mouseMotion.x;
            coorCursor.y=mouseMotion.y;
            coorCursor.w=40;
            coorCursor.h=40;
        }


        //gdy klikniemy mysza
        if(event.type==SDL_MOUSEBUTTONDOWN)
            SDL_GetMouseState(&mouseDown.x,&mouseDown.y);
        else
        {
            mouseDown.x=0;
            mouseDown.y=0;
        }
    }
}
void Control::keysControl(int frame)
{
    if(frame==1)
    {
        if(state[SDL_SCANCODE_W]&&jumpUp==false)
            jump=true;
        if(state[SDL_SCANCODE_D]&&character.x<550)
            character.x+=3;
        if(state[SDL_SCANCODE_A]&&character.x>0)
            character.x-=5;

        if(character.x<550)
            character.x+=2;
        if(map.x>2000)
            map.x=0;
        if(character.x>=0)
        {
            map.x+=2;
            meters+=0.15;
        }


        if(character.y>350&&jump==true)
        {
            character.y-=5;
            jumpUp=true;
        }
        else if(character.y>340)
        {
            jump=false;
            if(character.y<621)
            {
                character.y+=5;
                jumpUp=true;
            }
            else
                jumpUp=false;
        }
    }
    else
        close();
}
void Control::close()
{
    character.x=-400;
    character.y=621;
    jump=false;
    jumpUp=false;

    map.x=0;
    map.y=0;
    meters=0;
    state=SDL_GetKeyboardState(NULL);
}
void Control::resetMousePosition(int &x)
{
    if(x==0)
    {
        mouseDown.x=0;
        mouseDown.y=0;
    }
}


Meters::Meters()
{
    font=NULL;
    textTexture=NULL;
    surface=NULL;
    color.b=0xFF;
    color.g=0xFF;
    color.r=0xFF;
}
Meters::~Meters()
{
    font=NULL;
    textTexture=NULL;
    surface=NULL;
}
SDL_Texture* Meters::loadFromRenderedText(std::string path, SDL_Renderer* &renderer)
{
    surface=TTF_RenderText_Solid(font,path.c_str(),color);
    if(surface==NULL)
        printf("Nie mozna utworzyc powierzchni dla tekstu! SDL Error: %s\n",TTF_GetError());
    else
    {
        textTexture=SDL_CreateTextureFromSurface(renderer,surface);
        if(textTexture==NULL)
            printf("Nie mozna utworzyc tekstury z powierzchni tekstu! SDL Error: %s\n",TTF_GetError());

        rect.w=surface->w;
        rect.h=surface->h;
        rect.x=10;
        rect.y=10;
        coorEndMeters.w=surface->w;
        coorEndMeters.h=surface->h;
        coorEndMeters.x=340;
        coorEndMeters.y=50;
        SDL_FreeSurface(surface);
    }
    return textTexture;
}
bool Meters::loadMedia(SDL_Renderer* &renderer)
{
    bool success=true;

    font=TTF_OpenFont("fonts/truelies.ttf",28);
    if(font==NULL)
    {
        printf("Blad przy wczytywaniu trulies.ttf! SDL Error: %s\n",TTF_GetError());
        success=false;
    }

    return success;
}
void Meters::presentMeters(SDL_Renderer* &renderer, int x)
{
    endMeters=x;
    ss<<x;
    str=ss.str();
    str="METERS "+str;
    textTexture=loadFromRenderedText(str, renderer);
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);
    SDL_DestroyTexture(textTexture);
    ss.str("");
}
void Meters::presentEndMeters(SDL_Renderer* &renderer)
{
    ss<<endMeters;
    str=ss.str();
    str="Completed meters "+str;
    textTexture=loadFromRenderedText(str, renderer);
    SDL_RenderCopy(renderer, textTexture, NULL, &coorEndMeters);
    SDL_DestroyTexture(textTexture);
    ss.str("");
}
void Meters::close()
{
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}
