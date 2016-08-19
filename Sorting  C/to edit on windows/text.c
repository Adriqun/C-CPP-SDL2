#include "text.h"
#include <stdio.h>


void centre( int w, char* s )
{
	unsigned long len = strlen( s );
	int nr = ( w - len ) /2;

	for( int i = 0; i < nr; ++i )
	{
		printf( " " );
	}

	printf( "%s", s );
}
