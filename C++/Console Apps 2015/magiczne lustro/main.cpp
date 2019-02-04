#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int main()
{

    uint64_t liczba;
    while( cin >> liczba )
    {
        vector <int> bin;
        while( liczba !=0 )
        {
            if( liczba%2 == 1 )     bin.push_back(1);
            else                    bin.push_back(0);

            liczba /= 2;
        }

        uint64_t wynik = 0;
        uint64_t potega = 1;

        for( int i = bin.size()-1 ; i >= 0; i-- )
        {
            wynik += bin[ i ] * potega;
            potega *= 2;
        }

        cout << wynik << endl;
    }
}
