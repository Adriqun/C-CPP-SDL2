#include "global.h"

class Control //bez destruktora
{
    Uint8 state;
    /*
    state = 0 -> brak ruchu
    state = 1 -> pilka leci w prawo w gore
    state = 2 -> pilka leci w prawo w dol
    state = 3 -> pilka leci w lewo w gore
    state = 4 -> pilka leci w lewo w dol
    */
    bool counter;
    float ball_speed;

public:
    SDL_Rect board_one;
    SDL_Rect board_two;
    SDL_Rect ball;
    SDL_Point mouse;
    SDL_Rect play, exit, reset, menu;

    Control();
    bool load();
    void mouse_control();
    void keys_control();
    void ball_control();
    void collision();
};
