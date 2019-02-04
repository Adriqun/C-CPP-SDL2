#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    string napis="Maciek ma psa";

    transform (napis.begin(), napis.end(), napis.begin(),::toupper);
    cout<<napis<<endl;
    transform (napis.begin(), napis.end(), napis.begin(),::tolower);
    cout<<napis<<endl;
    return 0;
}
