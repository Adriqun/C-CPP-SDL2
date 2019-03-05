1.1
	It depends...
	Based on compilator you have answer may look like:
	GCC:
		A=3
		A=5
		A=6
		A=7
	G++:
		A=3
		A=3
		A=3
		A=3
	Most modern compilators does not allow to change value of const object via pointers.

1.2
	int main()
	{
		int i;
		const int* p1 = &i;			// data is const
		p1++;
		int* const p2 = &i;			// pointer is const
		const int* const p3 = &i;	// data and pointer is const
		int const* p4 = &i;			// data is const
	}

	If const is on the left of *, data is const
	If const is on the right of *, pointer is const

1.3
	Correct output is:
	4 4 4
	The ref const int is a reference to int.
	The ptr also const int is a pointer which points to the address of int.
	We cannot change the ptr and ref because they are const.
	We use const_cast to cast away constness of these objects, but
	these objects points to not const object which can be modified.



1.4
	The code wouldn't compile because of:
	void printDogName() const { cout << getName() << " const" << endl; }

	The function above is const which means variables cannot be modified and
	it can only invoke const functions.

	1. First solution (change getName() to const function)
	const string& getName() const { return name; }

	2. Second solution (change invoking getName() function into variable)
	void printDogName() const { cout << name << " const" << endl; }

	The correct output is:
	dummy not const
	dummy not const
	dummy not const
	dummy const

1.5
	The function is const.
	The function returns constant pointer which points to constant integer.
	The function parameter is a reference of a constant pointer pointing to constant integer.

1.6
	First solution is a keyword "mutable"
	mutable int accessCounter; // This variable is now allowed to be changed in const function

	Second solution is to keep accessCounter as not mutable.
	const_cast <BigArray*>(this)->accessCounter++; // Cast away

1.7
	Output is gh
	The expression (p += sizeof(int))[-1] can be written as (p += 4)[-1] which can be written
	as (p = p+4)[-] which returns address p+3 which is address of fourth element in argv[].

1.8
	Output is 2 3 5 6
	int main()
	{
		int a[][3] = { 1, 2, 3, 4, 5, 6 };
		int(*ptr)[3] = a; // ptr is now {1, 2, 3}
		printf("%d %d ", (*ptr)[1], (*ptr)[2]);
		++ptr; // ptr is now {4, 5, 6}
		printf("%d %d\n", (*ptr)[1], (*ptr)[2]);
		return 0;
	}

2.1
	First solution (c++11):
	Human(Human &h) = delete;
	Second solution (c++03), declare the function to be private, and not define it:
	private:
		Human(Human &h);

2.2
	Private destructors can only be stored on heap, knowing that the only possible way of using
	class Human is via pointers. By adding public function:
	void destroyMe() { delete this; }
	and in the main function:
	of->destroyMe();
	We freed the memory correctly.

2.3
	As long as you define constructor that takes parameters (class Dog), the compiler will failed
	in case of invoking default constructor.
	The output of the following code is compiler error "no default constructor" or sth like this.

2.4
	Shared ptr is the only that can be considered to use in this example:
	static std::shared_ptr<Dog> createYellowDog()
	{
		return std::shared_ptr<Yellowdog>(new Yellowdog());
	}
	All standard c++ containers have no virtual destructors.

2.5
	malloc() - allocates the memory and returns the pointer to the allocated memory.
	calloc() - does the same job as malloc() except it fills allocated memory with zeros.
	realloc() - changes the size of memory block on heap, frees if new size is smaller.

2.6
	Deleting c Collar before creating new Collar is not safe. The first solution:
	Dog& operator=(const Dog &rhs) {
		if (this == &rhs)
			return *this;

		// safe solution with buffer
		Collar buffer = c;
		c = new Collar(*rhs.c);
		delete buffer;
		return *this;
	}

	The second (runtime better and short) solution:
	Dog& operator=(const Dog &rhs) {
		*c = *rhs.c;
		return *this;
	}

2.7
	Output of the following program is:
	80
	sizeof(*p) is 80 but sizeof(p) is 800

2.8
	The members of a struct are on the stack, the output is:
	5 6 256
	char is 1 byte the array char[4] is 4 byte like integer. Reading from the left to the right
	the value (casted to integer from char array) is 256.

2.9
	The #<variable> prints variable name.
	The output is:
	i is 255
	*j is 255
