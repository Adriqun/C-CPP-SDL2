gcc -c -fPIC sh.cpp
gcc -shared sh.o -Wl,--version-script,script -o libsh.so
gcc -c main.cpp
gcc main.o -Wl,-R. -Wl,-L. -Wl,-lsh -o main
