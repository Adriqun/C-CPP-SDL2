struct Dog
{
	Dog dog() { return *this; }
};

int sum(int a, int b) { return a + b; }

int main()
{
	// lvalue - An object that occupies some identifiable location in memory
	// rvalue - Any object that is not a lvalue

	// lvalue examples
	int i;	// i is a lvalue
	int* p = &i; // i's address is identifiable
	i = 2; // memory content is modified
	Dog d1; // lvalue of user defined object

	// rvalue examples
	int x = 2;	// 2 is an rvalue
	int x = i + 2;	// (i + 2) is an rvalue
	int* p = &(i + 2); // error
	i + 2 = 4;	// error
	2 = i;	// error
	d1 = d1.dog(); // dog() is rvalue of user defined type

	int i = sum(3, 5); // sum(3, 5) is rvalue 

	return 0;
}