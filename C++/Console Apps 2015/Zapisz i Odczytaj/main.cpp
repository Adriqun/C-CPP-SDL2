#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
string imie, nazwisko;
fstream plik;
int main()
{
    cout << "Witaj! Za chwile dokonamy zapisu danych!"<<endl;
    cout << "Wpisz swoje imie: "; cin>>imie;
    cout << "Wpisz swoje nazwisko: "; cin>>nazwisko;

    plik.open ("dane.txt", ios::out);
    plik<<imie<<endl;
    plik<<nazwisko<<endl;
    plik.close ();
    Sleep (3000);
    plik.open ("dane.txt", ios::in);
    cout<<"Twoje imie to: "<<imie<<endl;
    cout<<"Twoje nazwisko to: "<<nazwisko<<endl;
    plik.close ();

    return 0;
}
