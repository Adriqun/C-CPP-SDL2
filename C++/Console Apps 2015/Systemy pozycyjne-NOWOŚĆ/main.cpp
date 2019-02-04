#include <iostream>

using namespace std;
int l,g,l2,t;
string jedn;
int main()
{
    cin>>t;
    while(t--)
    {
    jedn.clear();
    cin>>l;
    l2=l;
     //wczytuje pierwsza liczbe szesnastkowo
    if      (l2%16==10) jedn+='A';
    else if (l2%16==11) jedn+='B';
    else if (l2%16==12) jedn+='C';
    else if (l2%16==13) jedn+='D';
    else if (l2%16==14) jedn+='E';
    else if (l2%16==15) jedn+='F';
    else jedn+=(char)(l2%16)+48;
    g++;
    //wczytuje pozostale cyfry i zapisuje szesnastkowo
    do
    {
    l2/=16;
    if  (l2%16==10) jedn+='A';
    else if (l2%16==11) jedn+='B';
    else if (l2%16==12) jedn+='C';
    else if (l2%16==13) jedn+='D';
    else if (l2%16==14) jedn+='E';
    else if (l2%16==15) jedn+='F';
    else                jedn+=(char)(l2%16)+48;
    g++;
    }   while(l2>16);
    //warunek przeciwko np 0A (powinno byc samo A)
    if (jedn[g-1]!='0')
            cout<<jedn[g-1];
    //wypisywanie reszty liczb szesnastkowo
    for(int i=g-2;i>=0;i--)
        cout<<jedn[i];
        cout<<" ";
    //zeruje licznik i czyszcze zmienna
        g=0;
    jedn.clear();

    //zapisuje pierwsza cyfre jedynastkowo
    if (l%11==10)
        jedn+='A';
    else
        jedn+=(char)(l%11)+48;
        g++;
    //petla na wczytywanie pozostalych cyfr
    do
    {
        l/=11;
        if (l%11==10)
            jedn+='A';
        else
        jedn+=(char)(l%11)+48;
        g++;

    }   while(l>11);

    //wypisywanie jedenastkowo/warunek identyczny jak wczesniej
    if (jedn[g-1]!='0')
            cout<<jedn[g-1];
    for(int i=g-2;i>=0;i--)
        cout<<jedn[i];
    //przejscie do nastepne linijki/ zerowanie licznika
    cout<<endl;
    g=0;
    }
    return 0;
}

