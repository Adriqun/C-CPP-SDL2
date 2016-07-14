#include <iostream>
#include <iomanip>
using namespace std;
class Fib
{
public:

    int n,a;
    long double *fib;
    void funkcja1()
    {
        cout << "Na podstawie jakiej liczby chcesz wyznaczyc zlota liczbe? ";
        cin>>n;
        fib = new long double [n];
        fib[0]=1;
        fib[1]=1;
        for (int i=2; i<n; i++)
        {
            fib[i]=fib[i-1] + fib[i-2];
        }
    }
    void funkcja2()
    {
        cout<<setprecision(10000);
        cout<<"Zlota liczba wynosi: "<<fib[n-1]/fib[n-2]<<endl;
        delete [] fib ;
    }
};
int main()
{
    Fib f1;
    f1.funkcja1();
    f1.funkcja2();

    return 0;
}

