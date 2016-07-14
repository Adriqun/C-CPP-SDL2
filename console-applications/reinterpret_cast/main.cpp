#include <iostream>

using namespace std;

int main()
{
    int number = 400;
    int* wskaznik;
    unsigned adres;

    wskaznik = &number;
    adres = reinterpret_cast< unsigned >( wskaznik );
    cout << adres;

    return 0;
}
