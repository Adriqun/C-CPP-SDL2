#include <iostream>

using namespace std;
class Przycisk
{
    int w,s;
    string napis;
    public:
    Przycisk(int g=100,int h=25,string napis2="OK")
    {
        if(napis2==""||g<1||h<1)
            cout<<"Error!"<<endl;
        else
        {napis=napis2; w=h; s=g; }
    }
    void wypisz()
    {
        cout<<"Atrybuty: "<<endl;
        cout<<"Szerokosc: "<<s<<endl;
        cout<<"Wysokosc: "<<w<<endl;
        cout<<"Napis: "<<napis<<endl;
    }
};
int main()
{
    Przycisk p1;
    p1.wypisz();
    return 0;
}
