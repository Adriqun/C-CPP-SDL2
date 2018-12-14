#include "console.h"

int getWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );

	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int getHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );

	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
