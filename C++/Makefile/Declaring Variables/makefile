# comment
# declare
CC=g++
COUTPUT=-o runme
CFLAGS=-c -Wall

output: main.o msg.o
	$(CC) main.o msg.o $(COUTPUT)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

msg.o: msg.cpp msg.h
	$(CC) $(CFLAGS) msg.cpp

clean:
	rm *.o output