#include <iostream>
#include <math.h>
using namespace std;

int fast_atoi( std::string path )
{
    int num = 0, buf;

    for( uint8_t i = 0; i < path.length(); i++ )
    {
        buf = ( int ) path[ i ] - 48;
        for( uint8_t j = 1; j < path.length() - i; j++ )
            buf *= 10;
        num += buf;
    }
    return num;
}

long long int fast_pow( long long int num, long long int index )
{
    long long int buf = num;

    if( index == 0 )
        return 1;

    for( long long int i = 1; i < index; i++ )
        num *= buf;

    return num;
}

long long int fast_abs( long long int num )
{
    if( num >= 0 )
        return num;
    else
        return num * -1;
}

long double fast_fabs( long double num )
{
    if( num >= 0 )
        return num;
    else
        return num * -1;
}

int main()
{


    return 0;
}
