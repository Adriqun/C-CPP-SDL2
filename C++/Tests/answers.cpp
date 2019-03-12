0.1
	ABCBAD
	The parameters of the function are read from the right to the left but members of a class are created from
	the top to the bottom.

0.2
	While creating different constructors it is good to have one function like init(). Standard C++11 provides new kind
	solution for that.

	class C
	{
	public:
		C() { /*init*/ }
		C(int x) : C() {}
	};

	Class B is wrong because while calling second constructor we call another which creates again new object B.
	Calling C second constructor is safe because we use functionality of another constructor without creating another object.
	Calling C second constructor is even better because C() is called before C(int x).

0.3
	To force the compiler to generate default constructor we simply use this line:
	Dog() = default;

0.4
	The implementation:
	filter([](int x) {return (x > 3);}, v);

0.5
	The solution:
	auto f1 = [&a]() { a = 1; printf("%d\n", a); };
	auto f2 = [=]() { printf("%d\n", a + b + c + d); };
	auto f3 = [&, b]() { a = c = d; printf("%d\n", b); };
	& - pass all variables by reference (with variable: &variable)
	= - pass all variables by const copy (with variable: variable)

0.6
	Following constructor is the correct one for move semantics feature:
	MyVector(MyVector &&rhs) {
		size = rhs.size;
		arr = rhs.arr;
		rhs.arr = nullptr; // <- set rhs array as nullptr!
	}
	Without the last line moved MyVector would be destroyed so the array. Ascribed line above:
	arr = rhs.arr, would be pointing to array that does not exist which causes bug while calling getFirst().

0.7
	While creating shared pointer (memory leaks):
	std::shared_ptr<Dog> p3(new Dog[3]);
	only first element of the array is set to p3, the rest is lost. To prevent this we can use lambda function:
	std::shared_ptr<Dog> p3(new Dog[3], [](Dog* pDog) {delete[] pDog; });

1.0
	The program will crash while invoking yd->bark(2).
	Soution:
	struct YellowDog : public Dog {
		using Dog::bark; // <- solution
		virtual void bark(std::string msg = "Yellowdog") { std::cout << "I am " << msg << " dog" << std::endl; }
	};
	The reason is when the compiler sees bark(int) it will first search in the YellowDog class. However if the compiler
	does not find the bark(int) function in the YellowDog regardless of the parameter and the value type it will stop there.
	Two bark() functions are not inherited by YellowDog instead one bark(string) shadows the two bark() function inside Dog class.

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

3.0
	Suppose, you have a class String:

	class String {
	public:
	    String(int n); // allocate n bytes to the String object
	    String(const char *p); // initializes object with char *p
	};
	Now, if you try:

	String mystring = 'x';
	The character 'x' will be implicitly converted to int and then the String(int) constructor will be called.
	But, this is not what the user might have intended. So, to prevent such conditions, we shall define the
	constructor as explicit:

	class String {
	public:
	    explicit String (int n); //allocate n bytes
	    String(const char *p); // initialize sobject with string p
	};

3.1 
	Before the compiler sees the private open() function in InputFile class
	it first check which open() function would be invoked that is why compiler
	will still issue an error -> Ambiguous call...
	To open the file successfully:
	f.OutputFile::open();

3.2
	The output is:
	calling A::g()
	calling B::g()
	First line of output is Koenig Lookup example. If the compiler have not found the g() function it starts
	to search inside variable scope (A scope).
	Second line of output shows the priority class towards namespace. Class and its parents are always first
	taken into consider by compiler.

3.3
	constexpr allows to compute values at compile time only for const objects.
	The difference is that e() evaluation is calculated at runtime. Function f() is evaluated at compile time.

3.4
	Output is:
	10
	100
	volatile is a hint to the implementation to avoid aggressive optimization involving the object because the
	value of the object might be changed by means undetectable by an implementation.
	
	volatile tells the compiler: Hey compiler, I'm volatile and, you know, I can be changed by some XYZ that
	you're not even aware of. That XYZ could be anything. Maybe some alien outside this planet called program.
	Maybe some lighting, some form of interrupt, volcanoes, etc can mutate me. Maybe. You never know who is
	going to change me! So O you ignorant, stop playing an all-knowing god, and don't dare touch the code
	where I'm present.

3.5
	Solution is:
	Animal(float) = delete;
	Animal operator=(const Animal &rhs) = delete;

3.6
	Solution:
	int main()
	{
		auto raport = [lp = 0](const char* msg) mutable
		{
			std::cout << msg << ++lp << " ";
		};

		raport("A ");
		raport("B ");
		return 0;
	}

	Passing values to lambda function not by referece means passing by const copy!
	Keyword mutable allows as to change the value.
	Since it is copy the output is: "A 1 B 1" right?
	Wrong. The output is "A 1 B 2" but why?
	Modification of variable is not visible outside of lambda function, but inside the
	value is remembered. It is because lambda function is not function but object function.

3.7
	Literal operator may look like this:
	int operator"" _strBin2Dec(const char* str, size_t length) {
		int ret = 0;
		for (int i = 0; i < length; ++i) {
			ret = ret << 1;
			if (str[i] == '1')
				ret += 1;
		}
		return ret;
	}

	_strBin2Dec takes string and its size.
