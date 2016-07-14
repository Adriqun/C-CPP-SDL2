#include <iostream>
#include "stworz.h"
#include <cstdlib>
#include <windows.h>
#include <conio.h>
using namespace std;
void kolor(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i);
}
void ekran()
{
    string e="X. Czyszczenie ekranu";
    int wybor,r,suma=0,g=0,c=0;
    Wszystko z[100];
   while(true)
    {
        wybor=getch();
        switch (wybor)
        {
        case '1': z[g].fzapisu();g++; break;
        case '2':
            for(int i=0;i<g;i++)
            {
              z[i].nr_pytania=i;
               z[i].wczytywanie();
               suma+=z[i].punkty;
               c=1;
            }
            if (c==0) cout<<"Nie udalo sie wczytac pliku!"<<endl;
            else
            cout<<"Zdobyte punkty: "<<suma<<endl;
            suma=0;
            break;
        case '3': z[g].czyszczenie();g--;break;
        case '4': exit (0); break;
        default:
            system("cls");
            r=14; kolor(r);
            cout<<"                     MENU"<<endl;
            cout<<"                    ------"<<endl;
            r=7; kolor(r);
            cout<<"1. "; r=4; kolor(r); cout<<"Dodaj ";r=7; kolor(r);
            cout<<"(pytanie,odpowiedzi A|B i poprawna odp)"<<endl;

            cout<<"2. "; r=10; kolor(r); cout<<"Rozpocznij ";r=7; kolor(r);
            cout<<"gre"<<endl;

            cout<<"3. "; r=15; kolor(r); cout<<"Wyczysc "; r=7; kolor(r);
            cout<<"wszystkie aktualne zestawy"<<endl;

            cout<<"4. "; r=6; kolor(r); cout<<"Zakoncz "; r=7; kolor(r);
            cout<<"dzialanie programu"<<endl<<e<<endl<<endl;
        }
    }
}
int main()
{
    cout<<"Program sluzy do robienia quizu jak i rowniez do zagrania"<<endl;
    Sleep(2000);
    cout<<"Kliknij dowolny klawisz";
    ekran();


    return 0;
}
