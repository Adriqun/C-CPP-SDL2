#include <iostream>

using namespace std;

int main()
{
    int liczba[100100],w,k;
    int b,t,liczba2[100100];
    //wczytywanie
    cin>>t;
    while(t--)
    {
      cin>>w>>k;
    for(int i=1;i<=w*k;i++)
        cin>>liczba[i];
    // zabezpieczenie buforem
    b=liczba[1];
    //wypisywanie pierwszego wiersza
    for(int i=2;i<=k;i++)
        cout<<liczba[i]<<" ";
    cout<<liczba[k*2]<<endl;
    //wczytywanie ostatniego wiersza
    liczba2[(w*k)-(k*2)+1]=liczba[(w*k)-(k*2)+1];
    for(int i=w*k-(k-1);i<=w*k-1;i++)
        liczba2[i]=liczba[i];
    //wczytywanie kolumny prawej
    for(int i=k-2;i<=w;i++)
        liczba[k*(i-1)]=liczba[k*i];
    //wczytywanie kolumny lewej
    for(int i=1;i<=w-2;i++)
    liczba[(w*k)-(k*i-1)]=liczba[((w*k)-(k*i-1))-k];
    //wypisywanie gotowego srodka
    liczba[k+1]=b;
    for(int i=k+1;i<=w*k-k;i++)
    {
        cout<<liczba[i]<<" ";
        if(i%k==0)
            cout<<endl;
    }
    //wypisywanie ostatniego wiersza
    cout<<liczba2[(w*k)-(k*2)+1]<<" ";
    for(int i=w*k-(k-1);i<=w*k-1;i++)
        cout<<liczba2[i]<<" ";
        cout<<endl;
    }

    return 0;
}
