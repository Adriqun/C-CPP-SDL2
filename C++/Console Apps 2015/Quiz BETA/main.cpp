#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <algorithm> //z duzych liter na male
#include <string> //z duzych liter na male
using namespace std;
string odpowiedz;
fstream plik;
string linia,nick,temat,pytania[50],odpA[50];
string odpB[50],odpC[50],odpD[50],poprawne[50];
int nr_linii=1,nr_pytania=0;
int main()
{plik.open("quiz.txt",ios::in);
while (getline(plik,linia)){
    switch (nr_linii)
        {
        case 1: nick=linia;                   break;
        case 2: temat=linia;                  break;
        case 3: pytania[nr_pytania]=linia;    break;
        case 4: odpA[nr_pytania]=linia;       break;
        case 5: odpB[nr_pytania]=linia;       break;
        case 6: odpC[nr_pytania]=linia;       break;
        case 7: odpD[nr_pytania]=linia;       break;
        case 8: poprawne[nr_pytania]=linia;   break;
        }
        if  (nr_linii==8){nr_linii=2;nr_pytania++;}
        nr_linii++;}
        plik.close();
    cout<<nick<<endl;
    cout<<temat<<endl;
    for (int i=0;i<=8;i++){
    cout<<endl<<pytania[i]<<endl;
    cout<<"A. "<<odpA[i]<<endl;
    cout<<"B. "<<odpB[i]<<endl;
    cout<<"C. "<<odpC[i]<<endl;
    cout<<"D. "<<odpD[i]<<endl;
    cout<<"Twoja odpowiedz to: "<<endl;
    cin >>odpowiedz;
if (odpowiedz==poprawne[i]){
cout<<"Poprawna odpowiedz, zdobywasz punkt: "<<endl;}
else  cout<<"Zla odpowiedz, poprawna to: "<<poprawne[i]<<endl;}



    return (0);
}
