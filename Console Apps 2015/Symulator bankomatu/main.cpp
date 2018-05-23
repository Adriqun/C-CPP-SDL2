#include <iostream>

using namespace std;
string PIN;
int main()
{
    cout << "Witaj w naszym banku!"<< endl ;
    cout<< "Wprowadz kod PIN:";
    cin >> PIN;
     if(PIN == "1591")
     {
          cout<< "Wprowadziles poprawny PIN";
     }
    else
    {
        cout<< "Wprowadziles niepoprawny PIN";
    }
        return 0;
}
