#pragma once
#include <string>
#include <iostream>

class Animal
{
protected:
	int age;
public:
	Animal(int age = 0);
	Animal(Animal* animal);
	virtual ~Animal();

	int getAge();
	void setAge(int age);

	virtual std::string getName() = 0;
	virtual int getWeight() = 0;
	virtual std::string make_sound() = 0;

	// Print.
	friend std::ostream& operator<<(std::ostream& os, Animal* &animal);
	bool operator==(Animal* &animal);
};

class Pet :public virtual Animal
{
protected:
	std::string name;
public:
	Pet(std::string name = "", int age = 0);
	Pet(Pet* pet);
	virtual ~Pet();
	std::string getName();
	void setName(std::string name);
};

class Mammal :public virtual Animal
{
protected:
	int weight;
public:
	Mammal(int weight = 0, int age = 0);
	Mammal(Mammal* mammal);
	virtual ~Mammal();
	int getWeight();
	void setWeight(int weight);
};

class Dog :public Pet, Mammal
{
public:
	Dog(std::string name = "", int weight = 0, int age = 0);
	Dog(Dog* dog);
	~Dog();
	std::string make_sound();
};

class Cat :public virtual Pet, virtual Mammal
{
public:
	Cat(std::string name = "", int weight = 0, int age = 0);
	Cat(Cat* cat);
	~Cat();
	std::string make_sound();
};