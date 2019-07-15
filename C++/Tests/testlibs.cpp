// author: Adrian Michałek
// email: devmichalek@gmail.com

0.0 // Assume you have test.c with function func() and main.c which uses function func() from the static library libtest.a. Give the proper order of compilation, creation of executable binary and static library on linux. Write commands for the required needs.

0.1 // Do the same thing as in the previous task but now for the dynamic library.

0.2 // Assume you have the following files:
// part.c:
int add2(int a, int b) {
  return a + b;
}

int add3(int a, int b, int c) {
  return a + b + c;
}

//  test.c
int func(int x) {
  int add2(int, int);
  return x + add2(1, 2);
}

// main.c
#include <stdio.h>

int main()
{
  int func(int);
  int add3(int, int, int);
  int ret = func(3) + add3(1, 2, 3);
  printf("ret=%d\n", ret);
  return ret;
}
//  How would you create an exectutable main which uses dynamic library libtest.so which includes static library libpart.a? Note that shared library does not know that function add2() will be used by the library users.

0.3 // [Controlling Dynamic Library Symbols’ Visibility] From the high-level perspective, the mechanism of exporting/hiding the linker symbols is solved almost identically in both Windows and Linux. What is the substantial difference between them?

0.4 // [The Symbol Control Export at Build Time] The GCC compiler provides several mechanisms of setting up the visibility of linker symbols. Assume you have an internal and external function, both of them are external because that's how linux solves the linker symbols for dynamic library. How would you hide internal function of dynamic library?

0.5 // Could you specify some Linux/Windows functions for Dynamically Loading DLL?
    // For example, function to load dynamic library from code or finding symbols in DLL directly from code.

0.6 // How to distinguish the import library file (.lib) from static library (also .lib) quickly and quite accurate without looking at its contents?

0.7 // On the Linux we have the priority scheme for where the system search for Dynamic Libraries while running executable. How the priority scheme look like? Write entities from the highest priority to the lowest priority.

0.8 // On the Windows we have the priority scheme for where the system search for Dynamic Libraries while running exec. What tare Windows Runtime Dynamic Library location rules? Write these entities.

0.9 // How would you fix this problem:
    adrian@adrian:~/Documents/Test$ gcc main.o -ldl -lsh -o main
    /usr/bin/ld: cannot find -lsh
    collect2: error: ld returned 1 exit status
    // Tip: dynamic library libsh.so is in the same directory where commands are executed.

1.0 // [Linux] What is ELF and what distibution do we use to read them?
