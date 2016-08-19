#include "console.h"

int getWidth()
{
	struct winsize window;
    ioctl( STDOUT_FILENO, TIOCGWINSZ, &window );
	return window.ws_col;
}

int getHeight()
{
	struct winsize window;
    ioctl( STDOUT_FILENO, TIOCGWINSZ, &window );
	return window.ws_row;
}