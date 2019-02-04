#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;
int silnia1 (long long n)
{long long i=0,w=1;
    while (i<n)
    {
        i++;
        w=w*i;
    }
    return w;
}
int silnia2 (long long n)
{
    if (n==0) return 1;
    else return silnia2(n-1)*n;
}
int n,testy;
clock_t start, stop;
float czas=0;
int main()
{   cout<<"Wpisz n-silnie liczbe: ";
    cin>>n;
    cout<<endl<<"Wpisz liczbe testow: ";
    cin>>testy;
    start=clock();
    for (int i=1;i<=testy;i++)
    {
     silnia1(n);
    }
    stop=clock();
    czas= (float)(stop-start)/CLOCKS_PER_SEC;
    cout<<"Czas z uzyciem iteracji: "<<czas<<endl;
    start=clock();
    for (int i=1;i<=testy;i++)
    {
     silnia1(n);
    }
    stop=clock();
    czas=(float)(stop-start)/CLOCKS_PER_SEC;
    cout<<"Czas z uzyciem rekurencji: "<<czas<<endl;
    return 0;
}
