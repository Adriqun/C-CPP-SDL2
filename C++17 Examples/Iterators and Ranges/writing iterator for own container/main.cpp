#include <cassert>
#include <cstdio>
#include <iterator>

struct Node
{
	int data;
	Node* next;
};

class Iterator
{
	Node* nodeptr;
	friend class List;
	explicit Iterator(Node* p) : nodeptr(p) {}

public:
	int& operator*() const		{ return nodeptr->data; }
	Iterator& operator++()		{ nodeptr = nodeptr->next; return *this; }
	Iterator operator++(int)	{ auto result = *this; ++*this; return result; }

	bool operator==(const Iterator& i) const { return nodeptr == i.nodeptr; }
	bool operator!=(const Iterator& i) const { return nodeptr != i.nodeptr; }
};

class List
{
	Node* head = nullptr;
	Node* tail = nullptr;
	// ...
public:
	void add(int newData)
	{
		if (!head)
		{
			head = new Node;
			head->data = newData;
			head->next = nullptr;
			tail = head;
		}
		else
		{
			Node* tmp = head;
			while (tmp->next)
				tmp = tmp->next;

			tmp->next = new Node;
			tmp->next->data = newData;
			tmp->next->next = nullptr;
			tail = tmp;
		}
	}

	Iterator begin()	{ return Iterator{ head }; }
	Iterator end()		{ return Iterator{ nullptr }; }
};

template<class Container, class Predicate>
int count_if(Container& ctr, Predicate pred)
{
	int sum = 0;
	for (auto it = ctr.begin(); it != ctr.end(); ++it)
	{
		if (pred(*it))
		{
			sum += 1;
		}
	}

	return sum;
}

int main()
{
	List list;
	list.add(5);
	list.add(4);
	list.add(34);
	list.add(91);
	list.add(7);

	auto pred = [](int& i) { return i > 5; };

	int s = count_if(list, pred);

	return 0;
}
