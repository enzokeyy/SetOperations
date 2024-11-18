#ifndef ARVORE_LLRB_H
    #define ARVORE_LLRB_H

    #include <stdio.h>
    #include <stdlib.h>

    typedef struct no NO;
    typedef NO *ARVLLRB;

    /**
     * @brief Verifica a existência de uma chave na árvore rubro-negra.
     *
     * Realiza uma busca na árvore rubro-negra para verificar se uma chave
     * específica está presente.
     *
     * @param raiz Ponteiro para a raiz da árvore rubro-negra.
     * @param chave Valor inteiro da chave a ser consultada.
     * @return int Retorna 1 se a chave estiver presente, ou 0 caso contrário.
     *
     * @note A consulta não altera a estrutura da árvore.
     */
    int arvllrb_consultar(ARVLLRB *raiz, int chave);

    /**
     * @brief Insere uma nova chave na árvore rubro-negra.
     *
     * @param raiz Ponteiro para a raiz da árvore rubro-negra.
     * @param chave Valor inteiro a ser inserido na árvore.
     * @return int Retorna 1 se a inserção foi bem-sucedida, ou 0 em caso de falha.
     */
    int arvllrb_inserir(ARVLLRB *raiz, int chave);

    /**
     * @brief Remove uma chave da árvore rubro-negra, se existir.
     *
     * @param raiz Ponteiro para a raiz da árvore rubro-negra.
     * @param chave Valor inteiro a ser removido da árvore.
     * @return int Retorna 1 se a remoção foi bem-sucedida, ou 0 se a chave não foi
     * encontrada.
     */
    int arvllrb_remover(ARVLLRB *raiz, int chave);

    /**
     * @brief Imprime todos os elementos da árvore rubro-negra em ordem (ou em outro
     * formato específico).
     *
     * @param raiz Ponteiro para a raiz da árvore rubro-negra.
     *
     * @note A impressão pode ser adaptada para diferentes representações, como
     * em-ordem, pré-ordem ou pós-ordem.
     */
    void arvllrb_imprimir(ARVLLRB *raiz);

    /**
     * @brief Apaga a árvore rubro-negra, liberando toda a memória alocada.
     *
     * @param raiz Endereço do ponteiro para a raiz da árvore rubro-negra.
     * Após a execução, o ponteiro será definido como NULL.
     */
    void arvllrb_apagar(ARVLLRB **raiz);

    /**
     * @brief Cria uma nova árvore rubro-negra vazia.
     *
     * @return ARVLLRB* Retorna um ponteiro para a nova árvore rubro-negra, ou NULL
     * em caso de erro na alocação.
     */
    ARVLLRB *arvllrb_criar(void);

#endif
