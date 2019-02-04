#include <iostream>

using namespace std;
string nazwa;
int main()
{
    cout << "Wpisz nazwe a ja podam Ci wszystkie jego mozliwosci" << endl;
    cin >> nazwa;

    cout<<nazwa[0]<<nazwa[1]<<nazwa[2]<<nazwa[3]<<endl;
    cout<<nazwa[0]<<nazwa[1]<<nazwa[3]<<nazwa[2]<<endl;
    cout<<nazwa[0]<<nazwa[2]<<nazwa[3]<<nazwa[1]<<endl;
    cout<<nazwa[0]<<nazwa[2]<<nazwa[1]<<nazwa[3]<<endl;
    cout<<nazwa[0]<<nazwa[3]<<nazwa[2]<<nazwa[1]<<endl;
    cout<<nazwa[0]<<nazwa[3]<<nazwa[1]<<nazwa[2]<<endl;

    cout<<nazwa[1]<<nazwa[0]<<nazwa[2]<<nazwa[3]<<endl;
    cout<<nazwa[1]<<nazwa[0]<<nazwa[3]<<nazwa[2]<<endl;
    cout<<nazwa[1]<<nazwa[2]<<nazwa[3]<<nazwa[0]<<endl;
    cout<<nazwa[1]<<nazwa[2]<<nazwa[0]<<nazwa[3]<<endl;
    cout<<nazwa[1]<<nazwa[3]<<nazwa[2]<<nazwa[0]<<endl;
    cout<<nazwa[1]<<nazwa[3]<<nazwa[0]<<nazwa[2]<<endl;

    cout<<nazwa[2]<<nazwa[1]<<nazwa[0]<<nazwa[3]<<endl;
    cout<<nazwa[2]<<nazwa[1]<<nazwa[3]<<nazwa[0]<<endl;
    cout<<nazwa[2]<<nazwa[3]<<nazwa[0]<<nazwa[1]<<endl;
    cout<<nazwa[2]<<nazwa[3]<<nazwa[1]<<nazwa[0]<<endl;
    cout<<nazwa[2]<<nazwa[0]<<nazwa[1]<<nazwa[3]<<endl;
    cout<<nazwa[2]<<nazwa[0]<<nazwa[3]<<nazwa[1]<<endl;

    cout<<nazwa[3]<<nazwa[0]<<nazwa[2]<<nazwa[1]<<endl;
    cout<<nazwa[3]<<nazwa[0]<<nazwa[1]<<nazwa[2]<<endl;
    cout<<nazwa[3]<<nazwa[2]<<nazwa[0]<<nazwa[1]<<endl;
    cout<<nazwa[3]<<nazwa[2]<<nazwa[1]<<nazwa[0]<<endl;
    cout<<nazwa[3]<<nazwa[1]<<nazwa[2]<<nazwa[0]<<endl;
    cout<<nazwa[3]<<nazwa[1]<<nazwa[0]<<nazwa[2]<<endl;



    return 0;
}
