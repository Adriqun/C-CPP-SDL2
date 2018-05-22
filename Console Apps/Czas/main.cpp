#include <iostream>

using namespace std;

class Godzina
{
    public:
    int h, m, g,c,a,b ;
    void wczytaj()
    {
        cout <<endl << "Wpisz godzine:";
        cin>> h;
        cout << "Wpisz minuty:";
        cin>> m;
        g = 23;
        c = 59;
        a = g-h;
        b = c-m;
    }
    void wypisz()
    {
        cout<<"Godzin do konca dnia:"<<a;
        cout<<endl<<"Minut do konca dnia:"<<b;
    }
};
int main()
{
    Godzina g1;
    g1.wczytaj();
    g1.wypisz();

    return 0;
}
