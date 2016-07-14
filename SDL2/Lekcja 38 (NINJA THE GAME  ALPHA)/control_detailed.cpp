#include "control_detailed.h"

Mouse::Mouse()
{
    point.x =   0;
    point.y =   0;

    down =  false;
}

Keyboard::Keyboard()
{
    key = SDL_GetKeyboardState( NULL );
}

NinjaC::NinjaC()
{
    rect.h = 72;
    rect.w = 72;
    rect.x = 0;
    rect.y = 520 + 26;
    counter = 0;
    value = 0;
    speed = 8;
}

ShurikenC::ShurikenC()
{
    rect.h = 28;
    rect.w = 28;
    rect.x = 0;
    rect.y = 540 + 26;
    counter = 0;
    value = 0;
    speed = 16;
}

BackgroundC::BackgroundC()
{
    point.x = 0;
    point.y = 0;
    speed = 5;
}

ChartC::ChartC()
{
    rect.x = 0;
    rect.y = 0;
    rect.h = 128;
    rect.w = 128;
    type = 0;
}
