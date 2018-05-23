#include <iostream>

using namespace std;

class Ksztalt
{
    public:
    virtual void figura()=0;
};
class Kolo :public Ksztalt
{
    void figura();
};
class Kwadrat:public Ksztalt
{
    void figura();
};
class Trojkat:public Ksztalt
{
    void figura();
};
class Trapez:public Ksztalt
{
    void figura();
};
