#include <iostream>
#include <stack>
#include <windows.h>
using namespace std;


int main ()
{
    HANDLE kolor;
    kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 3 );
    int x;
    stack <int> mystack;
    for (int i=0; i<=4; i++)
    {
        cin>>x;
        mystack.push(x);
    }
    SetConsoleTextAttribute( kolor, 9 );

    cout<<endl<<"ZAWARTOSC STOSU: ";
    while (!mystack.empty())
    {
       cout<<mystack.top()<<' ';
        mystack.pop();
    }
    cout<<endl;
    SetConsoleTextAttribute( kolor, 3 );



    return 0;
}
