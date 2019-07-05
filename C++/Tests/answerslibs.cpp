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
