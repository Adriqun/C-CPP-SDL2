#include <iostream>

using namespace std;
int f(int n)
{
    if (n==0) return 3;
    else return f(n-1)+2;
}
int silnia (int n)
{
    if (n==0) return 1;
    else return silnia(n-1)*n;
}
int main()
{
    cout <<f(3)<< endl;
    cout<<silnia(6)<<endl;
    return 0;
}
