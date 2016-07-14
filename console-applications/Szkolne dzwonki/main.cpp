#include <iostream>

using namespace std;
int l,ln,liczba,numer[11000],i,g;
int main()
{
    string n;
    cin>>n;
    l=(int)n[1]-48;
    ln=(int)n[4]-48;

    if (n[0]=='1')l+=10;
    if (n[0]=='2')l+=20;

    switch(n[3])
    {
    case '1':ln+=10;break;
    case '2':ln+=20;break;
    case '3':ln+=30;break;
    case '4':ln+=40;break;
    case '5':ln+=50;break;
    }
    while(cin>>liczba)
        numer[i]=liczba;i++;



    for (int j=0;j<i;j++)
    {
        ln+=45;
        if (ln>=60)
        {
            while (ln>=60)
                ln-=60;l++;
        }
        while (l-24>=0)
            l=l-24;
        if(l<10)
            cout<<"0";
            cout<<l<<":";
        if (ln<10)
            cout<<"0";
            cout<<ln<<",";

        ln+=numer[j];

        if (ln>=60)
        {
            while (ln>=60)
                ln-=60;l++;
        }
        while (l-24>=0)
            l=l-24;
        if(l<10)
            cout<<"0";
            cout<<l<<":";
        if (ln<10)
            cout<<"0";
            cout<<ln<<",";
    }
        ln+=45;
        if (ln>=60)
        {
            while (ln>=60)
                ln-=60; l++;
        }
        while (l-24>=0)
            l=l-24;
        if(l<10)
            cout<<"0";
            cout<<l<<":";
        if (ln<10)
            cout<<"0";
            cout<<ln;
    return 0;
}
