#include "animal.h"

Animal::Animal(int age)
{
	this->age = age;
}

Animal::Animal(Animal* animal)
{
	this->age = animal->getAge();
}

Animal::~Animal()
{
	age = 0;
}

int Animal::getAge()
{
	return age;
}

void Animal::setAge(int age)
{
	this->age = age;
}

std::ostream& operator<<(std::ostream& os, Animal* &animal)
{
	if (animal != nullptr)
	{
		os << "Name: " << animal->getName()
			<< " Age: " << std::to_string(animal->getAge())
			<< " Weight: " << std::to_string(animal->getWeight())
			<< " " << animal->make_sound();
	}
	
	return os;
}

bool Animal::operator==(Animal* &animal)
{
	if (this->getAge() == animal->getAge())
	{
		if (this->getWeight() == animal->getWeight())
		{
			if (this->getName() == animal->getName())
			{
				return true;
			}
		}
	}

	return false;
}



Pet::Pet(std::string name, int age) :Animal(age)
{
	this->name = name;
}

Pet::Pet(Pet* pet)
{
	this->age = pet->getAge();
	this->name = pet->getName();
}

Pet::~Pet()
{
	name = "";
}

std::string Pet::getName()
{
	return name;
}

void Pet::setName(std::string name)
{
	this->name = name;
}



Mammal::Mammal(int weight, int age) :Animal(age)
{
	this->weight = weight;
}

Mammal::Mammal(Mammal* mammal)
{
	this->age = mammal->getAge();
	this->weight = mammal->getWeight();
}

Mammal::~Mammal()
{
	weight = 0;
}

int Mammal::getWeight()
{
	return weight;
}

void Mammal::setWeight(int weight)
{
	this->weight = weight;
}



Dog::Dog(std::string name, int weight, int age) :Pet(name), Mammal(weight), Animal(age)
{
	// ...
}

Dog::Dog(Dog* dog)
{
	this->age = dog->getAge();
	this->name = dog->getName();
	this->weight = dog->getWeight();
}

Dog::~Dog()
{
	// ...
}

std::string Dog::make_sound()
{
	return "Woof woof";
}



Cat::Cat(std::string name, int weight, int age) :Pet(name), Mammal(weight)
{
	this->age = age;
}

Cat::Cat(Cat* cat)
{
	this->age = cat->getAge();
	this->name = cat->getName();
	this->weight = cat->getWeight();
}

Cat::~Cat()
{
	// ...
}

std::string Cat::make_sound()
{
	return "Meow meow";
}