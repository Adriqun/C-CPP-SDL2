#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

class Human {
protected:
	int age;
public:
	Human(): age(0) {
		cout << "Human constructor-----------" << endl;
	}

	virtual ~Human() {
		age = 0;
		cout << "Human destructor------------" << endl;
	}

	const int& getAge() const {
		return age;
	}

	virtual string sound() {
		return "I am Human";
	}

	friend ostream& operator<<(ostream& os, Human& human) {
		os << human.sound() << "\n";
		return os;
	}
};

class Student :virtual public Human {
protected:
	string name;
public:
	Student(string name) {
		this->name = name;
		cout << "Student " + name + " constructor" << endl;
	}
	
	virtual ~Student() {
		cout << "Student " + name + " destructor" << endl;
		name = "";
		age = 0;
	}

	void setAge(int age) {
		this->age = age;
	}

	virtual string sound() {
		return "I am Student";
	}
};

class Faculty :virtual public Human {
protected:
	string type;
public:
	Faculty(string type) {
		this->type = type;
		cout << "Faculty " +type +" constructor" << endl;
	}

	virtual ~Faculty() {
		cout << "Faculty " + type + " destructor" << endl;
		type = "";
		age = 0;
	}

	void setAge(int age) {
		this->age = age;
	}

	virtual string sound() {
		return "I am Faculty";
	}
};

class TA :public Student, Faculty {
public:
	TA(string name, string type): Student(name), Faculty(type) {
		cout << "TA " + name + " " + type + " constructor" << endl;
	}

	~TA() {
		cout << "TA " + name + " " + type + " destructor" << endl;
	}

	virtual string sound() {
		return "I am FA";
	}
};

struct comparator1
{
	bool operator()(const char& a, const char& b) const
	{
		return a > b;
	}
};

int main()
{
	// Interesting.
	/*typedef function<bool(const char& a, const char& b)> Comparator;
	Comparator comparator2 =
	[](const char& a, const char& b)
	{
		return a > b;
	};
	map<char, Human*, Comparator> people(comparator2);*/

	map<char, Human*, comparator1> people;

	people.emplace(make_pair('g', new TA("Jack", "Maths")));
	people.insert(pair<char, Human*>('b', new Student("Ann")));
	people.emplace(pair<char, Human*>('j', new Human));
	people.insert(make_pair('x', new Faculty("Physics")));
	people.emplace(make_pair('a', new TA("Gabrielle", "English")));

	for (auto &it : people) {
		cout << "Key: " << to_string(it.first) << " " << *it.second;
	}
	cout << endl;

	map<char, Human*>::iterator it = people.find('g');
	delete it->second;
	people.erase(it);

	for (auto &it : people) {
		cout << "Key: " << to_string(it.first) << " " << *it.second;
	}
	cout << endl;

	for (;;) {
		if (people.empty()) {
			break;
		}

		delete people.begin()->second;
		people.erase(people.begin());
	}

	cout << people.size();

	return 0;
}
