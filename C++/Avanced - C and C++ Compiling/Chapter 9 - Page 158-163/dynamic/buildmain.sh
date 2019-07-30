gcc -Wall -O0 -Ilibfirst -Ilibsecond -c main.c
gcc main.o -Wl,-L. -Wl,-lfirst -Wl,-lsecond -Wl,-R. -o app
