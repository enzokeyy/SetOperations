#ifndef BST_AVL_H
#define BST_AVL_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore AVL.
typedef struct no NO;

// Define AVL como um ponteiro para a estrutura do nó.
typedef NO *AVL;

/**
 * @brief Imprime os elementos da árvore AVL em ordem crescente.
 *
 * Esta função percorre a árvore AVL em ordem (esquerda, raiz, direita) e
 * imprime os elementos na saída padrão.
 *
 * @param T Ponteiro para a árvore AVL.
 */
void avl_imprimir(AVL *T);

/**
 * @brief Busca um nó na árvore AVL com a chave especificada.
 *
 * Realiza uma busca binária na árvore AVL para localizar um nó com a chave
 * especificada. Caso o nó seja encontrado, retorna um ponteiro para ele.
 *
 * @param T Ponteiro para a árvore AVL.
 * @param chave Valor da chave a ser buscada.
 * @return Ponteiro para a chave encontrada.
 */
int avl_buscar(AVL *T, int chave);

/**
 * @brief Insere um novo nó com a chave especificada na árvore AVL.
 *
 * Adiciona um novo elemento à árvore AVL, garantindo que a propriedade
 * de balanceamento seja mantida após a inserção.
 *
 * @param T Ponteiro para a árvore AVL.
 * @param chave Valor da chave a ser inserida.
 * @return 1 se a inserção foi bem-sucedida, 0 se a chave já existir,
 *         ou -1 em caso de erro (ex.: ponteiro nulo).
 */
int avl_inserir(AVL *T, int chave);

/**
 * @brief Remove o nó com a chave especificada da árvore AVL.
 *
 * Remove um elemento da árvore AVL, ajustando o balanceamento para manter
 * as propriedades da árvore AVL após a remoção.
 *
 * @param T Ponteiro para a árvore AVL.
 * @param chave Valor da chave a ser removida.
 * @return 1 se a remoção foi bem-sucedida, 0 se a chave não foi encontrada,
 *         ou -1 em caso de erro (ex.: ponteiro nulo).
 */
int avl_remover(AVL *T, int chave);

/**
 * @brief Cria e inicializa uma nova árvore AVL vazia.
 *
 * Aloca memória para a estrutura da árvore AVL e inicializa seus valores
 * como uma árvore vazia.
 *
 * @return Ponteiro para a árvore AVL recém-criada ou NULL em caso de erro.
 */
AVL *criar_avl(void);

/**
 * @brief Libera a memória de uma árvore AVL.
 *
 * Remove todos os nós da árvore AVL e libera a memória associada. Após essa
 * função, o ponteiro para a árvore será configurado como NULL.
 *
 * @param T Ponteiro para o ponteiro da árvore AVL a ser apagada.
 */
void avl_apagar(AVL **T);

/**
 * @brief Obtém o filho esquerdo de um nó na árvore AVL.
 *
 * Esta função retorna o ponteiro para o nó filho à esquerda do nó especificado,
 * ou NULL caso o nó não tenha um filho esquerdo.
 *
 * @param no Ponteiro para o nó da árvore AVL.
 * @return NO* Ponteiro para o filho esquerdo ou NULL se não existir.
 */
NO *obter_esquerda_avl(NO *no);

/**
 * @brief Obtém o filho direito de um nó na árvore AVL.
 *
 * Esta função retorna o ponteiro para o nó filho à direita do nó especificado,
 * ou NULL caso o nó não tenha um filho direito.
 *
 * @param no Ponteiro para o nó da árvore AVL.
 * @return NO* Ponteiro para o filho direito ou NULL se não existir.
 */
NO *obter_direita_avl(NO *no);

/**
 * @brief Obtém o valor armazenado em um nó da árvore AVL.
 *
 * Esta função retorna o valor inteiro armazenado no nó especificado. Caso o
 * nó seja NULL, retorna 0 como valor padrão.
 *
 * @param no Ponteiro para o nó da árvore AVL.
 * @return int Valor armazenado no nó, ou 0 se o nó for NULL.
 */
int obter_valor_avl(NO *no);

#endif // BST_AVL_H
