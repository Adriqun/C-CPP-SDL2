#pragma once

struct Node {
	int key;
	Node* left;
	Node* right;

	Node(int key = 0);
	~Node();
};

class BST {
	int _size;
	Node* root;

	void printPrivate(Node* node);
	bool addPrivate(int key, Node* node);
	Node* getNodePrivate(int key, Node* node);

	int* findSmallest(Node* node);
	int* findGreatest(Node* node);

	void removePrivate(int key, Node* node);
	void removeRoot();
	void removeMatch(Node* parent, Node* match, bool left);

public:
	BST();
	~BST();
	int size();
	bool empty();

	void print();
	void printChildren(int key);
	bool add(int key);
	Node* getNode(int key);

	int* getRootKey();
	Node* getRootNode();

	int* getSmallest();
	int* getGreatest();

	void remove(int key);
};