#ifndef SET_H
#define SET_H

#include "../ARVORE_LLRB/arvore_llrb.h"
#include "../AVL/bst_avl.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct set SET;

/**
 * @brief Cria um novo conjunto com base no tipo de árvore escolhido.
 *
 * @param opt Identificador do tipo de árvore: 1 para AVL, 2 para Red-Black.
 * @return Ponteiro para o conjunto criado ou NULL em caso de erro.
 */
SET *criar_set(int opt);

/**
 * @brief Libera a memória associada a um conjunto.
 *
 * @param set Ponteiro duplo para o conjunto a ser apagado.
 */
void set_apagar(SET **set);

/**
 * @brief Verifica se um elemento pertence ao conjunto.
 *
 * @param set Ponteiro para o conjunto.
 * @param valor Elemento a ser verificado.
 * @return 1 se o elemento pertence ao conjunto, 0 caso contrário.
 */
int set_pertence(SET *set, int valor);

/**
 * @brief Remove um elemento do conjunto.
 *
 * @param set Ponteiro para o conjunto.
 * @param valor Elemento a ser removido.
 * @return 1 se a remoção for bem-sucedida, 0 caso o elemento não exista.
 */
int set_remover(SET *set, int valor);

/**
 * @brief Insere um elemento no conjunto.
 *
 * @param set Ponteiro para o conjunto.
 * @param valor Elemento a ser inserido.
 * @return 1 se a inserção for bem-sucedida, 0 caso o elemento já exista.
 */
int set_inserir(SET *set, int valor);

/**
 * @brief Imprime a união de dois conjuntos.
 *
 * A função percorre ambos os conjuntos e imprime os elementos de cada um,
 * sem duplicar valores já impressos.
 *
 * @param set1 Ponteiro para o primeiro conjunto.
 * @param set2 Ponteiro para o segundo conjunto.
 */

/**
 * @brief Imprime todos os elementos de um conjunto.
 *
 * @param set Ponteiro para o conjunto.
 */
void set_imprimir(SET *set);

/**
 * @brief Imprime a união de dois conjuntos.
 *
 * A função percorre ambos os conjuntos e imprime os elementos únicos.
 *
 * @param set1 Ponteiro para o primeiro conjunto.
 * @param set2 Ponteiro para o segundo conjunto.
 */
void set_uniao(SET *set1, SET *set2);

/**
 * @brief Imprime a intersecção de dois conjuntos.
 *
 * A função percorre ambos os conjuntos e imprime os elementos que forem
 * presentes em ambos conjuntos.
 *
 * @param set1 Ponteiro para o primeiro conjunto.
 * @param set2 Ponteiro para o segundo conjunto.
 */
void set_interseccao(SET *set1, SET *set2);

#endif // SET_H
