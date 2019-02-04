#include <iostream>

using namespace std;
int w;
int main()
{
    cout << "Witaj!" << endl;
    cout<<"Ile masz lat?";
    cin>> w;
    if ((w>=18)&&(w<35))
    cout<<"Jestes pelnoletni i nie mozesz kandydowac";
    else if (w>=35)
    cout<<"Jesteœ pelnoletni i mozesz kandydowac";
    else
    cout<<"Nie jestes pelnoletni i nie mozesz kandydowac";
    return 0;
}
