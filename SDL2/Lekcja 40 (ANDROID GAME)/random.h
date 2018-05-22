#ifndef RANDOM_H
#define RANDOM_H

class Random
{
    int x;
    int y;

public:

    Random();
    ~Random();
    int getX();
    int getY();

    void initRandom();
    void randomX( int startScope, int endScope );
    void randomY( int startScope, int endScope );
};

#endif // RANDOM_H
