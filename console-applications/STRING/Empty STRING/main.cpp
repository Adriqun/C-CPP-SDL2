#include <iostream>
#include <string>

using namespace std;
string napis;
int main()
{
    cin>>napis;
    napis.clear();
    if (napis.empty()==true)
        cout<<"Zmienna jest pusta";
    else
        cout<<"Zmienna jest zajeta";

    return 0;
}
