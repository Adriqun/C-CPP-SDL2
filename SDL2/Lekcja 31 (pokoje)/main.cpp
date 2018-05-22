#include "core.h"

int main( int argc, char** argv )
{
    Core core;

    core.init();
    core.load();
    core.renderAll();
    core.close();

    return 0;
}
