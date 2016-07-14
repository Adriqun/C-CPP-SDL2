#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <vector>
#include "universal.h"

#ifndef OPPONENTS_H
#define OPPONENTS_H
class Firework
{
    int nr;
    bool transparency;
    SDL_Texture* texture;
    SDL_Rect* spriteCoor, coor;
    Mix_Chunk* chunk;

public:
    Universal uni;
    Firework();
    ~Firework();
    void setVisible(int x, int y);
    bool loadMedia(std::string path, SDL_Renderer* &renderer);
    void present(SDL_Renderer* &renderer);
    void close();
};

class Fly1 //106x149
{
protected:
    Firework firework;
    SDL_Texture* texture;
    SDL_Rect* spriteCoor, coor;
    float coorX, coorY, speed;
    int cage;

public:
    int frame;

    Fly1();
    ~Fly1();
    void reload();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer);
    void close();
};
class Run2:public Fly1 //300x222
{
public:
    void reload();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer);
};
class Run1:public Fly1 //370x311
{
public:
    void reload();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer);
};
class Fly2:public Fly1 //372x314
{
public:
    void reload();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer);
};
class Fly3:public Fly1 //372x309
{
public:
    void reload();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer);
};
class Spike1:public Fly1 //368x354
{
public:
    void reload();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer);
};
class Spike2:public Fly1 //373x372
{
public:
    void reload();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer);
};
class Spider1:public Fly1 //208x116
{
public:
    void reload();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer);
};
class Bat1:public Fly1 //204x144
{
public:
    void reload();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer);
};
class Bat2:public Fly1 //366x188
{
public:
    void reload();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer);
};
class Enemy
{
    Run1 run1;
    Run2 run2;
    Fly1 fly1;
    Fly2 fly2;
    Fly3 fly3;
    Spike1 spike1;
    Spike2 spike2;
    Spider1 spider1;
    Bat1 bat1;
    Bat2 bat2;
    std::vector <Fly1> flyOne;
    std::vector <Fly2> flyTwo;
    std::vector <Fly3> flyThree;
    std::vector <Run1> runOne;
    std::vector <Run2> runTwo;
    std::vector <Spike1> spikeOne;
    std::vector <Spike2> spikeTwo;
    std::vector <Spider1> spiderOne;
    std::vector <Bat1> batOne;
    std::vector <Bat2> batTwo;

public:
    int frame;
    void loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point character, SDL_Point mouse, SDL_Renderer* &renderer, int meters);
    void close();
    void reload();
};
#endif
