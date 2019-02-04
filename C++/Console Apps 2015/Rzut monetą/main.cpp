#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
using namespace std;
string jedynka, dwojka;
int liczba, /*pojemnik[5],*/suma;
int main()
{   cout << "Rzuc moneta!" << endl;
    cout << "Wpisz pierwsze wyrazenie: "<< endl;
    cin >> jedynka;
    cout << "Wpisz drugie wyrazenie: "<< endl;
    cin >> dwojka;
  /* for (int i=0;i<4;i++)
    {
    srand (time(NULL));
    liczba=rand ()%4+i;
    cout<<liczba<<endl;
    cin>>pojemnik[i];
    Sleep (300);
    cout<<i<<endl;
    suma=suma+pojemnik[i];
    cout<<suma<<endl;
    }
    */
    srand (time(NULL));
    liczba=rand()%2+1;
    Sleep (2000);
    switch (liczba)
   {
    case 1:
    cout<<"Mysle..."<<endl;
    Sleep(1500);
    cout<<"Wylosowalem: "<<jedynka<<endl;
    break;
    case 2:
    cout<<"Mysle..."<<endl;
    Sleep(1500);
    cout<<"Wylosowalem: "<<dwojka<<endl;
    break;

    }




    return 0;
}
