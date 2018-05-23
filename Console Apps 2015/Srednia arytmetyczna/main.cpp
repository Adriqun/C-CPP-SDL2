#include <iostream>
#include <math.h>
using namespace std;
float a,b,c,d,e,m,s,w;
int main()
{
    cin>>a>>b>>c>>d>>e;
    s=(a+b+c+d+e)/5;
    cout<<"Srednia wynosi: "<<s<<" "<<endl;

     m=fabs(s-a);
     w=a;

        if (fabs(s-b)<m)
    {  m=fabs(s-b); w=b; }

        if (fabs(s-c)<m)
    {  m=fabs(s-c); w=c; }

        if (fabs(s-d)<m)
    {  m=fabs(s-d); w=d; }

        if (fabs(s-e)<m)
    {  m=fabs(s-e); w=e; }

    cout<<"Liczba najblizsza sredniej wynosi: "<<w;
    return 0;
}
