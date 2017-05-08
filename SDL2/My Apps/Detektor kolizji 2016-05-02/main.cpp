#include "engine.h"
#include <stdio.h>

int main( int argc, char** argv )
{
    /* Tu tworzymy silnik z wszystkimi obiektami */
    Engine engine;

    // inicjowanie programu
    if( !engine.init() )
    {
        printf( "Nie zainicjowano programu!\n" );
    }
    else
    {
        // renderowanie programu
        engine.render();
    }

    return 0;
}
