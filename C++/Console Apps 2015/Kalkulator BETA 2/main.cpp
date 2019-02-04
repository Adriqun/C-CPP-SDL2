#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <stdio.h>
using namespace std;
int wybor;
float x,y;
int main()
{ while (true)
    {
    cout<<" MENU GLOWNE "<<endl;
    cout<<"-------------"<<endl;
    cout<<"1.Dodawanie  "<<endl;
    cout<<"2.Odejmowanie"<<endl;
    cout<<"3.Mnozenie   "<<endl;
    cout<<"4.Dzielenie  "<<endl;
    cout<<"5.Wyjscie z programu"<<endl;
    Sleep (1000);
    cout<<"Wprowadz 1 liczbe"<<endl; cin >>x;
    cout<<"Wprowadz 2 liczbe"<<endl; cin >>y;
    cout<<"Wybierz: "<<endl;
    cin >>wybor;
    switch (wybor)
    {
    case 1:
    cout<<"Wynik to: "<<x+y<<endl;
    Sleep(3000);
    system ("cls");
    break;
    case 2:
    cout<<"Wynik to: "<<x-y<<endl;
    Sleep(3000);
    system ("cls");
    break;
    case 3:
    cout<<"Wynik to: "<<x*y<<endl;
    Sleep(3000);
    system ("cls");
    break;
    case 4:
    if (y==0)
    cout<<"Nie dzielimy przez 0"<<endl;
    else
    cout<<"Wynik to: "<<x/y<<endl;
    Sleep(3000);
    system ("cls");
    break;
    case 5: exit (0); break;
    }
    }
    return 0;
}
