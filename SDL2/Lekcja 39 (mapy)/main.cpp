#include <iostream>
#include <map>
using namespace std;

int main()
{
    map < string, int > slownik;

    slownik["slowo"] = 45;
    slownik["czekna"] = 88;

    cout << "Slowu \"slowo\" przypisano wartosc: " << slownik["czekna"];

    return 0;
}
