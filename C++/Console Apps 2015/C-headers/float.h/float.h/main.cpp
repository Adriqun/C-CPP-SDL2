#include <iostream>
#include <float.h>

using namespace std;

int main()
{
    // makra z prezentacja decymalna

    cout << "FLT_RADIX: " << /*( char )*/ FLT_RADIX << '\n';

    cout << "FLT_MANT_DIG: " << FLT_MANT_DIG << '\n';
    cout << "DBL_MANT_DIG: " << DBL_MANT_DIG << '\n';
    cout << "LDBL_MANT_DIG: "<< LDBL_MANT_DIG << '\n';

    return 0;
}
