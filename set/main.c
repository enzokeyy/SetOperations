#include <stdio.h>
#include <stdlib.h>
#include "set.h"

int main() {
    SET *conj1 = (SET*)criar_set(0); // Conjunto AVL
    SET *conj2 = (SET*)criar_set(0); // Conjunto AVL

    set_inserir(conj1, 10);
    set_inserir(conj1, 20);
    set_inserir(conj2, 30);
    set_inserir(conj2, 40);

    set_imprimir(conj1);
    set_imprimir(conj2);

    set_uniao(conj1, conj2);
    
    // Limpa a memória
    set_apagar(&conj1);
    set_apagar(&conj2);

    return 0;
}
