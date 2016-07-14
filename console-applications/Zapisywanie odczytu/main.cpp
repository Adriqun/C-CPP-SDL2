#include <iostream>
#include <fstream> //file
using namespace std;
string imie,nazwisko;
int nr;
int main()
{
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj nr telefonu: ";
    cin >> nr;
    fstream plik;
    plik.open("aaa.txt", ios::out|ios::app);
    plik<<imie<<endl;
    plik<<nazwisko<<endl;
    plik<<nr<<endl;
    plik.close ();
    return 0;
}
