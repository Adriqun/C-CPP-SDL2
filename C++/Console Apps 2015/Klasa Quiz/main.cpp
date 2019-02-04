#include <iostream>
#include "Quiz.h"
#include <windows.h>
using namespace std;

int main()
{
    int suma=0;
    Klasa s[6];
    for (int i=1;i<=5;i++)
    {
    s[i].co=i;
    s[i].wczytaj();
    s[i].wypisz();
    suma+=s[i].punkty;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout<<"Koniec gry! Zdobyte punkty: "<<suma;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    return 0;
}
