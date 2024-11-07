#ifndef BST_AVL_H
#define BST_AVL_H

#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó
typedef struct no {
    struct no* esq;
    struct no* dir;
    int chave;
    int height;
} NO;

// Funções auxiliares

/**
 * @brief Retorna a altura de um nó.
 *
 * @param root Ponteiro para o nó.
 * @return Altura do nó. Retorna 0 se o nó for NULL.
 */
int altura_no(NO* root);

/**
 * @brief Retorna o valor máximo entre dois inteiros.
 *
 * @param a Primeiro inteiro.
 * @param b Segundo inteiro.
 * @return O maior valor entre a e b.
 */
int max(int a, int b);

/**
 * @brief Cria um novo nó com a chave especificada.
 *
 * @param chave Valor da chave do novo nó.
 * @return Ponteiro para o novo nó criado. NULL se falhar na alocação.
 */
NO* criar_no(int chave);

// Funções de Rotação

/**
 * @brief Realiza a rotação à direita em um nó.
 *
 * @param root Ponteiro para o nó raiz onde a rotação será realizada.
 * @return Ponteiro para a nova raiz após a rotação.
 */
NO* rotacionar_direita(NO* root);

/**
 * @brief Realiza a rotação à esquerda em um nó.
 *
 * @param root Ponteiro para o nó raiz onde a rotação será realizada.
 * @return Ponteiro para a nova raiz após a rotação.
 */
NO* rotacionar_esquerda(NO* root);

/**
 * @brief Realiza uma rotação dupla à direita (rotação direita-esquerda).
 *
 * @param root Ponteiro para o nó raiz onde a rotação será realizada.
 * @return Ponteiro para a nova raiz após a rotação dupla.
 */
NO* rotacionar_direita_esquerda(NO* root);

/**
 * @brief Realiza uma rotação dupla à esquerda (rotação esquerda-direita).
 *
 * @param root Ponteiro para o nó raiz onde a rotação será realizada.
 * @return Ponteiro para a nova raiz após a rotação dupla.
 */
NO* rotacionar_esquerda_direita(NO* root);

// Funções de Balanceamento

/**
 * @brief Calcula o fator de balanceamento de um nó.
 *
 * @param root Ponteiro para o nó.
 * @return Fator de balanceamento (altura da subárvore esquerda - altura da subárvore direita).
 */
int fb_no(NO* root);

/**
 * @brief Balanceia a árvore AVL a partir de um nó específico.
 *
 * @param root Ponteiro para o nó que pode estar desbalanceado.
 * @return Ponteiro para o nó balanceado.
 */
NO* balancear(NO* root);

// Funções de Inserção e Remoção

/**
 * @brief Insere uma chave na árvore AVL.
 *
 * @param root Ponteiro para a raiz da árvore.
 * @param chave Valor da chave a ser inserida.
 * @return Ponteiro para a nova raiz após a inserção.
 */
NO* inserir_no(NO* root, int chave);

/**
 * @brief Encontra o nó com o valor mínimo na árvore AVL.
 *
 * @param root Ponteiro para a raiz da árvore.
 * @return Ponteiro para o nó com a chave mínima.
 */
NO* valor_minimo_no(NO* root);

/**
 * @brief Remove uma chave da árvore AVL.
 *
 * @param root Ponteiro para a raiz da árvore.
 * @param chave Valor da chave a ser removida.
 * @return Ponteiro para a nova raiz após a remoção.
 */
NO* remover_no(NO* root, int chave);

#endif // BST_AVL_H
