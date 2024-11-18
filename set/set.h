#ifndef SET_H
    #define SET_H

    #include <../ARVORE_LLRB/arvore_llrb.h>
    #include <../AVL/bst_avl.h>
    #include <stdio.h>
    #include <stdlib.h>

    /**
     * @brief Cria e inicializa um novo conjunto.
     *
     * @param opt Identificador do tipo de árvore (0 para AVL, 1 para LLRB).
     * @return SET* Ponteiro para o conjunto criado ou NULL em caso de erro.
     */
    SET *criar_set(int opt);

    /**
     * @brief Libera a memória associada ao conjunto e sua árvore.
     *
     * @param set Endereço do ponteiro para o conjunto a ser apagado.
     */
    void set_apagar(SET **set);

    /**
     * @brief Verifica se um valor pertence ao conjunto.
     *
     * @param set Ponteiro para o conjunto.
     * @param valor Valor inteiro a ser consultado.
     * @return int Retorna 1 se o valor pertence ao conjunto, 0 caso contrário.
     */
    int set_pertence(SET *set, int valor);

    /**
     * @brief Remove um valor do conjunto.
     *
     * @param set Ponteiro para o conjunto.
     * @param valor Valor inteiro a ser removido.
     * @return int Retorna 1 se a remoção foi bem-sucedida, 0 caso contrário.
     */
    int set_remover(SET *set, int valor);

    /**
     * @brief Insere um valor no conjunto.
     *
     * @param set Ponteiro para o conjunto.
     * @param valor Valor inteiro a ser inserido.
     * @return int Retorna 1 se a inserção foi bem-sucedida, 0 caso contrário.
     */
    int set_inserir(SET *set, int valor);

    // Struct para encapsular operações genéricas de árvore
    typedef struct arvore {
    /**
     * @brief Insere um valor na árvore.
     *
     * @param arv Ponteiro genérico para a estrutura da árvore.
     * @param valor Valor inteiro a ser inserido.
     * @return int Retorna 1 se a inserção foi bem-sucedida, 0 caso contrário.
     */
    int (*inserir)(void *arv, int valor);

    /**
     * @brief Remove um valor da árvore.
     *
     * @param arv Ponteiro genérico para a estrutura da árvore.
     * @param valor Valor inteiro a ser removido.
     * @return int Retorna 1 se a remoção foi bem-sucedida, 0 caso contrário.
     */
    int (*remover)(void *arv, int valor);

    /**
     * @brief Verifica se um valor pertence à árvore.
     *
     * @param arv Ponteiro genérico para a estrutura da árvore.
     * @param valor Valor inteiro a ser buscado.
     * @return int Retorna 1 se o valor está presente, 0 caso contrário.
     */
    int (*buscar)(void *arv, int valor);

    /**
     * @brief Cria uma nova estrutura de árvore.
     *
     * @return void* Ponteiro genérico para a estrutura criada.
     */
    void *(*criar)(void);

    /**
     * @brief Libera a memória associada à árvore.
     *
     * @param arv Endereço do ponteiro genérico para a estrutura da árvore.
     */
    void (*apagar)(void **arv);

    /**
     * @brief Imprime os elementos da árvore.
     *
     * @param arv Ponteiro genérico para a estrutura da árvore.
     */
    void (*imprimir)(void *arv);

    /**
     * @brief Ponteiro genérico para armazenar a estrutura da árvore (AVL ou
     * LLRB).
     */
    void *estrutura;

    } Arvore;

    // Struct para representar um conjunto (SET) utilizando árvores
    typedef struct set {
    /**
     * @brief Ponteiro para uma estrutura genérica de árvore.
     */
    Arvore *SET;

    /**
     * @brief Identificador do tipo de árvore (0 para AVL, 1 para LLRB).
     */
    int opt;

    } SET;

#endif