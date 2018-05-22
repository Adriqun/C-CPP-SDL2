#include <stdio.h>
#include <math.h>
#include <errno.h>

void show_errno(void)
{
    printf( "WARNING - " ); // lub occured - wystapil
    if( errno == EDOM )   printf( "domain error" );
    if( errno == EILSEQ ) printf( "illegal sequence" );
    if( errno == ERANGE ) printf( "pole or range error" );
    if( errno == 0 )      printf( "no error" );
    printf( "\n" );
}

int main(void)
{
    errno = 0;
    1.0 / 0.0;
    show_errno();

    errno = 0;
    acos( +1.1 );
    show_errno();

    errno = 0;
    log( 0.0 );
    show_errno();

    errno = 0;
    sin( 0.0 );
    show_errno();
}

/*
#include <iostream>
#include <cmath>
#include <cerrno>
#include <cstring>

int main()
{
    double not_a_number = std::log( -1.0 );

    if( errno == EDOM )
    {
        std::cout << "log(-1) failed: " << std::strerror( errno ) << '\n';
    }

    double too_range = pow( 100000.0, 100000.0 );

    if( errno == ERANGE )
    {
        std::cout << "pow(-1) failed: " << std::strerror( errno ) << '\n';
    }
}
*/
