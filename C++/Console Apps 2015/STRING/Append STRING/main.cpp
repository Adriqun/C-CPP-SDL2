#include <iostream>

using namespace std;
string nazwa;
int main()
{
    getline(cin,nazwa);
    nazwa.append(" siema");//do czego dodajemy i co dodajemy
    cout<<nazwa;
    return 0;
}
