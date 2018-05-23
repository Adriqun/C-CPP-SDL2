#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
using namespace std;
int nr=0,dlugosc;
float wynik[1000];
string linia; int nr_linii=1;
fstream plik;
float ile_cali(float m)
{
    return m*39.37;
}
float ile_jardow(float m)
{
    return m*1.093;
}
float ile_mil(float m)
{
    return m*0.000621;
}
int main()
{
 cout<<"Ile wynikow chcesz wczytac: "<<endl;
 cin>>dlugosc;
 system ("cls");
    plik.open("wartosci.txt", ios::in);
    while (getline(plik,linia))
    {
        switch(nr_linii)
        {
            case 1: wynik[nr]=atof(linia.c_str()); break;
        }
        if (nr_linii==1)
        {
            nr_linii=0;
            nr++;
        }
        nr_linii++;
    }
    plik.close();
    for (int i=0;i<=dlugosc-1;i++)
    {
        cout<<"Wartosc nr. "<<i+1<<" wynosi "<<wynik[i]<<endl;
        cout<<"----->Na cale: "<<ile_cali(wynik[i])<<endl;
        cout<<"-------->Na jardy: "<<ile_jardow(wynik[i])<<endl;
        cout<<"----------->Na mile: "<<ile_mil(wynik[i])<<endl;
        cout<<endl<<endl<<endl;
    }
    return 0;
}
