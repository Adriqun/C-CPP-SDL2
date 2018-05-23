#include <iostream>
#include <cmath>
using namespace std;
int a,b;
int main()
{
    cout << "Funkcja liczy najdluzszy bok trojkata" << endl;
    cout<<endl<<"Wpisz bok a i b: ";
    cin>>a>>b;
    cout<<endl<<"Bok c wynosi: "<<hypot(a,b);
    return 0;
}
