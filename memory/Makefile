
CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin

vpath %.h ./include
vpath %.c ./src

EXECS = $(BIN)/dlisttest $(BIN)/memory-test

all: mkpaths $(EXECS)

mkpaths:
	mkdir -p $(OBJ)

doc:
	doxygen

$(OBJ)/dnode.o: $(INC)/dnode.h $(SRC)/dnode.c
	$(CC) $(CFLAGS) -c $(SRC)/dnode.c -o $(OBJ)/dnode.o

$(OBJ)/dlist.o: $(INC)/dlist.h $(SRC)/dlist.c $(INC)/dnode.h
	$(CC) $(CFLAGS) -c $(SRC)/dlist.c -o $(OBJ)/dlist.o

$(BIN)/dlisttest: $(SRC)/dlisttest.c $(OBJ)/dnode.o $(OBJ)/dlist.o
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(SRC)/dlisttest.c -o $(BIN)/dlisttest

$(OBJ)/allocator.o: $(SRC)/allocator.c $(INC)/allocator.h
	$(CC) $(CFLAGS) -c $(SRC)/allocator.c -o $(OBJ)/allocator.o

$(BIN)/memory-test: $(OBJ)/allocator.o $(SRC)/memory-test.c
	$(CC) $(CFLAGS) $(SRC)/memory-test.c $(OBJ)/allocator.o $(OBJ)/dnode.o $(OBJ)/dlist.o -o $(BIN)/memory-test

.PHONY: clean
clean:
	/bin/rm -rf $(BIN)/* $(OBJ)/* core* *~

