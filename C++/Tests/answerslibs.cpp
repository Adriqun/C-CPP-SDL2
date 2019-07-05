// author: Adrian Michałek
// email: devmichalek@gmail.com

0.0 // The proper order for the specified needs is:
    // Compile test.c:
    //    gcc -c test.c
    // Create static library:
    //    ar -cvq libtest.a test.o
    // Compile and create executable:
    //    gcc -o main main.c libtest.a # or
    //    gcc -o main main -L/path/to/current/directory -ltest

0.1 // The proper order for the specified needs is:
    // Compile test.c with -fPIC (Platform Independent Code flag)
    //    gcc -fPIC -c test.c
    // Create dynamic library
    //    gcc -shared test.o -o libtest.so
    // Compile and create executable:
    //    gcc main.c -L/path/to/current/directory -ltest -o main
    // Set $LD_LIBRARY_PATH variable:
    //    LD_LIBRARY_PATH=path/to/current/directory
    //    export LD_LIBRARY_PATH

0.2 // You have to use --whole-archive and --no-whole-archive flag.
    // These flags are linker flags so the use is actually -Wl,<flag>
    // While creating shared library we specify --whole-archive that means take all the objects from static library even these not needed (add2() function is not used in dynamic library but it may be used by dynamic library users). Then turn off this flag by setting --no-whole-archive, this step is crucial to escape infinite loop error.

    // Compile part.c and create static library:
    //    gcc -c part.c
    //    ar -cvq libpart.a part.o
    // Compile test.c and create a shared library:
    //    gcc -fPIC -c test.c
    //    gcc -shared -Wl,--whole-archive libpart.a Wl,--no-whole-archive test.o -o libtest.so
    // Set $LD_LIBRARY_PATH variable:
    //    LD_LIBRARY_PATH=path/to/current/directory
    //    export LD_LIBRARY_PATH
    // Compile and create executable:
    //    gcc main.c libtest.so -o main
