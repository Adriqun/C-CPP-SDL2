#pragma once
#include <iostream>
#include <string>

class MyInt
{
	int value;

public:
	MyInt(int value);
	~MyInt();
	int getValue();
	friend std::ostream& operator<<(std::ostream& os, MyInt* myInt);
};