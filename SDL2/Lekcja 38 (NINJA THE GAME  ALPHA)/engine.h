#ifndef ENGINE_H
#define ENGINE_H

#include "core.h"
#include "timer.h"
#include "control.h"
#include "ninja.h"
#include "background.h"
#include "map_editor.h"
#include "engine_intro.h"

using namespace core;

class Engine
{
    // glowne zmienne
    int8_t frame;
    SDL_Renderer* renderer;
    SDL_Window* window;

    Intro intro;
    Control control;
    Background background;
    Chart chart;
    Ninja ninja;
    Shuriken shuriken;


    // zmienne "szczegolowe"
    void load_images();
    void load_music();
    void load_fonts();
    void load_files();
    void close_objects();

public:
    Engine();

    // zmienne "gupujace" - "ogolne"
    void start_program();
    void draw_program();
    void close_program();
};

#endif // ENGINE_H
