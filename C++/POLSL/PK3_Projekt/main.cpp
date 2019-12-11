/*
	File: main.cpp
	Author: Adrian Michalek
	Github: https://github.com/devmichalek
	Github (directly): https://github.com/devmichalek/Tutorials/tree/master/C%2B%2B/POLSL/PK3_Projekt
	Information:
		- File contains examples of predefined classes.
*/

#include "queue.h"
#include <vector>

void TestClassNode()
{
	std::cout << "TestClassNode:" << std::endl;
	{
		Node<int> n1(0);
		Node<int> n2(1);
		Node<int> n3(2);
		std::cout << "n1 = " << n1.m_data << " = 0" << std::endl;
		std::cout << "n2 = " << n2.m_data << " = 1" << std::endl;
		std::cout << "n3 = " << n3.m_data << " = 2" << std::endl;
	}
	
	{
		Node<int> n1(0);
		Node<int> n2(1);
		std::cout << "n1 = " << n1.m_data << " = 0" << std::endl;
		n1 = n2;
		std::cout << "n1 = " << n1.m_data << " = 1" << std::endl;
		Node<int> n3(3);
		std::cout << "n2 = " << n2.m_data << " = 1" << std::endl;
		n2 = n3;
		std::cout << "n2 = " << n2.m_data << " = 3" << std::endl;
	}

	{
		Node<int>* n1 = new Node<int>(1);
		Node<int>* n2 = new Node<int>(1);
		std::cout << "Allocated: " << Node<int>::allocated() << " = 24 bytes" << std::endl;
		delete n1;
		std::cout << "Left bytes: " << Node<int>::allocated() << " = 12 bytes" << std::endl;
		delete n2;
		std::cout << "Left bytes: " << Node<int>::allocated() << " = 0 bytes" << std::endl;
	}

	std::cout << std::endl;
}

void TestClassGuard()
{
	std::cout << "TestClassGuard:" << std::endl;

	{
		Node<int>* toDelete;
		Guard<int, false> guard;

		{
			Guard<int, false> guard;
			Node<int>* n1 = new Node<int>(1);
			toDelete = n1;
		}
		
		delete toDelete;
	}

	{
		std::vector<Node<char>*> toDelete;
		Guard<char, false> guard;

		{
			Guard<char, false> guard;
			Node<char>* n1 = new Node<char>(1);
			Node<char>* n2 = new Node<char>(1, n1);
			Node<char>* n3 = new Node<char>(1, n1, n2);
			Node<char>* n4 = new Node<char>(1, n3, n2);
			toDelete.push_back(n1);
			toDelete.push_back(n2);
			toDelete.push_back(n3);
			toDelete.push_back(n4);
		}

		for (auto& it : toDelete)
		{
			delete it;
			it = nullptr;
		}
		toDelete.clear();
	}

	{
		Node<__int64>* toDelete;
		Guard<__int64> guard;

		{	// Real guard
			Guard<__int64> guard;
			Node<__int64>* n1 = new Node<__int64>(1);
			toDelete = n1;
		}

		delete toDelete;
	}
	

	std::cout << std::endl;
}

void TestClassDoublyLinkedList()
{
	std::cout << "TestClassDoublyLinkedList:" << std::endl;

	Guard<int> guard1;
	Guard<char> guard2;
	Guard<__int64> guard3;

	{
		Guard<int> guardl1;
		DoublyLinkedList<int> dll1;
		std::cout << dll1 << " = empty" << std::endl;
		dll1.insert(1);
		const int tmp = 2;
		dll1.insert(tmp);
		dll1.insert(3);
		std::cout << dll1 << " = 1 2 3" << std::endl;
		dll1.clear();
		std::cout << dll1.size() << " = 0" << std::endl;
	}

	{
		Guard<int> guardl1;
		DoublyLinkedList<int> dll1;
		dll1.insert(1);
		const int tmp = 10;
		dll1.insert(tmp);
		dll1.insert(3);
	}

	{
		Guard<int> guardl1;
		DoublyLinkedList<int> dll1;
		std::vector<bool> results;
		dll1.insert(1);
		dll1.insert(2);
		dll1.insert(3);
		dll1.insert(4);
		dll1.insert(5);
		dll1.insert(6);
		std::cout << dll1 << " = 1 2 3 4 5 6" << std::endl;
		results.push_back(dll1.remove(uint64_t(0)));
		std::cout << dll1 << " = 2 3 4 5 6" << std::endl;
		results.push_back(dll1.pop_front());
		std::cout << dll1 << " = 3 4 5 6" << std::endl;
		results.push_back(dll1.remove(uint64_t(1)));
		std::cout << dll1 << " = 3 5 6" << std::endl;
		results.push_back(dll1.remove(uint64_t(dll1.size() - 1)));
		std::cout << dll1 << " = 3 5" << std::endl;

		results.push_back(dll1.remove(uint64_t(dll1.size())));
		results.push_back(dll1.remove(uint64_t(111)));
		results.push_back(dll1.remove(uint64_t(1)));
		results.push_back(dll1.pop_front());
		results.push_back(dll1.pop_front());

		std::cout << "[" << results[0] << ", 1]" << std::endl;
		std::cout << "[" << results[1] << ", 1]" << std::endl;
		std::cout << "[" << results[2] << ", 1]" << std::endl;
		std::cout << "[" << results[3] << ", 1]" << std::endl;
		std::cout << "[" << results[4] << ", 0]" << std::endl;
		std::cout << "[" << results[5] << ", 0]" << std::endl;
		std::cout << "[" << results[6] << ", 1]" << std::endl;
		std::cout << "[" << results[7] << ", 1]" << std::endl;
		std::cout << "[" << results[8] << ", 0]" << std::endl;
	}

	{
		Guard<__int64> guard1;
		DoublyLinkedList<__int64> dll1;
		dll1.insert(1);
		dll1.insert(2);
		dll1.insert(3);
		DoublyLinkedList<__int64> dll2(dll1);
		DoublyLinkedList<__int64> dll3(std::move(dll2));
		std::cout << dll1 << " = " << dll2 << " = " << dll3 << std::endl;
		dll1.pop_front();
		dll2.remove(uint64_t(1));
		dll3.remove(uint64_t(dll3.size() - 1));
		std::cout << dll1 << " = 2 3" << std::endl;
		std::cout << dll2 << " = 1 3" << std::endl;
		std::cout << dll3 << " = 1 2" << std::endl;
	}

	{
		Guard<char> guard1;
		DoublyLinkedList<char> dll1;
		dll1.insert('a');
		dll1.insert('b');
		dll1.insert('c');
		DoublyLinkedList<char> dll2 = dll1;
		DoublyLinkedList<char> dll3 = std::move(dll2);
		std::cout << dll1 << " = " << dll2 << " = " << dll3 << std::endl;

		dll1.pop_front();
		dll2.remove(uint64_t(1));
		dll3.remove(uint64_t(dll3.size() - 1));
		std::cout << dll1 << " = b c" << std::endl;
		std::cout << dll2 << " = a c" << std::endl;
		std::cout << dll3 << " = a b" << std::endl;
	}

	{
		Guard<int> guardl1;
		DoublyLinkedList<int> dll1;
		const Node<int>* tmp1, *tmp2;
		std::cout << dll1.front() << std::endl;
		std::cout << dll1.back() << std::endl;
		dll1.insert(1);
		tmp1 = dll1.head();
		tmp2 = dll1.tail();
		std::cout << dll1.front() << " = 1 = " << tmp1->m_data << std::endl;
		std::cout << dll1.back() << " = 1 = " << tmp2->m_data << std::endl;
		dll1.insert(2);
		tmp1 = dll1.head();
		tmp2 = dll1.tail();
		std::cout << dll1.front() << " = 1 = " << tmp1->m_data << std::endl;
		std::cout << dll1.back() << " = 2 = " << tmp2->m_data << std::endl;
		dll1.insert(3);
		tmp1 = dll1.head();
		tmp2 = dll1.tail();
		std::cout << dll1.front() << " = 1 = " << tmp1->m_data << std::endl;
		std::cout << dll1.back() << " = 3 = " << tmp2->m_data << std::endl;
		dll1.pop_front();
		tmp1 = dll1.head();
		tmp2 = dll1.tail();
		std::cout << dll1.front() << " = 2 = " << tmp1->m_data << std::endl;
		std::cout << dll1.back() << " = 3 = " << tmp2->m_data << std::endl;
		dll1.insert(4);
		dll1.insert(5);
		tmp1 = dll1.head();
		tmp2 = dll1.tail();
		std::cout << dll1.front() << " = 2 = " << tmp1->m_data << std::endl;
		std::cout << dll1.back() << " = 5 = " << tmp2->m_data << std::endl;
		dll1.remove(dll1.size());
		dll1.remove(dll1.size() - 1);
		tmp1 = dll1.head();
		tmp2 = dll1.tail();
		std::cout << dll1.front() << " = 2 = " << tmp1->m_data << std::endl;
		std::cout << dll1.back() << " = 4 = " << tmp2->m_data << std::endl;
	}

	{
		Guard<char> guard1;
		DoublyLinkedList<char> dll1;
		dll1.insert('a');
		dll1.insert('b');
		dll1.insert('c');
		DoublyLinkedList<char> dll2;
		dll2.insert('d');
		dll2.insert('e');
		dll2 += dll1;
		DoublyLinkedList<char> dll3;
		dll3.insert('f');
		dll3.insert('g');
		dll3 += std::move(dll1);
		std::cout << dll1 << " = a b c" << std::endl;
		std::cout << dll2 << " = d e a b c" << std::endl;
		std::cout << dll3 << " = f g a b c" << std::endl;

		dll1.pop_front();
		dll2.remove(uint64_t(1));
		dll3.remove(uint64_t(dll3.size() - 1));
		std::cout << dll1 << " = b c" << std::endl;
		std::cout << dll2 << " = d a b c" << std::endl;
		std::cout << dll3 << " = f g a b" << std::endl;
	}

	std::cout << std::endl;
}

void TestClassQueue()
{
	std::cout << "TestClassQueue:" << std::endl;

	Guard<int> guard1;
	Guard<char> guard2;
	Guard<__int64> guard3;

	{
		Queue<int> q1;
		std::cout << q1 << std::endl;
		q1.insert(1);
		const int tmp = 2;
		q1.insert(tmp);
		std::cout << q1 << " = 1 2" << std::endl;
		q1.insert(3);
		std::cout << q1 << " = 1 2 3" << std::endl;
		std::cout << Queue<int>::count() << " = 1" << std::endl;
		Queue<char> dll2;
		std::cout << Queue<char>::count() << " = 1" << std::endl;
		Queue<int> dll3;
		std::cout << Queue<int>::count() << " = 2" << std::endl;
	}

	{
		Queue<int> q1;
		std::cout << q1 << std::endl;
		q1.insert(1);
		q1.insert(2);
		q1.insert(3);
		q1.insert(4);
		std::cout << q1 << " = 1 2 3 4" << std::endl;
		std::cout << q1.size() << " = 4" << std::endl;
		q1.remove();
		std::cout << q1 << " = 2 3 4" << std::endl;
		q1.remove();
		std::cout << q1 << " = 3 4" << std::endl;
		std::cout << q1.size() << " = 2" << std::endl;
		q1.remove();
		std::cout << q1 << " = 4" << std::endl;
		q1.remove();
		std::cout << q1 << std::endl;
	}

	{
		Queue<int> q1;
		std::cout << q1 << std::endl;
		q1.insert(1);
		std::cout << q1.front() << " = 1" << std::endl;
		std::cout << q1.back() << " = 1" << std::endl;
		q1.insert(2);
		std::cout << q1.front() << " = 1" << std::endl;
		std::cout << q1.back() << " = 2" << std::endl;
		q1.insert(3);
		std::cout << q1.front() << " = 1" << std::endl;
		std::cout << q1.back() << " = 3" << std::endl;
		q1.insert(4);
		std::cout << q1.front() << " = 1" << std::endl;
		std::cout << q1.back() << " = 4" << std::endl;
		q1.remove();
		std::cout << q1.front() << " = 2" << std::endl;
		std::cout << q1.back() << " = 4" << std::endl;
		q1.remove();
		std::cout << q1.front() << " = 3" << std::endl;
		std::cout << q1.back() << " = 4" << std::endl;
		q1.remove();
		std::cout << q1.front() << " = 4" << std::endl;
		std::cout << q1.back() << " = 4" << std::endl;
		q1.remove();
		std::cout << q1.front() << std::endl;
		std::cout << q1.back() << std::endl;
	}

	{
		Queue<int> q1;
		std::cout << q1 << std::endl;
		q1.insert(1);
		q1.insert(2);
		q1.insert(3);
		q1.insert(4);
		std::cout << q1.size() << " = 4" << std::endl;
		std::cout << q1 << " = 1 2 3 4" << std::endl;
		q1.clear();
		std::cout << q1.size() << " = 0" << std::endl;
		std::cout << q1 << std::endl;
	}

	{
		Queue<__int64> q1;
		q1.insert(1);
		q1.insert(2);
		q1.insert(3);
		Queue<__int64> q2(q1);
		Queue<__int64> q3(std::move(q1));
		std::cout << q1 << " " << q2 << " " << q3 << std::endl;
		q2.remove();
		q3.remove();
		q3.remove();
		std::cout << q1 << " " << q2 << " " << q3 << std::endl;
	}

	{
		Queue<__int64> q1;
		q1.insert(1);
		q1.insert(2);
		q1.insert(3);
		Queue<__int64> q2 = q1;
		Queue<__int64> q3 = std::move(q1);
		std::cout << q1 << " " << q2 << " " << q3 << std::endl;
		q2.remove();
		q3.remove();
		q3.remove();
		std::cout << q1 << " " << q2 << " " << q3 << std::endl;
	}

	{
		Queue<__int64> q1;
		q1.insert(1);
		q1.insert(2);
		q1.insert(3);
		Queue<__int64> q2;
		q2.insert(4);
		q2.insert(5);
		q2 += q1;
		Queue<__int64> q3;
		q3.insert(6);
		q3.insert(7);
		q3 += std::move(q1);
		std::cout << q1 << " " << q2 << " " << q3 << std::endl;
		q2.remove();
		q3.remove();
		q3.remove();
		std::cout << q1 << " " << q2 << " " << q3 << std::endl;
	}

	std::cout << std::endl;
}

int main()
{
	TestClassNode();
	TestClassGuard();
	TestClassDoublyLinkedList();
	TestClassQueue();
	return 0;
}