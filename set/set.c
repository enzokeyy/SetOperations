#include <../ARVORE_LLRB/arvore_llrb.h>
#include <../AVL/bst_avl.h>
#include <stdio.h>
#include <stdlib.h>

// Struct das árvores - os atributos são comuns entre as árvores
typedef struct arvore {
  int (*inserir)(void *arv, int valor);
  int (*remover)(void *arv, int valor);
  int (*buscar)(void *arv, int valor);

  void *(*criar)(void);
  void (*apagar)(void **arv);

  void (*imprimir)(void *arv);
  void *estrutura; // Ponteiro genérico para AVL ou LLRB
} Arvore;

typedef struct set {
  Arvore *SET;
  int opt;
} SET;

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

  if (opt == 0) { // AVL
    s->SET->inserir = (int (*)(void *, int))avl_inserir;
    s->SET->remover = (int (*)(void *, int))avl_remover;
    s->SET->buscar = (int (*)(void *, int))avl_buscar;
    s->SET->criar = (void *(*)(void))criar_avl;
    s->SET->apagar = (void (*)(void **))avl_apagar;
    s->SET->imprimir = (void (*)(void *))avl_imprimir;
  } else if (opt == 1) { // LL-Red-Black
    s->SET->inserir = (int (*)(void *, int))arvllrb_inserir;
    s->SET->remover = (int (*)(void *, int))arvllrb_remover;
    s->SET->buscar =
        (int (*)(void *, int))arvllrb_consultar; // Substituir por busca correta
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

void set_apagar(SET **set) {
  if (!set || !*set)
    return;
  (*set)->SET->apagar(&((*set)->SET->estrutura));
  free((*set)->SET);
  free(*set);
  *set = NULL;
}

int set_pertence(SET *set, int valor) {
  if (!set || !set->SET)
    return 0;
  return set->SET->buscar(set->SET->estrutura, valor);
}

int set_remover(SET *set, int valor) {
  if (!set || !set->SET)
    return -1;
  return set->SET->remover(set->SET->estrutura, valor);
}

int set_inserir(SET *set, int valor) {
  if (!set || !set->SET)
    return -1;
  return set->SET->inserir(set->SET->estrutura, valor);
}
