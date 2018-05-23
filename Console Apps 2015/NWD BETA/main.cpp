#include <iostream>

using namespace std;
int a,b, i=0, szukana;
long long testy;


int main()
{
    cin>>testy;
    for (int g=1;g<=testy;g++)
    {
    cin>>a>>b;
    while ((i<a)||(i<b))
    {   i++;
        if(( (i<=a)  ||  (i<=b) && (a%i==0)&&(b%i==0))
        {
         szukana=i;
        }
    }
    cout<<szukana<<endl;
    i=0;
    }
   return 0;
}
