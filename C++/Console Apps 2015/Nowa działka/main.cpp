#include <iostream>

using namespace std;
int testy,n[100000];
int main()
{
    cin>>testy;
    for (int i=1;i<=testy;i++)
    {
        cin>>n[i];
    }
    for (int i=1;i<=testy;i++)
    {
        cout<<n[i]*n[i]<<endl;
    }
    return 0;
}
