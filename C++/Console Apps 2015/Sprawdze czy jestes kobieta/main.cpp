#include <iostream>

using namespace std;
string imie;
int dlugosc;
int main()
{
    cout << "Wpisz swoje imie: ";
    cin >> imie;
    dlugosc = imie.length();
    if (imie[dlugosc-1]=='a')
    {
     cout<<"Wydaje mi sie ze jestes kobieta"<<endl;
    }
    else
    cout<<"Wydaje mi sie ze jestes mezczyzna"<<endl;

    return 0;
}























