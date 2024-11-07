#include <stdio.h>
#include <stdlib.h>

#include "bst_avl.h"

typedef struct no {
    struct no* esq;
    struct no* dir;
    int chave;
    int height;
} NO;

// Função para obter a altura de um nó
int altura_no(NO* root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

// Função para calcular o máximo entre dois números
int max(int a, int b) {
    return a > b ? a : b;
}

// Função para criar um novo nó
NO* criar_no(int chave) {
    NO* newNo = (NO*) malloc(sizeof(NO));
    if (newNo == NULL) {
        return NULL;
    }
    newNo->esq = newNo->dir = NULL;
    newNo->height = 1;
    newNo->chave = chave;
    return newNo;
}

// Rotação à direita
NO* rotacionar_direita(NO* root) {
    NO* novoRoot = root->esq;
    NO* filho_filho = novoRoot->dir;

    novoRoot->dir = root;
    root->esq = filho_filho;

    root->height = max(altura_no(root->esq), altura_no(root->dir)) + 1;
    novoRoot->height = max(altura_no(novoRoot->esq), altura_no(novoRoot->dir)) + 1;

    return novoRoot;
}

// Rotação à esquerda
NO* rotacionar_esquerda(NO* root) {
    NO* novoRoot = root->dir;
    NO* filho_filho = novoRoot->esq;

    novoRoot->esq = root;
    root->dir = filho_filho;

    root->height = max(altura_no(root->esq), altura_no(root->dir)) + 1;
    novoRoot->height = max(altura_no(novoRoot->esq), altura_no(novoRoot->dir)) + 1;

    return novoRoot;
}

// Rotação dupla à direita
NO* rotacionar_direita_esquerda(NO* root) {
    root->dir = rotacionar_direita(root->dir);
    return rotacionar_esquerda(root);
}

// Rotação dupla à esquerda
NO* rotacionar_esquerda_direita(NO* root) {
    root->esq = rotacionar_esquerda(root->esq);
    return rotacionar_direita(root);
}

// Função para calcular o fator de balanceamento de um nó
int fb_no(NO* root) {
    if (root == NULL) {
        return 0;
    }
    return altura_no(root->esq) - altura_no(root->dir);
}

// Função para balancear a árvore AVL
NO* balancear(NO* root) {
    int fb = fb_no(root);

    if (fb > 1 && fb_no(root->esq) >= 0)
        return rotacionar_direita(root);

    if (fb < -1 && fb_no(root->dir) <= 0)
        return rotacionar_esquerda(root);

    if (fb > 1 && fb_no(root->esq) < 0)
        return rotacionar_esquerda_direita(root);

    if (fb < -1 && fb_no(root->dir) > 0)
        return rotacionar_direita_esquerda(root);

    return root;
}

// Função para inserir um nó na árvore AVL
NO* inserir_no(NO* root, int chave) {
    if (root == NULL) {
        return criar_no(chave);
    }

    if (chave > root->chave) {
        root->dir = inserir_no(root->dir, chave);
    } else if (chave < root->chave) {
        root->esq = inserir_no(root->esq, chave);
    } else {
        printf("Elemento já existente\n");
        return root;
    }

    root->height = max(altura_no(root->esq), altura_no(root->dir)) + 1;

    return balancear(root);
}

// Função para encontrar o valor mínimo em uma árvore AVL
NO* valor_minimo_no(NO* root) {
    NO* aux = root;
    while (aux && aux->esq) {
        aux = aux->esq;
    }
    return aux;
}

// Função para remover um nó da árvore AVL
NO* remover_no(NO* root, int chave) {
    if (root == NULL) {
        return NULL;
    }

    if (chave < root->chave) {
        root->esq = remover_no(root->esq, chave);
    } else if (chave > root->chave) {
        root->dir = remover_no(root->dir, chave);
    } else {
        if (root->esq == NULL || root->dir == NULL) {
            NO* temp = root->esq ? root->esq : root->dir;
            free(root);
            return temp;
        } else {
            NO* temp = valor_minimo_no(root->dir);
            root->chave = temp->chave;
            root->dir = remover_no(root->dir, temp->chave);
        }
    }

    root->height = max(altura_no(root->esq), altura_no(root->dir)) + 1;

    return balancear(root);
}
