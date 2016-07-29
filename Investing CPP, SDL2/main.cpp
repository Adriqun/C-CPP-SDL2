#include "engine.h"
#include <stdio.h>

int main( int argc, char** argv )
{
    Engine* engine = new Engine;

    if( !engine->init() )
    {
        printf( "Engine could not initialize!\n" );
    }
    else if( !engine->load() )
    {
        printf( "Wrong load engine!\n" );
    }
    else
    {
        engine->loop();
    }

    delete engine;
    engine = NULL;

    return 0;
}
