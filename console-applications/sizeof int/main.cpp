#include <iostream>
#include <math.h>
#include <SDL.h>
using namespace std;

int main( int argc, char** argv )
{
    cout <<  pow( 2, ( sizeof( Uint16 ) * 8 ) ) -1 << endl;
    return 0;
}
