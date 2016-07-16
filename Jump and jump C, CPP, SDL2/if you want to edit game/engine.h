#pragma once

#include "core.h"
#include "loading.h"
#include "intro.h"
#include "menu.h"
#include "scores.h"
#include "storm.h"
#include "wall.h"
#include "hero.h"
#include "shuriken.h"
#include "defeat.h"
#include "heart.h"
#include "pause.h"
#include "points.h"
#include "options.h"
#include "enemy.h"

class Engine
{
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;

    Core* core;
    Loading* loading;
    Intro* intro;

    Menu* menu;
    Scores* scores;
    Options* options;

    Storm* storm;
    Wall* wall;

    Hero* hero;
    Shuriken* shuriken;

    Defeat* defeat;
    Hearts* hearts;
    Pause* pause;
    Points* points;

    Enemy* enemy;

public:

    Engine();
    bool load();
    void render();
    void handle();
    void free();

    bool init();
    void loop();
    void close();
};
