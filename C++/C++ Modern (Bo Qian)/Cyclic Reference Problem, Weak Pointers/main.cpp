#include <iostream>
#include <string>
#include <memory>

class Dog
{
	//std::shared_ptr<Dog> m_pFriend; // cyclic reference
	std::weak_ptr<Dog> m_pFriend; // Dog* m_pFriend;
public:
	std::string m_name;
	void bark() { std::cout << "Dog " << m_name << " rules!\n"; }
	Dog(std::string newName) { std::cout << "Dog is created: " << newName << "\n"; m_name = newName; }
	~Dog() { std::cout << "Dog is destroyed: " << m_name << "\n"; }
	void makeFriend(std::shared_ptr<Dog> f) { m_pFriend = f; }
	void showFriend() {
		if (!m_pFriend.expired())
			std::cout << "My friend is " << m_pFriend.lock()->m_name << "\n";
		std::cout << "He is owned by " << m_pFriend.use_count() << "\n";
	}
};

int main()
{
	std::shared_ptr<Dog> pD1(new Dog("Gunner"));
	std::shared_ptr<Dog> pD2(new Dog("Smokey"));
	pD1->makeFriend(pD2);
	pD2->makeFriend(pD1);
	pD1->showFriend();
	return 0;
}