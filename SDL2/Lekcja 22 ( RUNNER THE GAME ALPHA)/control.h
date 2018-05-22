#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <sstream>
#include "universal.h"

#ifndef CONTROL_H
#define COTROL_H
class Control
{
public:
    SDL_Event event;
    SDL_Point mouseMotion, mouseDown, character, map;
    bool jump, jumpUp;

    Universal uni;
    SDL_Texture* cursor;
    SDL_Rect coorCursor;

    const Uint8* state;//klawisze
    float meters;

    Control();
    void mouseControl();
    void keysControl(int frame);
    void loadCursor(SDL_Renderer* &renderer);
    void close();
    void resetMousePosition(int &x);
};
class Meters
{
    std::string str;
    std::ostringstream ss;
    TTF_Font* font;
    SDL_Texture* textTexture;
    SDL_Surface* surface;
    SDL_Rect rect;
    SDL_Color color;
    int endMeters;
    SDL_Rect coorEndMeters;

public:
    Meters();
    ~Meters();
    SDL_Texture* loadFromRenderedText(std::string path, SDL_Renderer* &renderer);
    bool loadMedia(SDL_Renderer* &renderer);
    void presentMeters(SDL_Renderer* &renderer, int x);
    void presentEndMeters(SDL_Renderer* &renderer);
    void close();
};
#endif
