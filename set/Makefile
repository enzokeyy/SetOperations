CC = gcc
CFLAGS = -Wall -std=c99
INCLUDES = -I ../AVL -I ../ARVORE_LLRB

SRC = main.c set.c ../ARVORE_LLRB/arvore_llrb.c ../AVL/bst_avl.c
OBJ = main

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(OBJ)

run: $(OBJ)
	./$(OBJ)

clean:
	rm -f $(OBJ)
