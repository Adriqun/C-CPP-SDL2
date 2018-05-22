#include <iostream>

using namespace std;
string login, haslo;
int main()
{
    cout << "Witaj!" << endl;
    cout<< "Wprowadz login:"<< endl;
    cin>>login;
    cout<<"Wprowadz haslo:"<< endl;
    cin>>haslo;
    if((login=="admin")&&(haslo=="zupa"))
    {
    cout<<"Zalogowano sie pomyslnie";
    }
    else
    {
    cout<<"Wprowadzono zly login lub haslo";
    }
    return 0;
}
