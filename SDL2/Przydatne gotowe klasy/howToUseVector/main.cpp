#include "engine.h"
#include <stdio.h>

int main( int argc, char** argv )
{
    Engine engine;
    if( !engine.init() )
    {
        printf( "Nie zainicjowano programu!\n" );
    }
    else
    {
        engine.render();
    }

    return 0;
}
