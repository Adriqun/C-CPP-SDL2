#include <iostream>

using namespace std;

int main()
{
    // wyliczac

    enum liczby
    {
        KOT = 0,
        PIES,
        CZILALA
    };

    if( ( CZILALA == 2 and PIES == 1 ) or KOT == 0 )
    {
        cout << "ee tak" << endl;
    }

    return 0;
}
