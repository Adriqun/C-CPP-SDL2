#include <cstdio>
#include "parser.h"

void yyerror(const char* msg)
{
	printf("Error: %s\n", msg);
}

// Syntax analyzer (parser).
extern int yyparse();

int main(int argc, char** argv)
{
	yyparse();

	return 0;
}
