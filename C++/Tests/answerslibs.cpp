// author: Adrian Michałek
// email: devmichalek@gmail.com

0.0 // The proper order for the specified needs is:
    // Compile test.c - gcc -c test.c
    // Create static library - ar -cvq libtest.a test.o
    // Compile and create executable - gcc -o main main.c libtest.a
