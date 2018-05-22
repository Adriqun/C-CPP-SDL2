#include <iostream>

using namespace std;
string pat;
int main()
{
    cout << "Witaj w programie Adriana,TEST NA GLUPOTE" << endl;
    cout<<"Pamietaj ze imiona zaczynamy duza litera"<< endl;
    cout<< "Wpisz swoje imie:"<<endl;
    cin>> pat;
    if (pat=="Patrycja")
    {
         cout<< "Jestes debilem";
    }

    else
    {
        cout<<"Jestes geniuszem";
    }
    return 0;
}
