#ifndef CONTROL_GLOBAL_H
#define CONTROL_GLOBAL_H

#include "control_detailed.h"

class Control
{
    Mouse mouse;
    Keyboard keyboard;


    ShurikenC shurikenC;

    BackgroundC backgroundC;
    ChartC chartC;

public:
    NinjaC ninjaC;
    uint16_t screen_width;
    uint16_t screen_height;

    Control();
    void close();

    // bg
    SDL_Point get_background_point();

    // ninja i shuriken
    void ninja_mouse_control();
    void ninja_keyboard_control();
    SDL_Rect get_ninja_rect();
    SDL_Rect get_shuriken_rect();
    uint8_t get_ninja_value();
    uint8_t get_shuriken_value();

    // mapa, edytor mapy
    void map_keyboard_control();
    std::string int_to_string( int n );
    std::string get_block();
    SDL_Point get_map_mouse_point();
    SDL_Rect get_map_rect();
    uint8_t get_type_block();

    //system kolizji
    void check_collision( SDL_Rect &a, SDL_Rect b );
};

#endif // CONTROL_GLOBAL_H
