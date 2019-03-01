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