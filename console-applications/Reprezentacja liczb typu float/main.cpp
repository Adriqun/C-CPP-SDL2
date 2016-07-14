#include <iostream>
#include <cmath>
using namespace std;
void printfloat(float x)
 {
        unsigned char adres[4];
        unsigned char * wtab = adres ;
        *(reinterpret_cast<float*>(wtab)) = x;

        for(int i = 3; i >= 0; i--)
        cout << hex<<static_cast<int>(adres[i]) << " ";
        cout<<"\n";
}
int main()
{
    int t;
    float x;
    cin>>t;
    while (t--)
    {
      cin>>x;
    printfloat(x);
    }

}
