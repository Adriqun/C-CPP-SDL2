#pragma once

#include "core.h"
#include "title.h"
#include "goal.h"
#include "currency.h"
#include "attain.h"
#include "value.h"
#include "file.h"

class Engine
{
	Core* core;
	Title* title;
	Goal* goal;
	Currency* currency;
	Attain* attain;
	Value* value;
	File* file;
	
public:
	
	Engine();
	~Engine();
	void free();
	
	bool load();
	void handle();
	void draw();
	void loop();
};