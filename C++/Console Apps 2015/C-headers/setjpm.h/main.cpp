#include <stdio.h>      /* printf */
#include <setjmp.h>     /* jmp_buf, setjmp, longjmp */

int main()
{
    jmp_buf env;
    int val;

    val = setjmp( env );

    printf( "Powtorka nr: %d\n", val );

    if( val < 10 )
        longjmp( env, val + 1 );

    return 0;
}
