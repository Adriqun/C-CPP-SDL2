#include <iostream>
#include <windows.h>
using namespace std;
float a, b, c;
string szarlotka;
int main()


{
    for (int i=1; i<=18; i++)
    if (i==1)
    {
    cout<<"W";
    Sleep (100);
    }
    else if (i==2)
    {
    cout<<"i";
    Sleep (100);
    }
    else if (i==3)
    {
    cout<<"t";
    Sleep (100);
    }
    else if (i==4)
    {
    cout<<"a";
    Sleep (100);
    }
    else if (i==5)
    {
    cout<<"j";
    Sleep (100);
    }
    else if (i==6)
    {
    cout<<" w ";
    Sleep (100);
    }
    else if (i==7)
    {
    cout<<"k";
    Sleep (100);
    }
    else if (i==8)
    {
    cout<<"a";
    Sleep (100);
    }
    else if (i==9)
    {
    cout<<"l";
    Sleep (100);
    }
    else if (i==10)
    {
    cout<<"k";
    Sleep (100);
    }
    else if (i==11)
    {
    cout<<"u";
    Sleep (100);
    }
    else if (i==12)
    {
    cout<<"l";
    Sleep (100);
    }
    else if (i==13)
    {
    cout<<"a";
    Sleep (100);
    }
    else if (i==14)
    {
    cout<<"t";
    Sleep (100);
    }
    else if (i==15)
    {
    cout<<"o";
    Sleep (100);
    }
    else if (i==16)
    {
    cout<<"r";
    Sleep (100);
    }
    else if (i==17)
    {
    cout<<"z";
    Sleep (100);
    }
    else if (i==18)
    {
    cout<<"e"<<endl;
    Sleep (100);
    }
    {
        Sleep (1000);
    cout<<"Wpisz co chcialbys zrobic z dwiema liczbami"<<endl;
    cin>>szarlotka;
    cout<<"Wpisz liczbe a"<<endl;
    cin>>a;
    cout<<"Wpisz liczbe b"<<endl;
    cin>>b;
    }
    if (szarlotka=="dodawanie")
    {
    c=a+b;
    cout<<"Wynik wynosi:"<<c<<endl;
    }
    else if (szarlotka=="mnozenie")
    {
    c=a*b;
    cout<<"Wynik wynosi:"<<c<<endl;
    }
    else if (szarlotka=="odejmowanie")
    {
    c=a-b;
    cout<<"Wynik wynosi:"<<c<<endl;
    }
    else if (szarlotka=="dzielenie")
    {
    c=a/b;
    cout<<"Wynik wynosi:"<<c<<endl;
    }



    return 0;
}
