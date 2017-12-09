CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

all:
	$(CC) $(CFLAGS) -o dp dp.c 
	$(CC) $(CFLAGS) -o problem1 problem1.c
	$(CC) $(CFLAGS) -o problem2 problem2.c
	$(CC) $(CFLAGS) -o problem3-1 problem3-1.c
	$(CC) $(CFLAGS) -o problem3-2 problem3-2.c

.PHONY: clean
clean:
	/bin/rm -rf  problem2 problem2.dSYM problem3-1 problem3-1.dSYM problem3-2 problem3-2.dSYM problem1 problem1.dSYM dp dp.dSYM
