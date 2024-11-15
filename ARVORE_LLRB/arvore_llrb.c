#include <stdio.h>
#include <stdlib.h>

#include "arvore_llrb.h"

typedef NO *ARVLLRB;

#define RED 1
#define BLACK 0

// Struct Nó
typedef struct no {
  NO *esq;
  NO *dir;
  int chave;
  int cor;
} NO;

// Instancia o root para que podessemos sempre tê-lo guardado
// NO**
ARVLLRB *root = NULL;

// Protocolo das Funções
int cor_no(NO *H);
void troca_cor(NO *h);

NO *rotacionar_esquerda(NO *root);
NO *rotacionar_direita(NO *root);

NO *move2_esq_red(NO *root);
NO *move2_dir_red(NO *root);

NO *balancear(NO *root);

int insere_arvllrb(ARVLLRB *raiz, int chave);
NO *insere_no(NO *root, int chave, int *resp);
int remove_arvllrb(ARVLLRB *root, int chave);
NO *remove_no(NO *root, int chave);
NO *removerMenor(NO *root);

NO *procuraMenor(NO *root);

void libera_arvllrb(NO *root);


int consulta_arvllrb(ARVLLRB *raiz, int chave);

// Funções auxiliares

// Função que retorna a cor do nó passado
int cor_no(NO *H) {
  // tem-se como padrão que os nós folha são BLACK
  if (H == NULL) {
    return BLACK;
  }

  return H->cor;
}

// Função para trocar a cor do nó, e de seus filhos.
void troca_cor(NO *h) {
  // Faz a troca para o inverso da cor atual (apenas 2 possibilidades)
  h->cor = !h->cor;

  // Agora analisamos se os nós esquerdo e direito da raiz (h) são nulos
  // e trocamos suas cores.
  if (h->esq != NULL) {
    h->esq->cor = !h->esq->cor;
  }

  if (h->dir != NULL) {
    h->dir->cor = !h->dir->cor;
  }
}

// Rotações

// Rotação à direita - nós tendendo à esquerda
NO *rotacionar_direita(NO *root) {
  // Defini-se o novoRoot
  NO *novoRoot = root->esq;

  // Já faz-se a troca da sub-árvore que não iremos mexer do novoRoot
  root->esq = novoRoot->dir;

  // Definimos o novoRoot como o root mesmo
  novoRoot->dir = root;

  // Troca de cores.
  novoRoot->cor = root->cor;
  root->cor = RED;

  return novoRoot;
}

// Rotação à esquerda - nós tendendo à direita
NO *rotacionar_esquerda(NO *root) {
  NO *novoRoot = root->dir;
  root->dir = novoRoot->esq;

  novoRoot->esq = root;

  novoRoot->cor = root->cor;
  root->cor = RED;
  return novoRoot;
}

// Movendo nós vermelhos.

/**
 * @brief Move um nó vermelho do lado direito para o lado esquerdo.
 *
 * @param root Ponteiro para o nó atual.
 * @return Ponteiro para o nó ajustado após o movimento.
 */
NO *move2_esq_red(NO *root) {
  // Troca as cores do nó atual e seus filhos (simula "emprestar" cor).
  troca_cor(root);

  // Verifica se o filho esquerdo do nó direito é vermelho.
  // Exemplo:
  // Antes:   B(root)
  //         /  \
  //       B    R
  //           /
  //          R
  // Após rotação:
  //           R
  //         /   \
  //        B     B
  if (cor_no(root->dir->esq) == RED) {
    root->dir = rotacionar_direita(root->dir);  // Ajusta o filho direito.
    root = rotacionar_esquerda(root);          // Rotaciona o nó atual à esquerda.
    troca_cor(root);                           // Restaura as cores.
  }

  return root;
}

/**
 * @brief Move um nó vermelho do lado esquerdo para o lado direito.
 *
 * @param root Ponteiro para o nó atual.
 * @return Ponteiro para o nó ajustado após o movimento.
 */
NO *move2_dir_red(NO *root) {
  // Troca as cores do nó atual e seus filhos.
  troca_cor(root);

  // Verifica se o filho esquerdo do nó esquerdo é vermelho.
  // Exemplo:
  // Antes:    B(root)
  //          /  \
  //         R    B
  //        /
  //       R
  // Após rotação:
  //           R
  //         /   \
  //        B     B
  if (cor_no(root->esq->esq) == RED) {
    root = rotacionar_esquerda(root);  // Rotaciona o nó atual à esquerda.
    troca_cor(root);                  // Restaura as cores.
  }

  return root;
}

/**
 * @brief Balanceia uma subárvore Rubro-Negra após inserções ou remoções.
 *
 * @param root Ponteiro para o nó raiz da subárvore.
 * @return Ponteiro para o nó ajustado após o balanceamento.
 */
NO *balancear(NO *root) {
  // Caso: Filho direito é vermelho, mas filho esquerdo não.
  // Exemplo:
  // Antes:   B(root)
  //           \
  //            R
  // Após rotação:
  //           R
  //         /   \
  //        B     B
  if (cor_no(root->dir) == RED) {
    root = rotacionar_esquerda(root);
  }

  // Caso: Filho esquerdo e neto esquerdo são vermelhos.
  // Exemplo:
  // Antes:      B(root)
  //            /
  //          R
  //         /
  //        R
  // Após rotação:
  //           R
  //         /   \
  //        B     B
  if (root->esq != NULL && cor_no(root->dir) == RED &&
      cor_no(root->esq->esq) == RED) {
    root = rotacionar_direita(root);
  }

  // Caso: Ambos os filhos são vermelhos.
  // Exemplo:
  // Antes:    B(root)
  //         /    \
  //       R      R
  // Após troca de cores:
  //           R
  //         /   \
  //        B     B
  if (cor_no(root->esq) == RED && cor_no(root->dir) == RED) {
    troca_cor(root);
  }

  return root;
}

/**
 * @brief Insere uma chave na árvore Rubro-Negra.
 *
 * @param raiz Ponteiro para o ponteiro da raiz da árvore.
 * @param chave Chave a ser inserida.
 * @return 1 se a inserção for bem-sucedida, 0 caso contrário.
 */
int insere_arvllrb(ARVLLRB *raiz, int chave) {
  int resp;

  // Insere a chave na subárvore.
  *(raiz) = insere_no(*raiz, chave, &resp);

  // Garante que a raiz sempre será preta após a inserção.
  if ((*raiz) != NULL)
    (*raiz)->cor = BLACK;

  return resp;
}

/**
 * @brief Insere um nó em uma subárvore Rubro-Negra.
 *
 * @param root Ponteiro para a raiz da subárvore.
 * @param chave Chave a ser inserida.
 * @param resp Ponteiro para o código de resposta da operação.
 * @return Ponteiro para o nó raiz ajustado após a inserção.
 */
NO *insere_no(NO *root, int chave, int *resp) {
  if (root == NULL) {
    // Cria um novo nó vermelho com a chave.
    NO *novo = (NO *)malloc(sizeof(NO));

    if (!novo) {  // Caso de falha na alocação.
      *resp = 0;
      return NULL;
    }

    novo->chave = chave;
    novo->cor = RED;
    novo->dir = novo->esq = NULL;
    *resp = 1;
    return novo;
  }

  // Verifica se a chave já existe.
  if (chave == root->chave)
    *resp = 0;
  else {
    // Insere na subárvore esquerda ou direita.
    if (chave < root->chave)
      root->esq = insere_no(root->esq, chave, resp);
    else
      root->dir = insere_no(root->dir, chave, resp);
  }

  // Balanceia a árvore após a inserção.
  if (cor_no(root->dir) == RED && cor_no(root->esq) == BLACK) {
    root = rotacionar_esquerda(root);
  }

	
  if (cor_no(root->esq) == RED && cor_no(root->esq->esq) == RED) {
    root = rotacionar_direita(root);
  }

  if (cor_no(root->esq) == RED && cor_no(root->dir) == RED) {
    troca_cor(root);
  }

  return root;
}
int remove_arvllrb(ARVLLRB *root, int chave) {
  // Verifica se a chave existe na árvore antes de tentar removê-la
  if (consulta_arvllrb(root, chave)) {
    NO *h = *root; // Salva a raiz atual

    // Remove o nó com a chave especificada e reorganiza a árvore
    *root = remove_no(h, chave);
    
    // Se a árvore não estiver vazia, garante que a raiz seja preta
    if (*root != NULL)
      (*root)->cor = BLACK;

    return 1; // Retorna sucesso
  } else {
    return 0; // Retorna falha (chave não encontrada)
  }
}

NO *remove_no(NO *root, int chave) {
  if (chave < root->chave) {
    // Navega para a subárvore esquerda se a chave for menor
    if (cor_no(root->esq) == BLACK && cor_no(root->esq->esq) == BLACK)
      root = move2_esq_red(root); // Prepara a subárvore esquerda para remoção
    
    // Continua a remoção recursivamente na subárvore esquerda
    root->esq = remove_no(root->esq, chave);
  } else {
    // Garante que a subárvore direita esteja balanceada
    if (cor_no(root->esq) == RED)
      root = rotacionar_direita(root); // Rotaciona para a direita se necessário

    // Caso a chave seja encontrada e o nó não tenha subárvores
    if (chave == root->chave && (root->dir == NULL)) {
      free(root); // Libera o nó atual
      return NULL; // Retorna nulo para "remover" o nó
    }

    // Prepara a subárvore direita se necessário
    if (cor_no(root->dir) == BLACK && cor_no(root->dir->esq) == BLACK)
      root = move2_dir_red(root);

    // Caso a chave seja encontrada, substitui pelo sucessor
    if (chave == root->chave) {
      NO *sucessor = procuraMenor(root->dir); // Encontra o menor na subárvore direita
      root->chave = sucessor->chave;         // Substitui a chave do nó atual
      root->dir = removerMenor(root->dir);   // Remove o sucessor
    } else {
      // Continua a remoção recursivamente na subárvore direita
      root->dir = remove_no(root->dir, chave);
    }
  }

  // Após qualquer alteração, garante que a árvore permaneça balanceada
  return balancear(root);
}

NO *removerMenor(NO *root) {
  // Se o nó atual é o menor (não possui filho à esquerda)
  if (root->esq == NULL) {
    free(root); // Libera o nó atual
    return NULL; // Retorna nulo para "remover" o nó
  }

  // Prepara a subárvore esquerda, se necessário
  if (cor_no(root->esq) == BLACK && cor_no(root->esq->esq) == BLACK)
    root = move2_esq_red(root);

  // Continua a remoção recursivamente na subárvore esquerda
  root->esq = removerMenor(root->esq);

  // Garante que a árvore esteja balanceada após a remoção
  return balancear(root);
}

NO *procuraMenor(NO *root) {
  NO *busca_no = root;

  // Navega para a esquerda até encontrar o menor nó
  while (busca_no->esq != NULL)
    busca_no = busca_no->esq;

  return busca_no; // Retorna o menor nó encontrado
}


void libera_arvllrb(NO *root) {
    if (root == NULL)
        return;
    libera_arvllrb(root->esq);
    libera_arvllrb(root->dir);
    free(root);
}


int consulta_arvllrb(ARVLLRB *raiz, int chave) {
    NO *atual = *raiz;
    while (atual != NULL) {
        if (chave == atual->chave)
            return 1; // Chave encontrada
        if (chave < atual->chave)
            atual = atual->esq;
        else
            atual = atual->dir;
    }
    return 0; // Chave não encontrada
}
