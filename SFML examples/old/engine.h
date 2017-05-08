#pragma once

#include "core.h"
#include "templates/sprite.h"

class Engine
{
    Core* core;
	int x, y; // mouse x, y;
	MySprite* sprite;

public:

    Engine();
    ~Engine();

    void free();
    void load();

    void events();
    void states();

    void loop();
};
