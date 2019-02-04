/* fesetround example */
#include <stdio.h>      /* printf */
#include <fenv.h>       /* fesetround, FE_* */
#include <math.h>       /* rint */
#pragma STDC FENV_ACCESS on

int main ()
{
    printf ( "rounding -3.8:\n" );

    fesetround( FE_DOWNWARD ); // zaokragla do dolu 2.3 -> 2, -2.5 -> -3
    printf( "FE_DOWNWARD: %.1f\n", rint( -3.8 ) );

    fesetround( FE_UPWARD ); // zaokragla do gory 2.3 -> 3, -2.5 -> -2
    printf( "FE_UPWARD: %.1f\n", rint( -3.8 ) );

    fesetround( FE_TONEAREST ); // zaokgragla do najblizszej
    printf( "FE_TONEAREST: %.1f\n", rint( -3.8 ) );

    fesetround( FE_TOWARDZERO ); // odwrotnosc fe_tonearest
    printf( "FE_TOWARDZERO: %.1f\n", rint( -3.8 ) );

    return 0;
}
