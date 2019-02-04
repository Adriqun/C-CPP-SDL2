#include <iostream>

using namespace std;

class Imie
{
public:
    string imie;
    int ilosc;
    void h()
    {
        cout << "Podaj swoje imie: ";
        cin>> imie;
        cout<<"Podaj ile razy ma zostac napisane: ";
        cin>>ilosc;
        for (int i=1; i<=ilosc; i++)
        {
            cout<<i<<". "<<imie<<endl;
        }
    }
};
int main()
{
    Imie i;
    i.h();
    return 0;
}
