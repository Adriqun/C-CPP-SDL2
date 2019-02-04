#include <iostream>
#include <fstream>
#include "Quiz.h"
#include <windows.h>
using namespace std;
void Klasa::wczytaj()
{
    int i=(co-1)*4+1;
    int pyt=1;
    string li;
    plik.open("pytania.txt",ios::in);
    while(getline(plik,li))
    {
        if(pyt==i)pytanie=li;
        if(pyt==i+1)a=li;
        if(pyt==i+2)b=li;
        if(pyt==i+3)poprawna=li;
        pyt++;
    }
    plik.close();
}
void Klasa::wypisz()
{
    cout<<pytanie<<endl;
    cout<<"A. "<<a<<endl;
    cout<<"B. "<<b<<endl;
    cout<<"Odpowiedz: "; cin>>odpowiedz;
    if (odpowiedz==poprawna)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
        cout<<"Zdobywasz punkt!"<<endl<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        punkty=1;
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
        cout<<"Zla odpowiedz!"<<endl<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        punkty=0;
    }
}
