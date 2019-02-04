#include <stdio.h>
#include <math.h>

int main()
{
    // You get a represeting float value of const char* value
    const char* value = "b";
    float nr = nan( value );

    printf( "%f", nr );

    return 0;
}
