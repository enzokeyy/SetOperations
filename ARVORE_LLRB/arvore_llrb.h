#ifndef ARVORE_LLRB_H
#define ARVORE_LLRB_H

    #include <stdio.h>
    #include <stdlib.h>

    typedef NO *ARVLLRB;

    /**
     * @brief Consulta a árvore em busca de uma certa chave.
     *
     * @param raiz  Ponteiro de ponteiro da árvore.
     * @param chave Inteiro do valor procurado.
     * @return Valor inteiro booleano para o encontro do nó com a chave.
     */
    int consulta_arvllrb(ARVLLRB *raiz, int chave);


    /**
     * @brief Limpa toda a árvore.
     *
     * @param root Ponteiro para o nó root.
     * @return Chamada recursiva para free(root).
     */
    void libera_arvllrb(NO *root);

    
    /**
     * @brief Retorna a cor de um nó.
     *
     * @param H Ponteiro para o nó.
     * @return Cor do nó (RED ou BLACK). Retorna BLACK se o nó for NULL.
     */
    int cor_no(NO *H);

    /**
     * @brief Troca as cores do nó atual e de seus dois filhos.
     *
     * @param h Ponteiro para o nó cuja cor será trocada.
     */
    void troca_cor(NO *h);

    /**
     * @brief Realiza uma rotação à esquerda no nó fornecido.
     *
     * @param root Ponteiro para o nó que será rotacionado.
     * @return Novo nó raiz após a rotação à esquerda.
     */
    NO *rotacionar_esquerda(NO *root);

    /**
     * @brief Realiza uma rotação à direita no nó fornecido.
     *
     * @param root Ponteiro para o nó que será rotacionado.
     * @return Novo nó raiz após a rotação à direita.
     */
    NO *rotacionar_direita(NO *root);

    /**
     * @brief Move um nó vermelho do lado direito para o lado esquerdo.
     *
     * @param root Ponteiro para o nó atual.
     * @return Ponteiro para o nó ajustado após o movimento.
     */
    NO *move2_esq_red(NO *root);

    /**
     * @brief Move um nó vermelho do lado esquerdo para o lado direito.
     *
     * @param root Ponteiro para o nó atual.
     * @return Ponteiro para o nó ajustado após o movimento.
     */
    NO *move2_dir_red(NO *root);

    /**
     * @brief Realiza o balanceamento da árvore Rubro-Negra a partir de um nó.
     *
     * @param root Ponteiro para o nó que será balanceado.
     * @return Ponteiro para o nó ajustado após o balanceamento.
     */
    NO *balancear(NO *root);

    /**
     * @brief Insere uma chave na árvore Rubro-Negra.
     *
     * @param raiz Ponteiro para o ponteiro da raiz da árvore.
     * @param chave Chave a ser inserida.
     * @return 1 se a inserção for bem-sucedida, 0 caso contrário.
     */
    int insere_arvllrb(ARVLLRB *raiz, int chave);

    /**
     * @brief Insere um nó em uma subárvore Rubro-Negra.
     *
     * @param root Ponteiro para a raiz da subárvore.
     * @param chave Chave a ser inserida.
     * @param resp Ponteiro para o código de resposta da operação.
     * @return Ponteiro para o nó raiz ajustado após a inserção.
     */
    NO *insere_no(NO *root, int chave, int *resp);

    /**
     * @brief Remove uma chave da árvore Rubro-Negra.
     *
     * @param root Ponteiro para o ponteiro da raiz da árvore.
     * @param chave Chave a ser removida.
     * @return 1 se a remoção for bem-sucedida, 0 caso contrário.
     */
    int remove_arvllrb(ARVLLRB *root, int chave);

    /**
     * @brief Remove um nó com uma determinada chave em uma subárvore Rubro-Negra.
     *
     * @param root Ponteiro para a raiz da subárvore.
     * @param chave Chave a ser removida.
     * @return Ponteiro para o nó raiz ajustado após a remoção.
     */
    NO *remove_no(NO *root, int chave);

    /**
     * @brief Remove o menor nó de uma subárvore Rubro-Negra.
     *
     * @param root Ponteiro para a raiz da subárvore.
     * @return Ponteiro para o nó raiz ajustado após a remoção do menor nó.
     */
    NO *removerMenor(NO *root);

    /**
     * @brief Busca o menor nó em uma subárvore Rubro-Negra.
     *
     * @param root Ponteiro para a raiz da subárvore.
     * @return Ponteiro para o menor nó encontrado.
     */
    NO *procuraMenor(NO *root);

#endif
