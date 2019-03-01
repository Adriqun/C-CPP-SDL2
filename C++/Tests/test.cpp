// const
// A compile time constraint that an object can no be modified

// 1.1 What is the output of the following code?
void func(int* x)
{
	*x = 7;
}

int main()
{
	const int a = 3;
	int* ptr;
	ptr = const_cast<int*>(&a);
	std::cout << "A=" << a << std::endl;
	*ptr = 5;
	std::cout << "A=" << a << std::endl;
	*((int*)(&a)) = 6;
	std::cout << "A=" << a << std::endl;
	func((int*)(&a));
	std::cout << "A=" << a << std::endl;
	return 0;
}

// 1.2 Add comments next to p1, p2, p3 and p4, what is const in this line?
//	   Describe "const" with pointers and objects.
int main()
{
	int i;
	const int* p1 = &i;			// comment here
	p1++;
	int* const p2 = &i;			// comment here
	const int* const p3 = &i;	// comment here
	int const* p4 = &i;			// comment here
}

// 1.3 What is the output (and why) of the following code?
int main()
{
	int i = 2;
	const int& ref = i;
	const int* ptr = &i;

	i = 2;
	const_cast<int&>(ref) = 3;
	*const_cast<int*>(ptr) = 4;

	cout << i << ' ' << ref << ' ' << *ptr;
}