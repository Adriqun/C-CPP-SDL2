#include <iostream>

using namespace std;
int tab[100000],testy;
float xa,ya,xb,yb,xc,yc;
double a1,b1,a2,b2;
int main()
{
    cin>>testy;
    for (int i=1; i<=testy; i++)
    {
        cin>>xa>>ya>>xb>>yb>>xc>>yc;
        if (((xa==xb)&&(xa==xc))||((ya==yb)&&(ya==yc)))
            tab[i]=1;
        else
        {
            a1=(ya-yb)/(xa-xb);
            b1=ya/(xa*a1);
            a2=(ya-yc)/(xa-xc);
            b2=ya/(xa*a2);
            if ((a1==a2)&&(b1==b2))
                tab[i]=1;
            else
                tab[i]=0;
        }
    }
    for (int i=1; i<=testy; i++)
    {
        if (tab[i]==1)
            cout<<"TAK"<<endl;
        else
            cout<<"NIE"<<endl;
    }

    return 0;
}
