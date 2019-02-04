#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
using namespace std;
int liczba, strzal, prob=0;
int main()
{
    cout << "Witaj pomyslalem sobie liczbe z zakresu 1...100" << endl;
    srand(time(NULL));
    liczba=rand()%100+1;

    while(strzal!=liczba)
   { prob++;
    cout<<"Zgadnij jaka:(To twoja"<<prob<<" proba)"<<endl;
    cin >> strzal;

    if (strzal==liczba)
    cout<<"Wygrales w "<< prob<<" probie!"<<endl;

    else if (strzal<liczba)
    cout<<"To za malo"<<endl;

    else if (strzal>liczba)
    cout<<"To za duzo"<<endl;
    }
    getchar();getchar();

    return 0;
}
