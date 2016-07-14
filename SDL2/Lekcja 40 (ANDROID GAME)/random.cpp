#include "random.h"
#include <cstdlib>
#include <time.h>

Random::Random()
{
    x = 0;
    y = 0;
}

Random::~Random()
{
    // brak ;)
}

int Random::getX()
{
    return x;
}

int Random::getY()
{
    return y;
}

void Random::initRandom()
{
    srand( time( NULL ) );
}

void Random::randomX( int startScope, int endScope )
{
    x = rand()%endScope + startScope;
}

void Random::randomY( int startScope, int endScope )
{
    y = rand()%endScope + startScope;
}
