#ifndef DETECTOR_H
#define DETECTOR_H

#include <SDL.h>

class Detector
{
    Uint8 visible;
    Uint8 counter;

public:

    Detector();
    Uint8 checkCollision( SDL_Rect a, SDL_Rect b );
};

#endif // DETECTOR_H
