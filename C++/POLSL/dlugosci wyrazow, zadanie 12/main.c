#include "interpreter.h"
#include <stdio.h> // printf()

int main(int argc, char** argv)
{
	// parse, load file and evaluate
	Interpreter inter;
	init(&inter);
	if (parse(&argc, &argv, &inter))
		if (loadFile(&inter))
			evaluate(&inter);

	// free
	freeHeads(inter.pHeads);
	freeBuffers(&inter.pcInput, &inter.pcOutput);

	// end
	printf("Press enter to continue...\n");
	{
		char c = 0;
		while (c != '\r' && c != '\n')
			c = getchar();
	}

	// return success code
	return 0;
}
