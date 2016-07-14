#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "opponents.h"
#include "universal.h"

Fly1::Fly1()
{
    texture=NULL;
    frame=1;
}
Fly1::~Fly1()
{
    texture=NULL;
    spriteCoor=NULL;
}
bool Fly1::loadMedia(SDL_Renderer* &renderer)
{
    srand(time(NULL));
    bool success=true;

    texture=firework.uni.loadTexture("images/fly1.png",renderer);
    if(texture==NULL)
    {
        printf("Nie odnaleziono fly1.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    cage=4;
    speed=2.5;
    spriteCoor=new SDL_Rect[4];
    reload();
    coor.w=185;
    coor.h=155.5;

    for(int i=0; i<4; i++)
    {
        spriteCoor[i].y=0;
        spriteCoor[i].w=370;
        spriteCoor[i].h=311;
        spriteCoor[i].x=370*i;
    }

    firework.loadMedia("images/boomFly1.png",renderer);

    return success;
}
void Fly1::present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer)
{
    coorX-=speed*cos(atan2(coor.y - character.y, coor.x - character.x));
    coorY-=speed*sin(atan2(coor.y - character.y, coor.x - character.x));
    coor.x=coorX;
    coor.y=coorY;

    if(mouse.x<(coor.x+coor.w+30) && mouse.x>coor.x-30 && mouse.y<(coor.y+coor.h+30) && mouse.y>coor.y-30)
    {
        firework.setVisible(coorX,coorY);
        reload();
    }
    if(character.x<(coor.x+coor.w) && character.x+50>coor.x && character.y<(coor.y+coor.h) && character.y+75>coor.y)
    {
        reload();
        frame=2;
    }
    else
        frame=1;

    firework.present(renderer);
    SDL_RenderCopyEx(renderer,texture,&spriteCoor[firework.uni.counter(cage-1,12)/12],&coor,(atan2(coor.y - character.y, coor.x - character.x)*180/M_PI),NULL,SDL_FLIP_NONE);
}
void Fly1::close()
{
    //niszczenie wskaznikow
    SDL_DestroyTexture(texture);
    delete [] spriteCoor;
    firework.close();
}
void Fly1::reload()
{
    coorX=(std::rand()%1200)+1800;
    coorY=((std::rand()%200)+400)*-1;
}



bool Fly2::loadMedia(SDL_Renderer* &renderer)
{
    srand(time(NULL));
    bool success=true;

    texture=firework.uni.loadTexture("images/fly2.png",renderer);
    if(texture==NULL)
    {
        printf("Nie odnaleziono fly2.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    cage=6;
    speed=2;
    spriteCoor=new SDL_Rect[6];

    coor.w=186;
    coor.h=157;
    reload();

    for(int i=0; i<6; i++)
    {
        spriteCoor[i].y=0;
        spriteCoor[i].w=372;
        spriteCoor[i].h=314;
        spriteCoor[i].x=372*i;
    }
    firework.loadMedia("images/boomFly2.png",renderer);

    return success;
}
void Fly2::present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer)
{
    coorX-=speed*cos(atan2(coor.y - character.y, coor.x - character.x));
    coorY-=speed*sin(atan2(coor.y - character.y, coor.x - character.x));
    coor.x=coorX;
    coor.y=coorY;

    if(mouse.x<(coor.x+coor.w+30) && mouse.x>coor.x-30 && mouse.y<(coor.y+coor.h+30) && mouse.y>coor.y-30)
    {
        firework.setVisible(coorX,coorY);
        reload();
    }
    if(character.x<(coor.x+coor.w) && character.x+50>coor.x && character.y<(coor.y+coor.h) && character.y+75>coor.y)
    {
        reload();
        frame=2;
    }
    else
        frame=1;

    firework.present(renderer);
    SDL_RenderCopyEx(renderer,texture,&spriteCoor[firework.uni.counter(cage-1,18)/18],&coor,(atan2(coor.y - character.y, coor.x - character.x)*180/M_PI),NULL,SDL_FLIP_NONE);
}
void Fly2::reload()
{
    coorX=(std::rand()%-1200)-1800;
    coorY=(std::rand()%640);
}
bool Fly3::loadMedia(SDL_Renderer* &renderer)
{
    srand(time(NULL));
    bool success=true;

    texture=firework.uni.loadTexture("images/fly3.png",renderer);
    if(texture==NULL)
    {
        printf("Nie odnaleziono fly3.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    cage=6;
    speed=4;
    spriteCoor=new SDL_Rect[6];

    coor.w=186;
    coor.h=154.5;
    reload();

    for(int i=0; i<6; i++)
    {
        spriteCoor[i].y=0;
        spriteCoor[i].w=372;
        spriteCoor[i].h=309;
        spriteCoor[i].x=372*i;
    }
    firework.loadMedia("images/boomFly3.png",renderer);

    return success;
}
void Fly3::present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer)
{
    coorX-=speed*cos(atan2(coor.y - character.y, coor.x - character.x));
    coorY-=speed*sin(atan2(coor.y - character.y, coor.x - character.x));
    coor.x=coorX;
    coor.y=coorY;

    if(mouse.x<(coor.x+coor.w+30) && mouse.x>coor.x-30 && mouse.y<(coor.y+coor.h+30) && mouse.y>coor.y-30)
    {
        firework.setVisible(coorX,coorY);
        reload();
    }
    if(character.x<(coor.x+coor.w) && character.x+50>coor.x && character.y<(coor.y+coor.h) && character.y+75>coor.y)
    {
        reload();
        frame=2;
    }
    else
        frame=1;

    firework.present(renderer);
    SDL_RenderCopyEx(renderer,texture,&spriteCoor[firework.uni.counter(cage-1,5)/5],&coor,(atan2(coor.y - character.y, coor.x - character.x)*180/M_PI),NULL,SDL_FLIP_NONE);
}
void Fly3::reload()
{
    coorX=(std::rand()%1200)+1800;
    coorY=(std::rand()%640);
}



bool Run1::loadMedia(SDL_Renderer* &renderer)
{
    srand(time(NULL));
    bool success=true;

    //wczytywanie przeciwnika
    texture=firework.uni.loadTexture("images/run1.png",renderer);
    if(texture==NULL)
    {
        printf("Nie odnaleziono run1.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }

    //dynamiczne alokowanie pamieci dla wspolrzednych, ustawianie wspolrzednych
    cage=8;
    speed=1;
    spriteCoor=new SDL_Rect[8];

    //punkt startowy oraz rozmiary
    coor.w=106;
    coor.h=149;
    reload();

    //uzupelnianie gdzie znajduje sie dany fragment grafiki
    for(int i=0; i<8; i++)
    {
        spriteCoor[i].y=0;
        spriteCoor[i].w=106;
        spriteCoor[i].h=149;
        spriteCoor[i].x=106*i;
    }
    firework.loadMedia("images/boomRun1.png",renderer);

    return success;
}
void Run1::present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer)
{
    coor.x--;
    if(coor.x<-200)
        reload();
    if(mouse.x<(coor.x+coor.w+30) && mouse.x>coor.x-30 && mouse.y<(coor.y+coor.h+30) && mouse.y>coor.y-30)
    {
        firework.setVisible(coor.x,coor.y);
        reload();
    }
    if(character.x<(coor.x+coor.w) && character.x+50>coor.x && character.y<(coor.y+coor.h) && character.y+75>coor.y)
    {
        reload();
        frame=2;
    }
    else
        frame=1;

    firework.present(renderer);
    SDL_RenderCopyEx(renderer,texture,&spriteCoor[firework.uni.counter(cage-1,24)/24],&coor,0,NULL,SDL_FLIP_NONE);
}
void Run1::reload()
{
    coor.x=(std::rand()%1200)+1800;
    coor.y=651;
}
bool Run2::loadMedia(SDL_Renderer* &renderer)
{
    srand(time(NULL));
    bool success=true;

    texture=firework.uni.loadTexture("images/run2.png",renderer);
    if(texture==NULL)
    {
        printf("Nie odnaleziono run2.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    cage=8;
    spriteCoor=new SDL_Rect[8];

    coor.w=150;
    coor.h=111;
    reload();

    for(int i=0; i<8; i++)
    {
        spriteCoor[i].y=0;
        spriteCoor[i].w=300;
        spriteCoor[i].h=222;
        spriteCoor[i].x=300*i;
    }

    return success;
}
void Run2::present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer)
{
    coor.x--;
    if(coor.x<-200)
        reload();
    if(character.x<(coor.x+coor.w) && character.x+30>coor.x && character.y<(coor.y+coor.h) && character.y+60>coor.y)
    {
        reload();
        frame=2;
    }
    else
        frame=1;
    SDL_RenderCopyEx(renderer,texture,&spriteCoor[firework.uni.counter(cage-1,24)/24],&coor,0,NULL,SDL_FLIP_NONE);
}
void Run2::reload()
{
    coor.x=(std::rand()%1200)+1800;
    coor.y=689;
}


bool Spike1::loadMedia(SDL_Renderer* &renderer)
{
    srand(time(NULL));
    bool success=true;

    texture=firework.uni.loadTexture("images/spike1.png",renderer);
    if(texture==NULL)
    {
        printf("Nie odnaleziono spike1.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    cage=7;
    speed=1.5;
    spriteCoor=new SDL_Rect[7];

    coor.w=184;
    coor.h=177;
    reload();

    for(int i=0; i<7; i++)
    {
        spriteCoor[i].y=0;
        spriteCoor[i].w=368;
        spriteCoor[i].h=354;
        spriteCoor[i].x=368*i;
    }
    firework.loadMedia("images/boomSpike1.png",renderer);

    return success;
}
void Spike1::present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer)
{
    coorX-=speed*cos(atan2(coor.y - character.y, coor.x - character.x));
    coorY-=speed*sin(atan2(coor.y - character.y, coor.x - character.x));
    coor.x=coorX;
    coor.y=coorY;

    if(mouse.x<(coor.x+coor.w+30) && mouse.x>coor.x-30 && mouse.y<(coor.y+coor.h+30) && mouse.y>coor.y-30)
    {
        firework.setVisible(coorX,coorY);
        reload();
    }
    if(character.x<(coor.x+coor.w) && character.x+50>coor.x && character.y<(coor.y+coor.h) && character.y+75>coor.y)
    {
        reload();
        frame=2;
    }
    else
        frame=1;

    firework.present(renderer);
    SDL_RenderCopyEx(renderer,texture,&spriteCoor[firework.uni.counter(cage-1,21)/21],&coor,0,NULL,SDL_FLIP_VERTICAL);
}
void Spike1::reload()
{
    coorX=(std::rand()%-1200)-1800;
    coorY=(std::rand()%20)+500;
}
bool Spike2::loadMedia(SDL_Renderer* &renderer)
{
    srand(time(NULL));
    bool success=true;

    texture=firework.uni.loadTexture("images/spike2.png",renderer);
    if(texture==NULL)
    {
        printf("Nie odnaleziono spike2.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    cage=8;
    speed=1.5;
    spriteCoor=new SDL_Rect[8];

    coor.w=186.5;
    coor.h=186;
    reload();

    for(int i=0; i<8; i++)
    {
        spriteCoor[i].y=0;
        spriteCoor[i].w=373;
        spriteCoor[i].h=372;
        spriteCoor[i].x=373*i;
    }

    return success;
}
void Spike2::present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer)
{
    coor.x--;
    if(coor.x<-300)
        reload();

    if(character.x<(coor.x+coor.w) && character.x+50>coor.x && character.y<(coor.y+coor.h) && character.y+60>coor.y)
    {
        reload();
        frame=2;
    }
    else
        frame=1;

    SDL_RenderCopyEx(renderer,texture,&spriteCoor[firework.uni.counter(cage-1,2)/2],&coor,0,NULL,SDL_FLIP_NONE);
}
void Spike2::reload()
{
    coor.x=(std::rand()%1000)+3000;
    coor.y=614;
}


bool Spider1::loadMedia(SDL_Renderer* &renderer)
{
    srand(time(NULL));
    bool success=true;

    texture=firework.uni.loadTexture("images/spider1.png",renderer);
    if(texture==NULL)
    {
        printf("Nie odnaleziono spider1.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    cage=6;
    speed=2;
    spriteCoor=new SDL_Rect[6];

    coor.w=208;
    coor.h=116;
    reload();

    for(int i=0; i<6; i++)
    {
        spriteCoor[i].y=0;
        spriteCoor[i].w=208;
        spriteCoor[i].h=116;
        spriteCoor[i].x=208*i;
    }
    firework.loadMedia("images/boomSpider1.png",renderer);

    return success;
}
void Spider1::present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer)
{
    coorX-=speed*cos(atan2(coor.y - character.y, coor.x - character.x));
    coorY-=speed*sin(atan2(coor.y - character.y, coor.x - character.x));
    coor.x=coorX;
    coor.y=coorY;

    if(mouse.x<(coor.x+coor.w+30) && mouse.x>coor.x-30 && mouse.y<(coor.y+coor.h+30) && mouse.y>coor.y-30)
    {
        firework.setVisible(coorX,coorY);
        reload();
    }
    if(character.x<(coor.x+coor.w) && character.x+50>coor.x && character.y<(coor.y+coor.h) && character.y+75>coor.y)
    {
        reload();
        frame=2;
    }
    else
        frame=1;

    firework.present(renderer);
    SDL_RenderCopyEx(renderer,texture,&spriteCoor[firework.uni.counter(cage-1,18)/18],&coor,(atan2(coor.y - character.y, coor.x - character.x)*180/M_PI),NULL,SDL_FLIP_NONE);
}
void Spider1::reload()
{
    coorX=(std::rand()%-1200)-1800;
    coorY=(std::rand()%-1200)-1800;
}


bool Bat1::loadMedia(SDL_Renderer* &renderer)
{
    srand(time(NULL));
    bool success=true;

    texture=firework.uni.loadTexture("images/bat1.png",renderer);
    if(texture==NULL)
    {
        printf("Nie odnaleziono bat1.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    cage=4;
    speed=4;
    spriteCoor=new SDL_Rect[4];

    coor.w=205.25;
    coor.h=144;
    reload();

    for(int i=0; i<4; i++)
    {
        spriteCoor[i].y=0;
        spriteCoor[i].w=205.25;
        spriteCoor[i].h=144;
        spriteCoor[i].x=205.25*i;
    }
    firework.loadMedia("images/boomBat1.png",renderer);

    return success;
}
void Bat1::present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer)
{
    coorX-=speed*cos(atan2(coor.y - character.y, coor.x - character.x));
    coorY-=speed*sin(atan2(coor.y - character.y, coor.x - character.x));
    coor.x=coorX;
    coor.y=coorY;

    if(mouse.x<(coor.x+coor.w+30) && mouse.x>coor.x-30 && mouse.y<(coor.y+coor.h+30) && mouse.y>coor.y-30)
    {
        firework.setVisible(coorX,coorY);
        reload();
    }
    if(character.x<(coor.x+coor.w) && character.x+50>coor.x && character.y<(coor.y+coor.h) && character.y+75>coor.y)
    {
        reload();
        frame=2;
    }
    else
        frame=1;

    firework.present(renderer);
    SDL_RenderCopyEx(renderer,texture,&spriteCoor[firework.uni.counter(cage-1,12)/12],&coor,(atan2(coor.y - character.y, coor.x - character.x)*180/M_PI),NULL,SDL_FLIP_NONE);
}
void Bat1::reload()
{
    coorX=((std::rand()%100)+600)*-1;
    coorY=((std::rand()%100)+600)*-1;
}
bool Bat2::loadMedia(SDL_Renderer* &renderer)
{
    srand(time(NULL));
    bool success=true;

    texture=firework.uni.loadTexture("images/bat2.png",renderer);
    if(texture==NULL)
    {
        printf("Nie odnaleziono bat2.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }
    cage=8;
    speed=2;
    spriteCoor=new SDL_Rect[8];

    coor.w=183;
    coor.h=94;
    reload();

    for(int i=0; i<8; i++)
    {
        spriteCoor[i].y=0;
        spriteCoor[i].w=366;
        spriteCoor[i].h=188;
        spriteCoor[i].x=366*i;
    }
    firework.loadMedia("images/boomBat2.png",renderer);

    return success;
}
void Bat2::present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer)
{
    coorX-=speed*cos(atan2(coor.y - character.y, coor.x - character.x));
    coorY-=speed*sin(atan2(coor.y - character.y, coor.x - character.x));
    coor.x=coorX;
    coor.y=coorY;

    if(mouse.x<(coor.x+coor.w+30) && mouse.x>coor.x-30 && mouse.y<(coor.y+coor.h+30) && mouse.y>coor.y-30)
    {
        firework.setVisible(coorX,coorY);
        reload();
    }
    if(character.x<(coor.x+coor.w) && character.x+50>coor.x && character.y<(coor.y+coor.h) && character.y+75>coor.y)
    {
        reload();
        frame=2;
    }
    else
        frame=1;

    firework.present(renderer);
    SDL_RenderCopyEx(renderer,texture,&spriteCoor[firework.uni.counter(cage-1,14)/14],&coor,0,NULL,SDL_FLIP_NONE);
}
void Bat2::reload()
{
    coorX=(std::rand()%1000);
    coorY=(std::rand()%1000)*-1;
}



Firework::Firework()
{
    nr=0;
    transparency=false;
    texture=NULL;
    chunk=NULL;
}
Firework::~Firework()
{
    texture=NULL;
    chunk=NULL;
    spriteCoor=NULL;
}
void Firework::setVisible(int x, int y)
{
    Mix_PlayChannel( -1, chunk, 0 );
    transparency=true;
    coor.x=x;
    coor.y=y;
}
bool Firework::loadMedia(std::string path, SDL_Renderer* &renderer)
{
    bool success=true;

    texture=uni.loadTexture(path.c_str(), renderer);
    if(texture==NULL)
    {
        printf("Nie udalo sie wczytac %s!", path.c_str());
        success=false;
    }
    else
    {
        spriteCoor = new SDL_Rect [5];
        for(int i=0; i<5; i++)
        {
            spriteCoor[i].y=0;
            spriteCoor[i].w=408;
            spriteCoor[i].h=350;
            spriteCoor[i].x=408*i;
        }
        coor.w=204;
        coor.h=175;
    }

    chunk=Mix_LoadWAV("music/a.wav");
    if(chunk==NULL)
    {
        printf("Nie udalo sie wczytac a.wav!");
        success=false;
    }

    return success;
}
void Firework::present(SDL_Renderer* &renderer)
{
    if(transparency==true)
    {
        SDL_RenderCopy(renderer,texture,&spriteCoor[nr/5],&coor);
        if(nr==20)
        {
            transparency=false;
            nr=0;
        }
        nr++;
    }
}
void Firework::close()
{
    SDL_DestroyTexture(texture);
    delete [] spriteCoor;
    Mix_FreeChunk(chunk);
}

void Enemy::loadMedia(SDL_Renderer* &renderer)
{
    frame=1;
    run1.loadMedia(renderer);
    run2.loadMedia(renderer);
    fly1.loadMedia(renderer);
    fly2.loadMedia(renderer);
    fly3.loadMedia(renderer);
    spike1.loadMedia(renderer);
    spike2.loadMedia(renderer);
    spider1.loadMedia(renderer);
    bat1.loadMedia(renderer);
    bat2.loadMedia(renderer);

    for(int i=0; i<100; i++)
    {
        flyOne.push_back(fly1);
        flyTwo.push_back(fly2);
        flyThree.push_back(fly3);
        runOne.push_back(run1);
        runTwo.push_back(run2);
        spikeOne.push_back(spike1);
        spikeTwo.push_back(spike2);
        spiderOne.push_back(spider1);
        batOne.push_back(bat1);
        batTwo.push_back(bat2);
    }
}
void Enemy::present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer, int meters)
{
    for(int i=0; i<(meters/500)+1; i++)
    {
        flyOne[i].present(character,mouse,renderer);
        if(meters>250)
            flyTwo[i].present(character,mouse,renderer);
        if(meters>300)
            flyThree[i].present(character,mouse,renderer);
        if(meters>400)
            runOne[i].present(character,mouse,renderer);
        if(meters>10000)
            runTwo[i].present(character,mouse,renderer);
        if(meters>550)
            spiderOne[i].present(character,mouse,renderer);
        if(meters>400)
            spikeOne[i].present(character,mouse,renderer);
        if(meters>400)
            spikeTwo[i].present(character,mouse,renderer);
        if(meters>750)
            batOne[i].present(character,mouse,renderer);
        if(meters>100)
            batTwo[i].present(character,mouse,renderer);
        if(flyOne[i].frame==2||flyTwo[i].frame==2||flyThree[i].frame==2||runOne[i].frame==2||runTwo[i].frame==2||batOne[i].frame==2||batTwo[i].frame==2||spiderOne[i].frame==2||spikeOne[i].frame==2||spikeTwo[i].frame==2)
            {
                Mix_HaltMusic();
                frame=2;
            }
    }
}
void Enemy::close()
{
    run1.close();
    run2.close();
    fly1.close();
    fly2.close();
    fly3.close();
    spike1.close();
    spike2.close();
    spider1.close();
    bat1.close();
    bat2.close();

    flyOne.clear();
    flyTwo.clear();
    flyThree.clear();
    spikeOne.clear();
    spikeTwo.clear();
    batOne.clear();
    batTwo.clear();
    runOne.clear();
    runTwo.clear();
    spiderOne.clear();
}
void Enemy::reload()
{
    run1.reload();
    run2.reload();
    fly1.reload();
    fly2.reload();
    fly3.reload();
    spike1.reload();
    spike2.reload();
    spider1.reload();
    bat1.reload();
    bat2.reload();
}
