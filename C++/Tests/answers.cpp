0.0
	By static void f2() we tell the compiler that function f2() will be used only in main.cpp. Since function f2() is never called the linker would not look for the object.
	Function void f1() is not declared as a static so the linker assumes that this function may be used outside main.cpp which means it searches for a body of void print(int &&number);

0.1
	ABCBAD
	The parameters of the function are read from the right to the left but members of a class are created from the top to the bottom.

0.2
	While creating different constructors it is good to have one function like init(). Standard C++11 provides new kind solution for that.

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

0.8
	Output is 7.

0.9
	print_u() function should look like this:
	void print_u(int &i, int j)
	{
		std::lock_guard<std::mutex> locker(mu);
		printf("%d\n", unsigned_max(i, j));
	}

1.0
	The program will crash while invoking yd->bark(2). Solution is:
	struct YellowDog : public Dog {
		using Dog::bark; // <- solution
		virtual void bark(std::string msg = "Yellowdog") { std::cout << "I am " << msg << " dog" << std::endl; }
	};
	The reason is when the compiler sees bark(int) it will first search in the YellowDog class. However if the compiler does not find the bark(int) function in the YellowDog regardless of the parameter and the value type it will stop there.
	Two bark() functions are not inherited by YellowDog instead one bark(string) shadows the two bark() function inside Dog class.

1.1
	It depends... Based on compiler you have answer may look like:
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
	Most modern compilers do not allow to change value of the const object via pointers.

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
	We use const_cast to cast away constness of these objects, but these objects points to not const object which can be modified.



1.4
	The code wouldn't compile because of:
	void printDogName() const { cout << getName() << " const" << endl; }

	The function above is const which means variables cannot be modified and it can only invoke const functions.

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
	The expression (p += sizeof(int))[-1] can be written as (p += 4)[-1] which can be written as (p = p+4)[-] which returns address p+3 which is address of fourth element in argv[].

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

1.9
	Counter stores number 6

2.1
	First solution (c++11):
	Human(Human &h) = delete;
	Second solution (c++03), declare the function to be private, and not define it:
	private:
		Human(Human &h);

2.2
	Private destructors can only be stored on heap, knowing that the only possible way of using class Human is via pointers. By adding public function:
	void destroyMe() { delete this; }
	and in the main function:
	of->destroyMe();
	We freed the memory correctly.

2.3
	As long as you define constructor that takes parameters (class Dog), the compiler will failed in case of invoking default constructor. The output of the following code is compiler error "no default constructor" or sth like this.

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
	char is 1 byte the array char[4] is 4 byte like integer. Reading from the left to the right the value (casted to integer from char array) is 256.

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
	The character 'x' will be implicitly converted to int and then the String(int) constructor will be called but, this is not what the user might have intended. So, to prevent such conditions, we shall define the constructor as explicit:

	class String {
	public:
	    explicit String (int n); //allocate n bytes
	    String(const char *p); // initialize sobject with string p
	};

3.1 
	Before the compiler sees the private open() function in InputFile class it first check which open() function would be invoked that is why compiler will still issue an error -> Ambiguous call... To open the file successfully:
	f.OutputFile::open();

3.2
	The output is:
	calling A::g()
	calling B::g()
	First line of output is Koenig Lookup example. If the compiler have not found the g() function it starts to search inside variable scope (A scope).
	Second line of output shows the priority class towards namespace. Class and its parents are always first taken into consider by compiler.

3.3
	constexpr allows to compute values at compile time only for const objects.
	The difference is that e() evaluation is calculated at runtime. Function f() is evaluated at compile time.

3.4
	Output is:
	10
	100
	volatile is a hint to the implementation to avoid aggressive optimization involving the object because the value of the object might be changed by means undetectable by an implementation.
	
	volatile tells the compiler: Hey compiler, I  am volatile and, you know, I can be changed by some XYZ that you are not even aware of. That XYZ could be anything. Maybe some alien outside this planet called program. Maybe some lighting, some form of interrupt, volcanoes, etc can mutate me. Maybe. You never know who is going to change me! So O you ignorant, stop playing an all-knowing god, and don not dare touch the code where I am present.

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

	Passing values to lambda function not by referece means passing by const copy! Keyword mutable allows as to change the value. Since it is copy the output is: "A 1 B 1" right? Wrong. The output is "A 1 B 2" but why?
	Modification of variable is not visible outside of lambda function, but inside the value is remembered. It is because lambda function is not function but object function.

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

3.8
	Output is:
	1.
	Dog A is created.
	Dog A is destroyed.
	2.
	Dog B is created.
	3.
	Dog B is destroyed.
	It turns out that standard smart pointers have build in move semantics so automatically returning the std::unique_ptr actually returns std::move(std::unique_ptr<>()) which is very important.

3.9
	Obviously:
	Int Constructor
	0
	-255
	Int Desctructor
	right?
	Nope, not at all, most compilers would not compile this code. Because thread takes parameters by copy, compiler will copy i.data value even for function that takes reference, first value will be copied then passed. Solution for that is to pass i.data like:
	std::thread t(_, std::ref(i));

4.0
	Output is:
	B

	Passing value with move semantics into the operator() function will simply not copy the value but move it. Since it is an oryginal the std::string destructor is called at the end of this function. Then std::string value is empty.

4.1
	print_I(): Say I have two thread running thread A and B, lets say thread A first checked if m_ofstream is open and it were not then it locks m_mutex and opens the file "file.log" but before it opens the file thread B checks if file is open and it turns out it is not, then thread B tries to lock m_mutex but it must wait because thread A was first. Thread A opens the file and leave the block, now thread B locks m_mutex and opens file again... So both thread opened file. File was opened twice.
	
	print_II(): This solution is thread safe but the file needs to be opened once. In this solution every time if someone call print_II() the another thread will be blocked which means another threads need to wait until the current leave the block. It is a waste of computer cycles.

	The standard library provides a solution for this kind of problem.
	Instead of using another mutex:
	class LogFile {
		std::mutex m_mutex;
		std::once_flag m_flag; // <- once flag
		std::ofstream m_ofstream;
		// ...
	public:
		// ...
		void print_III(/* some arguments */)
		{	// file will be open only once and only by one std::thread
			std::call_once(m_flag, [&](){ m_ofstream.open("file.log"); });
			// ... now std::mutex if needed
		}
	}

4.2
	The solution is std::recursive_mutex which allows to use nested recursive function for threads.
	std::recursive_mutex mutex;
	void nested(int &i, bool b)
	{
		std::lock_guard<std::recursive_mutex> locker(mutex);
		if (i > 10)
			return;
		++i;
		nested(i, true);
	}

4.3
	On 32 bit computer you get a structure that is 48 bits, 32 for int, 16 for the short.
	On the 64 bit computer you get structure that is 80 bits long, 64 for in, 16 for short.
	The problem comes about when you tried to use this struct to read what was written by the other.
	Better implementation:
	struct A {
		long a; // 4 bytes
		short b; // 2 bytes
	}

	If you are sending stuff across the wire you must use the char, short, long, etc. If you are not then you can use int, as int and let the compiler figure it out.

4.4 double (*ptr)[7][4]

4.5
	The reason for this is that early versions of C did not have function prototypes; parameter types were declared at the function site but were not known at the call site. But different types are represented differently, and the representation of the passed argument must match the called functions expectation. So that char and short values could be passed to functions with int parameters, or float values could be passed to functions with double parameters, the compiler promoted the smaller types to be of the larger type. This behavior is still seen when the type of the parameter is not known at the call site -- namely, for variadic functions or functions declared without a prototype.

4.6
	a = ??? (undefined), b = 5

4.7
	a = 1, b = 4

4.8
	The answer is 120.
	At first look, the expression (a*b)/c seems to cause arithmetic overflow because signed characters can have values only from -128 to 127 (in most of the C compilers), and the value of subexpression ‘(a*b)’ is 1200 which is greater than 128. But integer promotion happens here in arithmetic done on char types and we get the appropriate result without any overflow.
	Integer Promotions:
	Some data types like char , short int take less number of bytes than int, these data types are automatically promoted to int or unsigned int when an operation is performed on them. This is called integer promotion. For example no arithmetic calculation happens on smaller types like char, short and enum. They are first converted to int or unsigned int, and then arithmetic is done on them. If an int can represent all values of the original type, the value is converted to an int . Otherwise, it is converted to an unsigned int.

4.9
	extern "C" makes a function-name in C++ have 'C' linkage (compiler does not mangle the name) so that client C code can link to (i.e use) your function using a 'C' compatible header file that contains just the declaration of your function. Your function definition is contained in a binary format (that was compiled by your C++ compiler) that the client 'C' linker will then link to using the 'C' name.
	Since C++ has overloading of function names and C does not, the C++ compiler cannot just use the function name as a unique id to link to, so it mangles the name by adding information about the arguments. A C compiler does not need to mangle the name since you can not overload function names in C. When you state that a function has extern "C" linkage in C++, the C++ compiler does not add argument/parameter type information to the name used for linkage.

	int example() - function name will be evaluated into sth like: _Z1examplev
	extern "C" int example - function name will be evaluated into: example