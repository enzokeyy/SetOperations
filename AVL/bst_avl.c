#include <stdio.h>
#include <stdlib.h>

#include "bst_avl.h"

// Struct Nó
typedef struct no {
    struct no* esq;
    struct no* dir;
    int chave;
    int height;
} NO;

// Protocolo das Funções

int altura_no(NO* root);
int max(int a, int b);

NO* criar_no(int chave);

NO* rotacionar_direita(NO* root);
NO* rotacionar_esquerda(NO* root);

NO* rotacionar_esquerda_direita(NO* root);
NO* rotacionar_direita_esquerda(NO* root);

int fb_no(NO* root);
NO* balancear(NO* root);

NO* inserir_no(NO* root, int chave);
NO* valor_minimo_no(NO* root);


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
    
    //Altura do nó ao ser criado é 1
    newNo->height = 1;
    newNo->chave = chave;
    return newNo;
}

// Rotação à direita
/*
    Apenas trocamos os vetores, os nomes estão bem sugestivos, e 
    pensamos o "filho_filho" como uma possível existência. 
*/
NO* rotacionar_direita(NO* root) {
    // novoRoot é o esquerdo do root atual.
    NO* novoRoot = root->esq;
    NO* filho_filho = novoRoot->dir;

    // Colocamos o novoRoot, que antes, fazendo uma altura maior, estava no meio
    // dos filho_filho e do root, como o que faz uma "balança" com o root
    novoRoot->dir = root;
    // Perceba que não mexemos com a sub-árvore esquerda do novoRoot. 
    root->esq = filho_filho;


    // Ajusta-se a altura de cada um dos nós que mexemos, menos o filho_filho
    // que apenas foi de um nó para outro, não mexemos com sua esquerda nem direita sub-árvores.
    root->height = max(altura_no(root->esq), altura_no(root->dir)) + 1;
    novoRoot->height = max(altura_no(novoRoot->esq), altura_no(novoRoot->dir)) + 1;

    return novoRoot;
}

// Rotação à esquerda 
// Segue a mesma proposta da rotação à direita. Só que agora
// os nós tendem à direita.

/*
        (root)
                        (novoRoot)

                (filho_filho)    

*/
NO* rotacionar_esquerda(NO* root) {
    NO* novoRoot = root->dir;
    NO* filho_filho = novoRoot->esq;

    novoRoot->esq = root;
    root->dir = filho_filho;

    root->height = max(altura_no(root->esq), altura_no(root->dir)) + 1;
    novoRoot->height = max(altura_no(novoRoot->esq), altura_no(novoRoot->dir)) + 1;

    return novoRoot;
}

// Rotação dupla à esquerda
NO* rotacionar_esquerda_direita(NO* root) {
    /*  
    Estado inicial:

            A
        
        B
            
             C
    


    
    Rotação à esquerda do B e C

            A
        
        C

    B

    

    Rotação à direita de A - C - B
        
        C

    B       A


    Veja que faz sentido, já que segue os pré-requisitos da Árvore Binária de Busca
    */


    root->esq = rotacionar_esquerda(root->esq);
    return rotacionar_direita(root);
}


// Rotação dupla à direita
NO* rotacionar_direita_esquerda(NO* root) {
    root->dir = rotacionar_direita(root->dir);
    return rotacionar_esquerda(root);
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
        // Se for nulo o nó atual, então pode criar o nó com a chave passada.
        return criar_no(chave);
    }
    // Faz-se o ercurso para achar onde é possível (nó nulo) inserir o nó 
    if (chave > root->chave) {
        // Perceba que o retorno da função deve ser um NO*, logo, devemos passar 
        // o nó para receber a entrada dele mesmo na função recursivamente.
        root->dir = inserir_no(root->dir, chave);
    } else if (chave < root->chave) {
        root->esq = inserir_no(root->esq, chave);
    } else {
        // Se achou a chave, não podemos adicionar outro nó com a mesma chave
        printf("Elemento já existente\n");
        return root;
    }

    // Após inserir, devemos calcular novamente a altura do nó

    root->height = max(altura_no(root->esq), altura_no(root->dir)) + 1;
    // Pegamos o máximo e somamos um, já que somamos a altura deve mesmo

    // Balanceamos o root (AVL)
    return balancear(root);
}


// Função para encontrar o valor mínimo em uma árvore AVL
NO* valor_minimo_no(NO* root) {
    NO* aux = root;
    // Retornamos o menor valor 
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
    // Percurso em Ordem para achar a chave de acordo com o nó atual (root)
    if (chave < root->chave) {
        root->esq = remover_no(root->esq, chave);
    } else if (chave > root->chave) {
        root->dir = remover_no(root->dir, chave);
    } else {
        // Caso em que foi encontrado a chave.

        // Resolvemos o caso 1, 2 (0 filhos, 1 filho), com um só if
        if (root->esq == NULL || root->dir == NULL) {
            NO* aux_apagar = root;

            NO* temp = root->esq ? root->esq : root->dir;

            free(aux_apagar);

            return temp;

            // Se nem o filho direito ou o esquerdo são nulos, então, ambos são verdadeiros.
        } else {
            NO* temp = valor_minimo_no(root->dir);
            // Pegamos o menor valor a direita, logo, o SUCESSOR

            // Trocamos o valor da chave que buscamos pelo do root.
            root->chave = temp->chave;

            // Então agora passamos recursivamente para eliminar o nó (FOLHA)
            // que está à direita do root (onde foi achado o menor) para remover 
            // o nó com a chave passada.
            root->dir = remover_no(root->dir, temp->chave);
        }
    }

    // Ajustamos a altura do root
    root->height = max(altura_no(root->esq), altura_no(root->dir)) + 1;

    // Balanceamos a partir do root
    return balancear(root);
}
