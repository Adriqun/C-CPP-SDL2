#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
using namespace std;
int wybor;
void zapis();
void odczyt();
void menu ();
int main()
{   menu ();
    while (true)
    {
    wybor=getch();
      switch(wybor)
      {
    case '1': system ("cls"); zapis();  break;
    case '2': system ("cls"); odczyt(); break;
    case '3': system ("cls"); exit(0);  break;
    default : system ("cls"); menu ();
      }
    }

    return 0;
}

void zapis()
{
    string ia[10000]; fstream plik;
    for (int i=1; i<=2;i++)
{
    cout << "Wpisz dane: "; getline(cin,ia[i]);
}
    plik.open("dane.txt",ios::out | ios::app);
    for (int i=1; i<=3;i++)
{
    plik<<ia[i]<<endl;
}
    plik.close();
}
void odczyt()
{
    fstream plik; string linia,zdanie[10000],odp;
    int nr_linii=1,nr_nr=0;

    plik.open("dane.txt",ios::in);
    while (getline(plik,linia))
    {
    switch (nr_linii)
    {
        case 1: zdanie[nr_nr]=linia; break;
    }
    if (nr_linii=1)
    {   nr_nr++;
        nr_linii=0;
    }
    nr_linii++;
    }
    plik.close();

    for (int i=0;i<=(nr_nr-1);i++)
    {
        cout<<zdanie[i]<<endl;
    }
}
void menu ()
{
    cout<<"MENU"<<endl;
    cout<<"1.Zapis"<<endl;
    cout<<"2.Odczyt"<<endl;
    cout<<"3.Koniec programu"<<endl;
    cout<<"Dowolny klawisz.Czyszczenie ekranu"<<endl;
}
