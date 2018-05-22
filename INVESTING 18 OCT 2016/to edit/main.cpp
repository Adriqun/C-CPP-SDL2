#include "engine.h"
#include <stdio.h>

int main( int argc, char** argv )
{
    Engine engine;

    if( !engine.load() )
    {
        printf( "Engine could not initialize!\n" );
    }
    else
    {
        engine.loop();
    }

    return 0;
}
