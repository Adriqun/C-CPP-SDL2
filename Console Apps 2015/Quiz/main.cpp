#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <algorithm> //z duzych liter na male
#include <string> //z duzych liter na male
using namespace std;
string temat,nick,a[5],b[5],c[5],d[5],poprawna[5],tresc[5],linia,odpowiedz;
int nr_linii=1, nr_pytania=0,punkty=0;
int main()
{
    fstream plik;
    plik.open ("quiz.txt", ios::in);
    if (plik.good()==false)
    {
        cout<<"Plik nie istnieje!"<<endl;
        exit (0);}
        while (getline(plik,linia))
        {
            switch (nr_linii)
            {
                case 1: temat=linia;       break;
                case 2: nick=linia;        break;
                case 3: tresc[nr_pytania]=linia;    break;
                case 4: a[nr_pytania]=linia;        break;
                case 5: b[nr_pytania]=linia;        break;
                case 6: c[nr_pytania]=linia;        break;
                case 7: d[nr_pytania]=linia;        break;
                case 8: poprawna[nr_pytania]=linia; break;
            }
            if (nr_linii==8){nr_linii=2;nr_pytania++;}
            nr_linii++;
        } plik.close();
        for(int i=0;i<=4;i++)
        {
        cout<<endl<<tresc[i]<<endl;
        cout<<"A. "<<a[i]<<endl;
        cout<<"B. "<<b[i]<<endl;
        cout<<"C. "<<c[i]<<endl;
        cout<<"D. "<<d[i]<<endl;



        cout<<"Twoja odpowiedz: "<<endl;
        cin>>odpowiedz;
        transform (odpowiedz.begin(),odpowiedz.end(),odpowiedz.begin(), ::tolower) ;
        if (odpowiedz==poprawna[i])
        {cout<<"Dobrze zdobywasz punkt!"<<endl;
        punkty++;}
        else cout<<"Zle! Brak punktu, poprawna odpowiedz to: "<<poprawna[i]<<endl;
        }
        cout<<endl<<"Koniec gry! Zdobyte punkty: "<<punkty<<endl;
    return 0;
}
