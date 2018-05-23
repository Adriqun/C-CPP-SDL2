#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
class Znak
{
    public:
    char znak;
    void wczytaj()
    {
        znak=getch();
    }
    void wypisz()
    {
        switch (znak)
        {
        case 'a':
            cout<<"Czekolada"<<endl;
            break;
        case 'b':
            cout<<"Szynka"<<endl;
            break;
        }
    }
};
int main()
{
    Znak z1;
    z1.wczytaj();
    z1.wypisz();
    return 0;
}
