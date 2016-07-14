#ifndef DETECTOR_H
#define DETECTOR_H

#include <SDL.h>

class Detector
{

public:

    bool checkCollision( SDL_Rect &a, SDL_Rect &b );
    SDL_Rect setRect( SDL_Rect a, SDL_Rect b, Uint16 &w, Uint16 &h, float velX, float velY );
};

#endif // DETECTOR_H
