CC = gcc

CFLAGS = -Wall -g -std=c99
RM = rm -rf *.o libgrades.so

libgrades.so: grades.o
			$(CC) -shared grades.o -o libgrades.so -llinked-list -L.

grades.o: grades.c grades.h linked-list.h
		$(CC) $(CFLAGS) -c -fpic grades.c

clean:
		$(RM)