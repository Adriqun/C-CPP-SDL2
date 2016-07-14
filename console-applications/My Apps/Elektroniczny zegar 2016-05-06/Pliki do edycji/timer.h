#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
    Uint32 fps;
    Uint32 startTicks;
    Uint32 pausedTicks;

    bool paused;
    bool started;

public:

    Timer( Uint32 _fps );

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 get_ticks();
    void present();
};

#endif // TIMER_H
