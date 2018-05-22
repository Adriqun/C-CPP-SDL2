#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>	// GetConsoleScreenBufferInfo
#include <stdio.h>
#include <unistd.h>		// usleep
#include <time.h>	// clock_t

int getWidth();
int getHeight();

#endif // CONSOLE_H
