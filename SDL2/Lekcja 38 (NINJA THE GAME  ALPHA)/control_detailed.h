#ifndef CONTROL_DETAILED_H
#define CONTROL_DETAILED_H

#include <SDL.h>
#include <string>

class Mouse
{
    friend class Control;

    bool down;
    SDL_Event event;
    SDL_Point point;

public:
    Mouse();
};

class Keyboard
{
    friend class Control;

    const Uint8* key;

public:
    Keyboard();
};

class NinjaC
{
    friend class Control;


    uint8_t counter, value, speed;

public:
    SDL_Rect rect;
    NinjaC();
};

class ShurikenC
{
    friend class Control;

    SDL_Rect rect;
    uint8_t counter, value, speed;

public:
    ShurikenC();
};

class BackgroundC
{
    friend class Control;

    SDL_Point point;
    uint8_t speed;

public:
    BackgroundC();
};

class ChartC
{
    friend class Control;

    SDL_Rect rect;
    uint8_t type;

public:
    ChartC();
};

#endif // CONTROL_DETAILED_H
