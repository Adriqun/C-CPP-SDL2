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
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 get_ticks();
    void set_fps();
};

#endif // TIMER_H
