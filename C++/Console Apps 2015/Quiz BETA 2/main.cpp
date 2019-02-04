#include <iostream>
#include <fstream>
using namespace std;

string dane[3],dana[3],zdrowsze[3],linia,poprawna;
fstream plik;
int nrl=1,nrp=0, punkty=0;
int main()

{ cout<<"Zadanie polega na odgadnieciu co ma wiecej bialka, lets go!"<<endl;
plik.open("quiz.txt", ios::in);
while (getline (plik,linia))
 {
     switch (nrl)
     {
         case 1: dane[nrp]=linia; break;
         case 2: dana[nrp]=linia; break;
         case 3: zdrowsze[nrp]=linia; break;
     }
     if (nrl=3)
     {
         nrl=0;
         nrp++;
     }
     nrl++;}
     for (int i=0;i<=2;i++)
     {
         cout<<"A. "<<dane[i]<<endl;
         cout<<"B. "<<dana[i]<<endl;

     cout<<"Twoja odpowiedz to: "<<endl;
     cin>>poprawna;
     if (poprawna==zdrowsze[i])
     {
         cout<<"Poprawna odpowiedz, otrzymujesz punkt!"<<endl;
         punkty++;
     }
     else
        cout<<"Zla odpowiedz, poprawna to: "<<zdrowsze[i]<<endl;
     }
     cout<<"Koniec gry, zdobyte punkty: "<<punkty<<endl;






    return 0;
}
