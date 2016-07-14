#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "universal.h"
#include "character.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H
class Play //2000x800
{
    Universal uni;
    SDL_Texture* wall;
    SDL_Texture* grass;
    SDL_Texture* palm[18];
    SDL_Rect coorWall;
    SDL_Rect coorPalm[5];
    int random[5];
    Mix_Music* music;

public:
    Play();
    ~Play();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Renderer* &renderer, int xMap, int frame);
    void close();
};
class Menu //1000x800
{
    SDL_Point coorChar;
    Character character;

    SDL_Texture* runner;
    SDL_Rect coorRunner;

    SDL_Texture* info;
    SDL_Rect coorInfo;

    SDL_Texture* menu;
    SDL_Rect coorMenu;

    SDL_Texture* play;
    SDL_Rect coorPlay;

    SDL_Texture* exit;
    SDL_Rect coorExit;

    Mix_Music* music;
    Universal uni;

public:
    int frame;
    Menu();
    ~Menu();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point mouseMotion, SDL_Point mouseDown, SDL_Renderer* &renderer);
    void close();
};
class Timer //*x*
{
    Uint32 startTicks;
    bool started;

public:
    Timer();
    void start(SDL_Renderer* &renderer);
    Uint32 getTicks();
};
class GameOver //1000x800
{
    SDL_Texture* background;
    SDL_Rect coorBack;

    SDL_Texture* replay;
    SDL_Rect coorReplay;

    SDL_Texture* menu;
    SDL_Rect coorMenu;

    //Mix_Music* music;
    Universal uni;

public:
    int frame;
    GameOver();
    ~GameOver();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point mouseMotion, SDL_Point mouseDown, SDL_Renderer* &renderer);
    void close();
};
#endif
