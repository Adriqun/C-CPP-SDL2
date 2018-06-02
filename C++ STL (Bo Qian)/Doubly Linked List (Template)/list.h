#pragma once

template<class Data>
class List
{
	struct Node
	{
		Data* data;
		Node* next;
		Node* prev;

		Node(Data* data = nullptr);
		~Node();
	};

	int counter;
	Node* head;
	Node* tail;

public:
	List();
	~List();

	int& size();
	bool empty();

	// We don't allow to add identic two objects.
	bool push_back(Data* data);
	bool push_front(Data* data);
	bool pop_back();
	bool pop_front();

	Node* &begin();
	Node* &end();
	Node* search(Data* data);

	bool erase(Node* node);
	bool erase(Data* data);
	void swap(List* &list);

	void print();
	void print(Node* node);
};