#include "global.h"

class Keyboard
{
    SDL_Event e;
    const Uint8* key;

    Uint8 vel;
    Uint8 velBall;
    /* STANY PILKI
    1 = W PRAWO DO GORY
    2 = W PRAWO W DOL
    3 = W LEWO DO GORY
    4 = W LEWO W DOL
    */

public:

    SDL_Rect floor;
    SDL_Rect ball;
    Uint8 state;
    SDL_Point point;
    bool click;
    bool defeat;

    Keyboard();
    ~Keyboard();
    bool load();
    void keys();
    void mouse();
    void collision();
};
