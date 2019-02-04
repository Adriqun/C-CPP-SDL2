#include <iostream>
#include "stworz.h"
#include <fstream>
#include <windows.h>
using namespace std;
void Wszystko::fzapisu()
{
    cout<<"Wpisz pytanie: ";
    getline(cin,pytanie);

    cout<<endl<<"Wpisz odp A: ";
    getline(cin,a);

    cout<<endl<<"Wpisz odp B: ";
    getline(cin,b);

    cout<<endl<<"Wpisz poprawna odp: ";
    getline(cin,poprawna);

    cout<<endl<<endl;

    plik.open("pytanka.txt",ios::out|ios::app);

    plik<<pytanie<<endl;
    plik<<a<<endl;
    plik<<b<<endl;
    plik<<poprawna<<endl;

    plik.close();
}
void Wszystko::czyszczenie()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<endl<<"Plik jest czyszczony..."<<endl;
    Sleep(2000);

    plik.open("pytanka.txt",ios::out | ios::trunc);
    plik.close();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<"Gotowe!"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}
void Wszystko::wczytywanie()
{

    int nr=(nr_pytania-1)*4+1;
    plik.open("pytanka.txt",ios::in);
    if (plik.good()==false)
    {
        cerr<<"Nie udalo sie wczytac pliku!";
    }
    else
    {
        while(getline(plik,linia))
        {
            nr_linii++;
            if(nr_linii==nr)    pytanie=linia;
            if(nr_linii==nr+1)  a=linia;
            if(nr_linii==nr+2)  b=linia;
            if(nr_linii==nr+3)  poprawna=linia;
        }
    plik.close();
        cout<<endl<<pytanie<<endl;
        cout<<"A. "<<a<<endl;
        cout<<"B. "<<b<<endl;
        cout<<"Twoja odpowiedz: ";
        cin>>odpowiedz;
        if (odpowiedz==poprawna)
            punkty=1;
        else
            punkty=0;

    }

}

