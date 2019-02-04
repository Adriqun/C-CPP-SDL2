#include <iostream>

using namespace std;
int a,b;
long long testy;
int main()

{   cin>>testy;
    for (int i=1;i<=testy;i++)
    {
    cin>>a>>b;
    while (a!=b)
    {
        if (a<b) b-=a;
        else a-=b;
    }
    cout<<a<<endl;
    }

    return 0;
}
