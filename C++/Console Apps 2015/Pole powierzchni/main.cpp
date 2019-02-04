#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
using namespace std;
int i=0,a=0;
char wybor;
float h_trj, p_trj, b_kw, b_pr, b_pr2,h_row,p_row ;
int main()
{
    cout<<"Wcisnij 3 krotnie klawisz enter aby wlaczyc program"<<endl;
    cout<<"Zakoncz klikajac klawisz 9"<<endl;
    cout<<"Wyczysc ekran klikajac dowolny klawisz";
    getchar();getchar();
    system ("cls");

    while (true)
    {
        wybor=getch();
    switch (wybor)
    {
    case '1':
         cout<<"Wpisz wysokosc trojkata: "<<endl; cin>>h_trj;
         cout<<"Wpisz podstawa trojkata: "<<endl; cin>>p_trj;
         cout<<endl<<"Pole trojkata wynosi: "<<(h_trj*p_trj)/2<<endl;
         break;
    case '2':
         cout<<"Wpisz bok kwadratu: "<<endl; cin>>b_kw;
         cout<<endl<<"Pole kwadratu wynosi: "<<b_kw*b_kw<<endl;
         break;
    case '3':
         cout<<"Wpisz bok a: "<<endl; cin>>b_pr;
         cout<<"Wpisz bok b: "<<endl; cin>>b_pr2;
         cout<<endl<<"Pole prostokata wynosi: "<<b_pr*b_pr2<<endl;
         break;
    case '4':
         cout<<"Wpisz wysokosc: "<<endl; cin>>h_row;
         cout<<"Wpisz podstawe: "<<endl; cin>>p_row;
         cout<<endl<<"Pole rownolegloboku wynosi: "<<h_row*p_row<<endl;
         break;
    case '5':
        cout<<"Wpisz pierwsza przekatna: "<<endl; cin>>p_row;
        cout<<"Wpisz druga przekatna: "<<endl; cin>>h_row;
        cout<<"Pole rombu wynosi: "<<(h_row*p_row)/2<<endl;
        break;
    case '6':
        cout<<"Wpisz wysokosc trapezu: "<<endl; cin>>h_row;
        cout<<"Wpisz kolejno bok a i b: "<<endl; cin>>p_row>>b_pr;
        cout<<"Pole trapezu wynosi: "<<((p_row+b_pr)*h_row)/2<<endl;
        break;
    case '7':
        cout<<"Wpisz kolejno przekatne a i b: "<<endl; cin>>p_row>>h_row;
        cout<<"Pole deltoidu wynosi: "<<p_row*h_row/2<<endl;
        break;
    case '8':
        cout<<"Wpisz promien: "<<endl; cin>>p_row;
        cout<<"Pole kola wynosi: "<<(p_row*p_row)*3.14<<endl;
        break;
    case '9':
        exit(0);
        break;
    default:
        system("cls");
    cout << "1.Trojkat            ";
    cout << "2.Kwadrat            ";
    cout << "3.Prostokat          ";
    cout << "4.Rownoleglobok      ";
    cout << "5.Romb               ";
    cout << "6.Trapez             ";
    cout << "7.Deltoid            ";
    cout << "8.Kolo               "<<endl;
    }
    }



    return 0;
}
