#ifndef ARVORE_LLRB_H
#define ARVORE_LLRB_H

typedef struct NO* ARVLLRB;

// Funções auxiliares
int cor_no(struct NO* H);
void troca_cor(struct NO* h);

// Funções de rotação
struct NO* rotacionar_esquerda(struct NO* root);
struct NO* rotacionar_direita(struct NO* root);

// Funções de movimento para nós vermelhos
struct NO* move2_esq_red(struct NO* root);
struct NO* move2_dir_red(struct NO* root);

// Função de balanceamento
struct NO* balancear(struct NO* root);

// Funções de inserção e remoção
int insere_arvllrb(ARVLLRB* raiz, int chave);
struct NO* insereNO(struct NO* root, int chave, int* resp);
int remove_arvllrb(ARVLLRB* root, int chave);
struct NO* remove_no(struct NO* root, int chave);
struct NO* removerMenor(struct NO* root);

// Função auxiliar para busca do menor elemento
struct NO* procuraMenor(struct NO* root);

#endif
