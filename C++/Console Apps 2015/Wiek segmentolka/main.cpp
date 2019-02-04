#include <iostream>

using namespace std;
int test,odwlok,sumanog,nogi[100000],p[100000];
int main()
{
    cin>>test;
    for (int i=1;i<=test;i++)
    {
        cin>>odwlok;
        p[i]=(p[i]+odwlok-1);

        for (int a=1;a<=odwlok;a++)
        {
        cin>>nogi[a];

        p[i]=p[i]+nogi[a];
        }

    }
    for (int i=1;i<=test;i++)
    {
    cout<<p[i]<<endl;
    }
    return 0;
}
