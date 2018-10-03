#include <stdio.h>
#include <stdarg.h>

void fprintf(const char* format, ...)
{
	va_list arg;
	va_start(arg, format);
	vfprintf(stdout, format, arg);
	va_end(arg);
}

int main()
{
	fprintf("Our Solar System has ");
	fprintf("%d planets\n", 8);
	
	return 0;
}