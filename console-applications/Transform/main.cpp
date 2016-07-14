#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <windows.h>
using namespace std;
string litera;
int zmienna;
int main()
{
    cout<<" MENU "<<endl;
    cout<<"1-z malych na duze"<<endl;
    cout<<"2-z duzych na male"<<endl;
    if (!(cin>>zmienna))
    {
    cerr<<"Brak dostepnych opcji"<<endl;
    }
    else
    while (true)

    { Sleep (5000);
    system ("cls");
    switch (zmienna)
    {
    case 1:

    cout<< "Wpisz dowolny napis: " ;
    cin>>litera;
    transform (litera.begin(), litera.end(), litera.begin(), ::toupper);
    cout<<litera<<endl;
    break;
    case 2:

    cout << "Wpisz dowolny napis: " ;
    cin>>litera;
    transform (litera.begin(), litera.end(), litera.begin(), ::tolower);
    cout<<litera<<endl;
    break;
    }
    }
    return 0;
}
