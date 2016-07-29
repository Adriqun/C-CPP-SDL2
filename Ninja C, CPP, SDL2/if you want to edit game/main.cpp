#include "engine.h"     //  init(), loop(), close()

#include <stdio.h>      //  printf()
#include <time.h>       //  time()
#include <stdlib.h>     //  srand()

int main( int argc, char** argv )
{
    srand( static_cast <int> (time( NULL )) );

    Engine engine;

    if( !engine.init() )
    {
        printf( "Program could not initialize!" );
    }
    else
    {
        engine.loop();
    }

    engine.close();

    return 0;
}
