#include <../ARVORE_LLRB/arvore_llrb.h>
#include <../AVL/bst_avl.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Estrutura de operações genéricas para árvores.
 *
 * Esta estrutura define um conjunto de ponteiros de função que abstraem
 * operações fundamentais, como inserir, remover, buscar, criar, apagar
 * e imprimir elementos de uma árvore.
 */
typedef struct arvore {
  int (*inserir)(void *arv,
                 int valor); /**< Função para inserir um elemento na árvore. */
  int (*remover)(void *arv,
                 int valor); /**< Função para remover um elemento da árvore. */
  int (*buscar)(void *arv,
                int valor); /**< Função para buscar um elemento na árvore. */
  void *(*criar)(void);     /**< Função para criar uma nova árvore. */
  void (*apagar)(
      void **arv); /**< Função para apagar a árvore e liberar memória. */
  void (*imprimir)(
      void *arv);  /**< Função para imprimir os elementos da árvore. */
  void *estrutura; /**< Ponteiro genérico para a estrutura da árvore. */
} Arvore;

/**
 * @brief Estrutura que representa um conjunto utilizando árvores.
 *
 * O conjunto é implementado como uma abstração que utiliza árvores AVL
 * ou Red-Black internamente, permitindo operações típicas de conjuntos,
 * como união, interseção, inserção e busca de elementos.
 */
typedef struct set {
  struct arvore
      *SET; /**< Estrutura de operações e dados da árvore subjacente. */
  int opt;  /**< Identificador do tipo de árvore: AVL ou Red-Black. */
} SET;

// Protocolos das funções

SET *criar_set(int opt);
void set_apagar(SET **set);
void set_imprimir(SET *set);

int set_pertence(SET *set, int valor);

void in_order_uniao(void *no, SET *set_origem, SET *set_verificados);
void set_uniao(SET *set1, SET *set2);

void set_interseccao(SET *set1, SET *set2);
void in_order_interseccao(void *no, SET *set_origem, SET *set_destino,
                          SET *set_interseccao);

int set_remover(SET *set, int valor);

int set_inserir(SET *set, int valor);

void *obter_esquerda(void *no, int opt);
void *obter_direita(void *no, int opt);
int obter_valor(void *no, int opt);

// Wrapper usado para funções menos importantes das estruturas
void *obter_esquerda(void *no, int opt) {
  // escolhe-se de acordo com a opt de estrutura escolhida
  // se for verdadeira a expressão de ser igual à 0, então é AVL
  // se falsa então é a Rubro-Negra
  return (opt == 0) ? obter_esquerda_avl(no) : obter_esquerda_llrb(no);
}

void *obter_direita(void *no, int opt) {
  return (opt == 0) ? obter_direita_avl(no) : obter_direita_llrb(no);
}

int obter_valor(void *no, int opt) {
  if (!no) {
    return -1;
  }
  if (opt == 0) {
    return obter_valor_avl((NO *)no);
  } else {
    return obter_valor_llrb((NO *)no);
  }
}

// Função para criar o set
SET *criar_set(int opt) {
  SET *s = malloc(sizeof(SET));
  if (!s)
    return NULL;

  s->SET = malloc(sizeof(Arvore));
  if (!s->SET) {
    free(s);
    return NULL;
  }

  s->opt = opt;

  /*
    De acordo com a opção escolhida pelo usuário que podemos
    colocar as funções de atributo (característica) do set
    no proprio s(set) criado agora
  */

  if (opt == 0) {
    // AVL
    s->SET->inserir = (int (*)(void *, int))avl_inserir;
    s->SET->remover = (int (*)(void *, int))avl_remover;
    s->SET->buscar = (int (*)(void *, int))avl_buscar;
    s->SET->criar = (void *(*)(void))criar_avl;
    s->SET->apagar = (void (*)(void **))avl_apagar;
    s->SET->imprimir = (void (*)(void *))avl_imprimir;
  } else if (opt == 1) {
    // LL-Red-Black
    s->SET->inserir = (int (*)(void *, int))arvllrb_inserir;
    s->SET->remover = (int (*)(void *, int))arvllrb_remover;
    s->SET->buscar = (int (*)(void *, int))arvllrb_consultar;
    s->SET->criar = (void *(*)(void))arvllrb_criar;
    s->SET->apagar = (void (*)(void **))arvllrb_apagar;
    s->SET->imprimir = (void (*)(void *))arvllrb_imprimir;
  } else {
    free(s->SET);
    free(s);
    return NULL;
  }

  s->SET->estrutura = s->SET->criar();
  return s;
}

void set_imprimir(SET *set) {
  if (!set)
    return;

  return set->SET->imprimir(set->SET->estrutura);
}

// Apaga todo o set existente
void set_apagar(SET **set) {
  if (!set || !*set)
    return;
  (*set)->SET->apagar(&((*set)->SET->estrutura));
  free((*set)->SET);
  free(*set);
  *set = NULL;
}

// Se utiliza da estrutura especificada para buscar um valor
int set_pertence(SET *set, int valor) {
  if (!set || !set->SET)
    return 0;
  return set->SET->buscar(set->SET->estrutura, valor);
}

// Se utiliza da estrutura especificada para remover um valor
int set_remover(SET *set, int valor) {
  if (!set || !set->SET)
    return -1;
  return set->SET->remover(set->SET->estrutura, valor);
}

// Se utiliza da estrutura especificada para inserir um valor
int set_inserir(SET *set, int valor) {
  if (!set)
    return 0;

  return set->SET->inserir(set->SET->estrutura, valor);
}

// Função para imprimir a união de dois conjuntos
void set_uniao(SET *set1, SET *set2) {
  if (!set1 || !set2) {
    // Verificação de validade dos conjuntos
    printf("Erro: Um ou ambos os conjuntos são inválidos.\n");
    return;
  }

  // Criação de um conjunto temporário para evitar duplicações
  SET *conjunto_verificados = criar_set(set1->opt);
  if (!conjunto_verificados) {
    printf("Erro: Falha ao criar o conjunto temporário.\n");
    return;
  }

  // printf("União dos conjuntos: ");

  // Realiza o percurso in-order para inserir os elementos únicos no conjunto
  // temporário
  in_order_uniao(set1->SET->estrutura, set1, conjunto_verificados);
  in_order_uniao(set2->SET->estrutura, set2, conjunto_verificados);

  // Imprime os elementos únicos armazenados no conjunto temporário
  conjunto_verificados->SET->imprimir(conjunto_verificados->SET->estrutura);

  // Libera o espaço alocado para o conjunto temporário
  set_apagar(&conjunto_verificados);
}

// Função auxiliar para percorrer e imprimir elementos únicos
void in_order_uniao(void *no, SET *set_origem, SET *set_verificados) {
  if (!no)
    return;

  // Percorre a subárvore esquerda
  in_order_uniao(obter_esquerda(no, set_origem->opt), set_origem,
                 set_verificados);

  // Obtém o valor do nó atual
  int valor = obter_valor(no, set_origem->opt);

  // Insere e imprime apenas valores únicos
  if (valor > 0 && !set_pertence(set_verificados, valor)) {
    set_inserir(set_verificados, valor);
  }

  // Percorre a subárvore direita
  in_order_uniao(obter_direita(no, set_origem->opt), set_origem,
                 set_verificados);
}

// Função de intersecção entre dois conjuntos
void set_interseccao(SET *set1, SET *set2) {
  if (!set1 || !set2) {
    printf("Erro: Conjuntos inválidos.\n");
    return;
  }

  // Cria um conjunto temporário para armazenar a interseção
  SET *conjunto_interseccao = criar_set(set1->opt);
  if (!conjunto_interseccao) {
    printf("Erro: Falha ao criar conjunto de interseção.\n");
    return;
  }

  // Percorre o primeiro conjunto e verifica quais valores estão no segundo
  in_order_interseccao(set1->SET->estrutura, set1, set2, conjunto_interseccao);

  // Imprime os elementos do conjunto de interseção
  set_imprimir(conjunto_interseccao);

  // Apaga o conjunto de interseção
  set_apagar(&conjunto_interseccao);
}

// Função auxiliar para percorrer em ordem e verificar interseção
void in_order_interseccao(void *no, SET *set_origem, SET *set_destino,
                          SET *set_interseccao) {
  if (!no)
    return;

  // Fica mais óbvio que estamos pegando a sub-árvore esquerda
  void *esquerda = obter_esquerda(no, set_origem->opt);
  in_order_interseccao(esquerda, set_origem, set_destino, set_interseccao);

  // valor da raiz obtido
  int valor = obter_valor(no, set_origem->opt);

  // Verifica se o valor está presente no outro conjunto
  // e se pertence adicionamos
  if (valor > 0 && set_pertence(set_destino, valor)) {
    if (!set_pertence(set_interseccao, valor)) {
      set_inserir(set_interseccao, valor);
    }
  }

  void *direita = obter_direita(no, set_origem->opt);
  in_order_interseccao(direita, set_origem, set_destino, set_interseccao);
}
