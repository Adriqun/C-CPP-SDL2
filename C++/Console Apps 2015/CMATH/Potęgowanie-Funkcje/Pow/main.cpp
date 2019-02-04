#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
long long int x;
unsigned int y;
int main()
{
    x=pow(2,32)-1; // funkcja pow (podstawa,wykladnik)
    y=x;
    cout<<setprecision(30);
    cout <<x<< endl;
    cout <<y<< endl;
    return 0;
}
