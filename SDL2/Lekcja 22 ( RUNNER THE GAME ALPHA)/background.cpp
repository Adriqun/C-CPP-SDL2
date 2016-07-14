#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include "background.h"
#include "universal.h"

Play::Play()
{
    //przypisywanie wartosci startowych
    wall=NULL;
    grass=NULL;
    music=NULL;
}
Play::~Play()
{
    //ustawianie wskaznikow na NULL'a
    wall=NULL;
    grass=NULL;
    for(int i=0; i<18; i++)
        palm[i]=NULL;
    music=NULL;
}
bool Play::loadMedia(SDL_Renderer* &renderer)
{
    //pobieranie czasu z komputera
    srand(time(NULL));
    bool success=true;

    //wczytywanie sciany
    wall=uni.loadTexture("palms/wall.png",renderer);
    if(wall==NULL)
    {
        printf("Problem z wczytaniem wall.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    //wczytywanie trawy
    grass=uni.loadTexture("palms/grass.png",renderer);
    if(grass==NULL)
    {
        printf("Problem z wczytaniem grass.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    //ustawianie startowej pozycji dla sciany i trawy
    coorWall.w=2000;
    coorWall.h=800;

    //wczytywanie palm
    palm[0]=uni.loadTexture("palms/1.png",renderer);
    palm[1]=uni.loadTexture("palms/2.png",renderer);
    palm[2]=uni.loadTexture("palms/3.png",renderer);
    palm[3]=uni.loadTexture("palms/4.png",renderer);
    palm[4]=uni.loadTexture("palms/5.png",renderer);
    palm[5]=uni.loadTexture("palms/6.png",renderer);
    palm[6]=uni.loadTexture("palms/7.png",renderer);
    palm[7]=uni.loadTexture("palms/8.png",renderer);
    palm[8]=uni.loadTexture("palms/9.png",renderer);
    palm[9]=uni.loadTexture("palms/10.png",renderer);
    palm[10]=uni.loadTexture("palms/11.png",renderer);
    palm[11]=uni.loadTexture("palms/12.png",renderer);
    palm[12]=uni.loadTexture("palms/13.png",renderer);
    palm[13]=uni.loadTexture("palms/14.png",renderer);
    palm[14]=uni.loadTexture("palms/15.png",renderer);
    palm[15]=uni.loadTexture("palms/16.png",renderer);
    palm[16]=uni.loadTexture("palms/17.png",renderer);
    palm[17]=uni.loadTexture("palms/18.png",renderer);

    //ustawianie pozycji palm
    for(int i=0; i<5; i++)
    {
        coorPalm[i].w=500;
        coorPalm[i].h=800;
        coorPalm[i].y=0;
        coorPalm[i].x=400*i;
        random[i]=rand()%17+1;
    }

    music=Mix_LoadMUS("music/a.mp3");
    if(music==NULL)
    {
        printf("Cos poszlo nie tak z muzyka! SDL Error: %s\n",Mix_GetError());
        success=false;
    }

    return success;
}
void Play::present(SDL_Renderer* &renderer, int xMap, int frame)
{
    if(frame==1)
    {
        if(Mix_PlayingMusic()==0)
            Mix_PlayMusic( music, -1 );

        coorWall.x=xMap*-1;
        //losowanie grafiki
        if(xMap==500)
            random[0]=rand()%10+1;
        if(xMap==1000)
            random[1]=rand()%5+1;
        if(xMap==1500)
            random[2]=rand()%14+3;
        if(xMap==2000)
            random[3]=rand()%17+1;
        if(xMap==5)
            random[4]=rand()%9+8;

        //wyswietlanie palm w obszarze 0-2000
        for(int i=0; i<5; i++)
        {
            coorPalm[i].x=(xMap*-1)+(400*i);
            SDL_RenderCopy(renderer,palm[random[i]],NULL,&coorPalm[i]);
        }

        //wyswietlanie trawy w obszarze 0-2000
        SDL_RenderCopy(renderer,grass,NULL,&coorWall);

        //wyswietlanie palm w obszarze 2000-4000
        for(int i=0; i<5; i++)
        {
            coorPalm[i].x=(xMap*-1)+(400*i)+2000;
            SDL_RenderCopy(renderer,palm[random[i]],NULL,&coorPalm[i]);
        }

        //wyswietlanie trawy w obszarze 2000-4000
        coorWall.x=(xMap*-1)+2000;
        SDL_RenderCopy(renderer,grass,NULL,&coorWall);
    }
}
void Play::close()
{
    //niszczenie wskaznikow
    SDL_DestroyTexture(wall);
    SDL_DestroyTexture(grass);
    for(int i=0; i<18; i++)
        SDL_DestroyTexture(palm[i]);
    Mix_FreeMusic(music);
}



Menu::Menu()
{
    //przypisywanie wartosci startowych
    menu=NULL;
    runner=NULL;
    info=NULL;
    play=NULL;
    exit=NULL;
    music=NULL;
    frame=0;
}
Menu::~Menu()
{
    //ustawianie wskaznikow na NULL'a
    menu=NULL;
    runner=NULL;
    info=NULL;
    play=NULL;
    exit=NULL;
    music=NULL;
}
bool Menu::loadMedia(SDL_Renderer* &renderer)
{
    bool success=true;

    //wczytywanie tla do menu
    menu=uni.loadMenuTexture("images/menu.png",renderer);
    if(menu==NULL)
    {
        printf("Nie odnaleziono menu.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    //ustawanie pozycji tla do menu
    coorMenu.w=1000;
    coorMenu.h=800;
    coorMenu.x=0;
    coorMenu.y=0;

    //wczytywanie grafiki nazwy gry
    runner=uni.loadMenuTexture("images/runner.png",renderer);
    if(runner==NULL)
    {
        printf("Nie odnaleziono runner.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    //ustawianie pozycji bannera runner
    coorRunner.w=737;
    coorRunner.h=187;
    coorRunner.x=145;
    coorRunner.y=38;

     //wczytywanie grafiki z informacjami
    info=uni.loadMenuTexture("images/info.png",renderer);
    if(info==NULL)
    {
        printf("Nie odnaleziono info.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    //ustawianie pozycji bannera info
    coorInfo.w=1000;
    coorInfo.h=555;
    coorInfo.x=0;
    coorInfo.y=245;

    //wczytywanie przycisku play
    play=uni.loadMenuTexture("images/play.png",renderer);
    if(play==NULL)
    {
        printf("Nie odnaleziono play.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    //ustawianie pozycji przycisku play
    coorPlay.w=353;
    coorPlay.h=147;
    coorPlay.x=237;
    coorPlay.y=258;

    //wczytywanie przycisku exit
    exit=uni.loadMenuTexture("images/exit.png",renderer);
    if(exit==NULL)
    {
        printf("Nie odnaleziono exit.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }

    //ustawianie pozycji przycisku exit
    coorExit.w=395;
    coorExit.h=147;
    coorExit.x=397;
    coorExit.y=468;

    //wczytywanie muzyki
    music=Mix_LoadMUS("music/menu.mp3");
    if(music==NULL)
    {
        printf("Cos poszlo nie tak z muzyka! SDL Error: %s\n",Mix_GetError());
        success=false;
    }

    character.loadMedia(renderer);
    coorChar.x=-400;
    coorChar.y=621;

    return success;
}
void Menu::present(SDL_Point mouseMotion, SDL_Point mouseDown, SDL_Renderer* &renderer)
{
    //odtwarza muzyke i wyswietla menu
    if(Mix_PlayingMusic()==0)
        Mix_PlayMusic( music, -1 );

    SDL_RenderCopy(renderer,menu,NULL,&coorMenu);
    character.present(coorChar,renderer);


    //gdy najedziemy myszka na runner
    if(mouseMotion.x>coorRunner.x && mouseMotion.x<coorRunner.x+coorRunner.w  &&  mouseMotion.y>coorRunner.y && mouseMotion.y<coorRunner.y+coorRunner.h)
    {
        SDL_RenderCopy(renderer,runner,NULL,&coorRunner);
        SDL_RenderCopy(renderer,info,NULL,&coorInfo);
    }

    //gdy najedziemy myszka na play
    if(mouseMotion.x>coorPlay.x && mouseMotion.x<coorPlay.x+coorPlay.w  &&  mouseMotion.y>coorPlay.y && mouseMotion.y<coorPlay.y+coorPlay.h)
    {
        SDL_RenderCopy(renderer,play,NULL,&coorPlay);
        if(mouseDown.x>coorPlay.x && mouseDown.x<coorPlay.x+coorPlay.w  &&  mouseDown.y>coorPlay.y && mouseDown.y<coorPlay.y+coorPlay.h)
        {
            coorChar.x=-400;
            frame=1;
            Mix_HaltMusic();
        }
    }

    //gdy najedziemy myszka na exit
    if(mouseMotion.x>coorExit.x && mouseMotion.x<coorExit.x+coorExit.w  &&  mouseMotion.y>coorExit.y && mouseMotion.y<coorExit.y+coorExit.h)
    {
        SDL_RenderCopy(renderer,exit,NULL,&coorExit);
        if(mouseDown.x>coorExit.x && mouseDown.x<coorExit.x+coorExit.w  &&  mouseDown.y>coorExit.y && mouseDown.y<coorExit.y+coorExit.h)
            SDL_Quit();
    }

    coorChar.x++;
    if(coorChar.x>1500)
        coorChar.x=-400;
}
void Menu::close()
{
    //niszczenie wskaznikow
    SDL_DestroyTexture(menu);
    SDL_DestroyTexture(runner);
    SDL_DestroyTexture(play);
    SDL_DestroyTexture(exit);
    Mix_FreeMusic(music);
}



Timer::Timer()
{
    //ustawianie wartosci startowych
    startTicks=0;
    started=false;
}
void Timer::start(SDL_Renderer* &renderer)
{
    //rozpoczynanie liczenia
    started=true;
    startTicks=SDL_GetTicks();

    //czyszczenie rendera
    SDL_SetRenderDrawColor(renderer,0,0,0,0xFF);
    SDL_RenderClear(renderer);
}
Uint32 Timer::getTicks()
{
    //pobieranie "chwil"
    Uint32 time=0;
    if(started)
        time=SDL_GetTicks()-startTicks;

    return time;
}



GameOver::GameOver()
{
    background=NULL;
    replay=NULL;
    menu=NULL;
    //music=NULL;
    frame=2;
}
GameOver::~GameOver()
{
    background=NULL;
    replay=NULL;
    menu=NULL;
    // music=NULL;
}
bool GameOver::loadMedia(SDL_Renderer* &renderer)
{
    bool success=true;

    background=uni.loadMenuTexture("images/gameover.png",renderer);
    if(background==NULL)
    {
        printf("Nie odnaleziono gameover.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    coorBack.w=1000;
    coorBack.h=800;
    coorBack.x=0;
    coorBack.y=0;

    replay=uni.loadMenuTexture("images/replay.png",renderer);
    if(replay==NULL)
    {
        printf("Nie odnaleziono replay.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    coorReplay.w=468;
    coorReplay.h=139;
    coorReplay.x=291;
    coorReplay.y=303;

    menu=uni.loadMenuTexture("images/menuB.png",renderer);
    if(menu==NULL)
    {
        printf("Nie odnaleziono menuB.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    coorMenu.w=362;
    coorMenu.h=137;
    coorMenu.x=309;
    coorMenu.y=491;


    /*music=Mix_LoadMUS("music/menu.mp3");
    if(music==NULL)
    {
        printf("Cos poszlo nie tak z muzyka! SDL Error: %s\n",Mix_GetError());
        success=false;
    }
    */

    return success;
}
void GameOver::present(SDL_Point mouseMotion, SDL_Point mouseDown, SDL_Renderer* &renderer)
{
    /*
    if(Mix_PlayingMusic()==0)
        Mix_PlayMusic( music, -1 );
    */

    SDL_RenderCopy(renderer,background,NULL,&coorBack);

    if(mouseMotion.x>coorMenu.x && mouseMotion.x<coorMenu.x+coorMenu.w  &&  mouseMotion.y>coorMenu.y && mouseMotion.y<coorMenu.y+coorMenu.h)
        SDL_RenderCopy(renderer,menu,NULL,&coorMenu);
    if(mouseDown.x>coorMenu.x && mouseDown.x<coorMenu.x+coorMenu.w  &&  mouseDown.y>coorMenu.y && mouseDown.y<coorMenu.y+coorMenu.h)
        frame=0;


    if(mouseMotion.x>coorReplay.x && mouseMotion.x<coorReplay.x+coorReplay.w  &&  mouseMotion.y>coorReplay.y && mouseMotion.y<coorReplay.y+coorReplay.h)
        SDL_RenderCopy(renderer,replay,NULL,&coorReplay);
    if(mouseDown.x>coorReplay.x && mouseDown.x<coorReplay.x+coorReplay.w  &&  mouseDown.y>coorReplay.y && mouseDown.y<coorReplay.y+coorReplay.h)
        frame=1;
}
void GameOver::close()
{
    //niszczenie wskaznikow
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(replay);
    SDL_DestroyTexture(menu);
    //Mix_FreeMusic(music);
}
