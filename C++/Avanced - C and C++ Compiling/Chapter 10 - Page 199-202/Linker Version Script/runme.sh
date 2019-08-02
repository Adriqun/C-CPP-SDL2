gcc -Wall -g -O0 -fPIC -c sh.c
gcc -g -shared sh.o -o libsh.so -Wl,--version-script,script
readelf -S libsh.so
readelf -V libsh.so
readelf --symbols libsh.so | grep function

# now compile, create main
gcc -g -O0 -c main.c
gcc main.o -Wl,-R. -Wl,-L. -Wl,-lsh -o main

# run main
./main

# now if version of libsh.so has changed (script2), main would not work
gcc -g -shared sh.o -o libsh.so -Wl,--version-script,script2

# run main, expected error msg
./main # ./main: ./libsh.so: version `LIBSH_1.0' not found (required by ./main)
