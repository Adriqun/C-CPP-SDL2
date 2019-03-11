#include <iostream>

class MyVector {
	int size;
	double* arr;
public:
	MyVector(int &&newSize) {
		size = newSize;
		arr = new double[size];
		for (int i = 0; i < size; ++i)
			arr[i] = i;
	}

	MyVector(const MyVector &rhs) {
		size = rhs.size;
		arr = new double[size];
		for (int i = 0; i < size; ++i) {
			arr[i] = rhs.arr[i];
		}
	}

	MyVector(MyVector &&rhs) {
		size = rhs.size;
		arr = rhs.arr;
		rhs.arr = nullptr; // <- the most important line
	}

	~MyVector() {
		if (arr) {
			delete[] arr;
			arr = nullptr;
		}

		size = 0;
	}

	double getFirst() { return arr ? arr[0] : -1; }
};

MyVector getMyVector() {
	MyVector buffer(10);
	return buffer;
}

void relaymain(int &x) {
	std::cout << x;
}

template<typename T>
void relay(T&& arg) {
	relaymain(std::forward<T>(arg))
}

int main()
{
	// 1. Move semantics example (v3)
	MyVector v1(10);
	MyVector v2(v1);
	MyVector v3(getMyVector());
	std::cout << v1.getFirst() << " " << v2.getFirst() << " " << v3.getFirst();

	// 2. Perfect forwarding (no copying)
	// Calling relay() with rvalue and lvalue at the same time!
	relay(5);
	int i = 5;
	relay(i);

	return 0;
}