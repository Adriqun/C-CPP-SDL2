#	all: library.cpp main.cpp
#	$@ evaluates to all
#	$< evaluates to library.cpp
#	$^ evaluates to library.cpp main.cpp


CC=g++
CFLAGS=-c -Wall

output: main.o msg.o
	$(CC) $^ -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) $<

msg.o: msg.cpp msg.h
	$(CC) $(CFLAGS) $<

clean:
	rm *.o output