#include <iostream>

using namespace std;
float F,C,K,H,G;
string haslo;
int main()
{
    cout << "Wprowadz z jakiej wartosci liczysz (f lub k)" << endl;
    cin>> haslo;
    if (haslo=="f")
    {
        cout<< "Witaj w programie F na C"<<endl;
        cout<<"Wprowadz temperature w F:";
        cin>>F;
        C=(F-32)*5;
        G=C/9;
        cout<<"Temperatura w C wynosi:"<<G;
    }
    else if (haslo=="k")
    {
        cout<< "Witaj w programie K na C:"<<endl;
        cout<<"Wprowadz remperature w K:";
        cin>>K;
        H=(K-273);
        cout<<"Temperatura w C wynosi:"<<H;
    }
   else
   cout<<"Not today";

    return 0;
}
