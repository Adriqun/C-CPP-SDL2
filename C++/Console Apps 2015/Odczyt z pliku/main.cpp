#include <iostream>
#include <fstream> //file
#include <cstdlib>
using namespace std;
string imie, nazwisko,linia;
int nr,nr_linii=1;
int main()
{
    fstream plik;
    plik.open("aaa.txt" ,ios::in);
    if (plik.good()==false)
    {
        cout<<"Plik nie istnieje";
        exit(0);
    }
    while (getline (plik,linia))
    {
    switch (nr_linii)
    {
    case 1: imie = linia; break;
    case 2: nazwisko = linia; break;
    case 3: nr = atoi(linia.c_str()); break;
    }
    nr_linii++;
    }

   plik.close();
   cout << imie<<endl;
   cout<< nazwisko<< endl;
   cout<<nr<<endl;

    return 0;
}
