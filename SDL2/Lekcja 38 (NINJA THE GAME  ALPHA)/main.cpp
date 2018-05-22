#include "engine.h"

int main( int argc, char** argv )
{
    Engine engine;

    engine.start_program();
    engine.draw_program();
    engine.close_program();

    return 0;
}
