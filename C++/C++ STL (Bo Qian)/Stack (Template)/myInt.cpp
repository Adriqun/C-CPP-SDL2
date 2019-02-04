#include "myInt.h"


MyInt::MyInt(int value)
{
	this->value = value;
}

MyInt::~MyInt()
{
	value = 0;
}

int MyInt::getValue()
{
	return value;
}

std::ostream& operator<<(std::ostream& os, MyInt* myInt)
{
	os << "Value: " << std::to_string(myInt->getValue()) << std::endl;
	return os;
}