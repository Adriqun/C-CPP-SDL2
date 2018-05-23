#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
using namespace std;
string odpA[15],odpB[15],odpC[15],poprawna[15],pytanie[15];
string linia,nick,temat,odpowiedz;
fstream plik;
int nr_linii=1,nr_pytania=0,punkty=0;
int main()
{
    plik.open("Rodzina.txt", ios::in);
    if (plik==false)
    {
    cerr<<"Plik nie istnieje!";
    }
    else
    {
    while(getline(plik,linia))
    {
     switch(nr_linii)
     {
     case 1: nick=linia;                    break;
     case 2: temat=linia;                   break;
     case 3: pytanie[nr_pytania]=linia;     break;
     case 4: odpA[nr_pytania]=linia;        break;
     case 5: odpB[nr_pytania]=linia;        break;
     case 6: odpC[nr_pytania]=linia;        break;
     case 7: poprawna[nr_pytania]=linia;    break;
     }
     if (nr_linii==7)
     {
         nr_pytania++;
         nr_linii=2;
     }
    nr_linii++;
    } plik.close();
    for (int i=0;i<=10;i++)
    {
     Sleep (2000);
     system ("cls");
        cout<<endl<<pytanie[i]<<endl;
        cout<<"A. "<<odpA[i]<<endl;
        cout<<"B. "<<odpB[i]<<endl;
        cout<<"C. "<<odpC[i]<<endl;
        cout<<"Twoja odpowiedz to: ";
          odpowiedz=getch();
        transform(odpowiedz.begin(), odpowiedz.end(), odpowiedz.begin(), ::tolower);
    if (poprawna[i]==odpowiedz)
    {
        punkty ++;
        cout<<"Poprawna odpowiedz!"<<endl;
    }
    else
        cout<<"Zla odpowiedz! Poprawna odpowiedz to: "<<poprawna[i]<<endl;
    }
    cout<<"Koniec gry! Zdobyte punkty: "<<punkty<<"/11"<<endl;
    }


    return 0;
}
