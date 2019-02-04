#include <iostream>
#include <cstdlib>
using namespace std;
string nazwa;
char liter[300];
int ile,suma=0;
int main()
{
    cin>>nazwa;
    ile=nazwa.length();
    for(int i=0;i<=ile-1;i++)
    {
        liter[i]=nazwa[i];
    }
    for(int i=0;i<=ile-1;i++)
    {
        switch(liter[i])
        {
            case 'a': suma=suma+1;break;
            case 'b': suma=suma+2;break;
            case 'c': suma=suma+3;break;
            case 'd': suma=suma+4;break;
            case 'e': suma=suma+5;break;
            case 'f': suma=suma+6;break;
            case 'g': suma=suma+7;break;
            case 'h': suma=suma+8;break;
            case 'i': suma=suma+9;break;
            case 'k': suma=suma+10;break;
            case 'l': suma=suma+20;break;
            case 'm': suma=suma+30;break;
            case 'n': suma=suma+40;break;
            case 'o': suma=suma+50;break;
            case 'p': suma=suma+60;break;
            case 'q': suma=suma+70;break;
            case 'r': suma=suma+80;break;
            case 's': suma=suma+90;break;
            case 't': suma=suma+100;break;
            case 'v': suma=suma+200;break;
            case 'x': suma=suma+300;break;
            case 'y': suma=suma+400;break;
            case 'z': suma=suma+500;break;

        }
    }
    cout<<suma;
    return 0;
}
