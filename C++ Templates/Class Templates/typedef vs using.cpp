#include <iostream>
#include <deque>
using namespace std;

// using is more readable
typedef int INT;
using CHAR = char;


// example of template
template<class Type, class Data = deque<Type>>
class Stack {};

// 1 - ready made value type
using STACK = Stack<int>;

// 2 - whatever type we want to have
template<typename Type>
using DEQUE = Stack<Type, deque<Type>>;

int main()
{
	INT a;
	CHAR b;
	STACK c;
	DEQUE <char> d;	// instead of Stack<char, deque<char>> d;

	return 0;
}