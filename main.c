#include <../set/set.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int tipo, opcao, valor, tam_1, tam_2;

    scanf("%d", &tipo);
    // Criar sets
    SET *conj_1 = (SET*)criar_set(tipo);
    SET *conj_2 = (SET*)criar_set(tipo);

    scanf(" %d %d", &tam_1, &tam_2);
    // Inserir elementos
    for(int i=0; i<tam_1; i++) {
        scanf(" %d", &valor);
        set_inserir(conj_1, valor);
    }
    for(int i=0; i<tam_2; i++) {
        scanf(" %d", &valor);
        set_inserir(conj_2, valor);
    }

    scanf(" %d", &opcao);
    // Menu
    switch(opcao){
        case 1: {
            int elemento, pertence;
            scanf(" %d", &elemento);
            pertence = set_pertence(conj_1, elemento);
            if(pertence == 1)
                printf("Pertence.\n");
            else
                printf("Nao pertence.\n");
            break;
        }
        case 2: {
            set_uniao(conj_1, conj_2);
            break;
        }
        case 3: {
            set_interseccao(conj_1, conj_2);
            break;
        }
        case 4: {
            int elemento;
            scanf(" %d", &elemento);
            set_remover(conj_1, elemento);
            set_imprimir(conj_1);
            break;
        }
  }

  return 0;
}
