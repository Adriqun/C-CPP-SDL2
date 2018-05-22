#include <iostream>
using namespace std;
void przyklad()
{
    cout<<"Przedstawiam przyklad!"<<endl;
}
namespace Adrian
{
namespace Adrian2
{
void iLikeThis()
{
    przyklad();
}
namespace Adrian3
{
class test
{
public:
    void sprawdzian()
    {
        cout<<"DZIALA!"<<endl;
    }

};
}
}
}

int main()
{
    Adrian::Adrian2::Adrian3::test t;
    t.sprawdzian();
    Adrian::Adrian2::iLikeThis();
    return 0;
}

