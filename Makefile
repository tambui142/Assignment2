CC=gcc
LD=gcc
CFLAGS=-ggdb -std=c99 -Wall
LIBS= -lm

testArraysStrings: testArraysStrings.o arraysStrings.o vectors.o
	$(LD) -o testArraysStrings testArraysStrings.o arraysStrings.o vectors.o $(LIBS)
	
arraysStrings.o: arraysStrings.h arraysStrings.c
	$(CC) $(CFLAGS) -c arraysStrings.c

testArraysStrings.o: testArraysStrings.c
	$(CC) $(CFLAGS) -c testArraysStrings.c
	
vectors.o: vectors.c vectors.h
	$(CC) $(CFLAGS) -c vectors.c

clean:
	rm *.o
	rm testArraysStrings
