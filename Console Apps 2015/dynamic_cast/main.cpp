#include <iostream>
#include <stdio.h>
#include <cstddef>

using namespace std;

class A
{

public:
    virtual void f()
    {
        cout << "A::f()" << endl;
    }
};

class B : public A
{

public:
    void f()
    {
        cout << "B::f()" << endl;
    }
};

/* Klasa B dziedziczy od klasy A, zmieniajac przy tym funkcje wirtualna f() */

int main()
{
    // tworzenie obiektow
    A a;
    B b;

    // wywolanie funkcji obiektow
    a.f();
    b.f();

    // tworzenie wskaznikow na obiekt
    A *pA = &a;
    B *pB = &b;

    // wywolanie funkcji wskaznikow na obiekt
    pA->f();
    pB->f();


    pA = &b;
    // pB = &a;      // not allowed, nie dozwolone
    pB = dynamic_cast<B*>(&a); // allowed but it returns NULL, dozwolone ale zwroci NULL'a

    if( pB == NULL )
    {
        printf( "\nObject is not type B\n" );
    }

    return 0;
}
