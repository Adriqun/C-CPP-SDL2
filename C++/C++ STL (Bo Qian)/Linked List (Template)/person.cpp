#include "person.h"

Person::Person(std::string name, int age)
{
	this->age = age;
	this->name = name;
}

Person::~Person()
{
	free();
}

void Person::free()
{
	age = 0;
	name = "";
}



void Person::setAge(int age)
{
	this->age = age;
}

void Person::setName(std::string name)
{
	this->name = name;
}

int Person::getAge()
{
	return age;
}

std::string Person::getName()
{
	return name;
}



std::ostream& operator<<(std::ostream& os, Person* person)
{
	os << "Name: " << person->getName() << " Age: " << std::to_string(person->getAge()) << std::endl;
	return os;
}

bool Person::operator==(Person* person) const
{
	if (person == nullptr) return false;

	if (age == person->getAge())
	{
		if (name == person->getName())
		{
			return true;
		}
	}
	
	return false;
}