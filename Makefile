all: main

main: main.c ./set/set.c ./ARVORE_LLRB/arvore_llrb.c
	gcc main.c ./set/set.c ./ARVORE_LLRB/arvore_llrb.c ./AVL/bst_avl.c -o main -Wall -std=c99 -I ./set -I ./AVL ./ARVORE_LLRB

run: main
	./main

clean:
	rm -f main
