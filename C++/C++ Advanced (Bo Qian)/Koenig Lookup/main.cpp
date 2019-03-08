//#include <iostream>
//#include <string>

//void* operator new(std::size_t size) throw(std::bad_alloc)
//{
//	while (true)
//	{
//		void* pMem = malloc(size); // Allocate memory
//		if (pMem)
//			return pMem; // Return the memory if successful
//
//		std::new_handler handler = std::set_new_handler(0); // Get new handler.
//		std::set_new_handler(handler);
//
//		if (handler)
//			(*handler)(); // Invoke new handler
//		else
//			throw std::bad_alloc(); // If new handler is null throw exception
//		// in case of no more memory left the handler can be set as null etc.
//	}
//}
//
//int main() 
//{
//	int* a = new int(0);
//
//	if (a)
//		delete a;
//	
//	return 0;
//}


#include <iostream>
#include <numeric>
namespace A
{
	struct X {};
	void g(X x) { std::cout << "calling A::g()\n"; }
}

struct B
{
	void g(A::X x) { std::cout << "calling B::g()\n"; }
};

class C : public B {
public:
	void j() {
		A::X x;
		g(x);
	}
};

namespace D
{
	struct X {};
	void h(X x) {}
	void h() {}
}

//namespace E {
//	struct F {};
//	int operator+(E::F, int n) { return n + 1; }
//}

int main()
{
	A::X x;
	g(x); // koenig lookup
	C c;
	c.j();

	D::X d;
	h(d);
	//h(); // error

	// without koenig lookup code looks ugly
	std::operator<<(std::cout, "Hello");

	//E::F arr[3];
	//std::accumulate(arr, arr + 3, 0);

	return 0;
}