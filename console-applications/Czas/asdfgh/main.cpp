#include <iostream>

using namespace std;
float czasy[10];
int wynik,wynik2;

int main()
{
    for (int i=0;i<10;i++)
    {
    cout<<"Wpisz czas nr. "<<i+1<<" ktory uzyskales"<<endl;
    cin >> czasy[i];
    wynik+=czasy[i];
    wynik2=wynik/10;
    }

    cout<<"Sredni czas wynosi: "<<wynik2<<" sekund/y"<<endl;

    return 0;
}
