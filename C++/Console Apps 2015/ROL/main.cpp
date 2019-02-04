#include <iostream>

using namespace std;
int ile_liczb,n[1000000],ile_w_lewo;
int main()
{
    cin>>ile_liczb;
    cin>>ile_w_lewo;
    for (int i=1;i<=ile_liczb;i++)
    {
        cin>>n[i];
    }
    for (int i=ile_w_lewo+1;i<=ile_liczb;i++)
    {
    cout<<n[i]<<" ";
    }
    for (int i=1;i<=ile_w_lewo;i++)
    {
    cout<<n[i]<<" ";
    }


    return 0;
}
