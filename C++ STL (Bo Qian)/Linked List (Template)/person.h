#pragma once
#include <string>
#include <iostream>

class Person
{
	std::string name;
	int age;

public:
	Person(std::string name = "", int age = 0);
	~Person();
	void free();

	void setAge(int age);
	void setName(std::string name);
	int getAge();
	std::string getName();

	bool operator==(Person* person) const;
};

std::ostream& operator<<(std::ostream& os, Person* person);