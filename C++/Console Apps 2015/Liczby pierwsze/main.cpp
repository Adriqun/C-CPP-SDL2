#include <iostream>

using namespace std;
int n,testy;
bool czy_pierwsza(int n)
{
  if(n<2)
    return false;

  for(int i=2;i*i<=n;i++)
    if(n%i==0)
      return false;
  return true;
}
int main()
{   cin>>testy;
    int *tablica;
    for (int i=1;i<=testy;i++)
    {
    tablica=new int [i];
    }

    for (int i=1;i<=testy;i++)
    {
    cin>>tablica[i];

    }
    for (int i=1;i<=testy;i++)
    {
    if (czy_pierwsza(tablica[i]))
    cout<<"TAK"<<endl;
    else
    cout<<"NIE"<<endl;
    }




    return 0;
}
