#include "engine.h"

int main( int argc, char **argv )
{
    Engine engine;

    engine.startProgram();
    engine.renderProgram();
    engine.closeProgram();

    return 0;
}
