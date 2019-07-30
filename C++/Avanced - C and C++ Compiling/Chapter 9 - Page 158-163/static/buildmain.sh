gcc -Wall -O0 -Ilibfirst -Ilibsecond -c main.c
gcc main.o -lfirst -lsecond -o app
