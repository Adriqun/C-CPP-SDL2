gcc -Wall -g -O0 -fPIC -c first.c
gcc -shared first.o -Wl,-soname,libfirst.so.1 -o libfirst.so.1.0.0
ldconfig -n .
ln -s libfirst.so.1 libfirst.so
