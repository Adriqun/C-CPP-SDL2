#include "instrukcja.h"
#include <iostream>
using namespace std;
void Klasa::metoda()
{

    for(;;) // while(wybor!=5) while (true)
    {
        cout<<"MENU GLOWNE"<<endl;
        cout<<"-----------"<<endl;
        cout<<"1.Dodawanie"<<endl;
        cout<<"2.Odejmowanie"<<endl;
        cout<<"3.Mnozenie"<<endl;
        cout<<"4.Dzielenie"<<endl;
        cout<<"5.Koniec programu"<<endl<<endl;
        cout << "Podaj 1 liczbe: ";
        cin >> x;
        cout << "Podaj 2 liczbe: ";
        cin >>y;
        cout<<endl;

        cout<<"Wynik: ";
        wybor=getch(); //pobierz znak


        switch (wybor)
        {
        case '1':
            cout<<x+y<<endl;
            break;
        case '2':
            cout<<x-y<<endl;
            break;
        case '3':
            cout<<x*y<<endl;
            break;
        case '4':
            if (y==0)
                cout<<"Nie dzielimy przez 0!"<<endl;
            else
                cout<<x/y<<endl;
            break;
        case '5':
            exit(0);
            break;

        default:
            cout<<"Nie ma takiej opcji w menu"<<endl;
        }
        getchar();
        getchar();
        system ("cls");
    }
}
