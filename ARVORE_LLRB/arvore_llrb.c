#include "arvore_llrb.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct NO* ARVLLRB;

#define RED 1
#define BLACK 0

typedef struct no{
	NO* esq;
	NO* dir;
	int chave;
	int cor;
}NO;

// Instancia o root para que podessemos sempre tê-lo guardado
ARVLLRB* root;


// Funções auxiliares
int cor_no(NO* H){
	if(H == NULL){
		return BLACK;
	}

	return H->cor;
}


void troca_cor(NO* h){
	h->cor = !h->cor;

	if(h->esq != NULL){
		h->esq->cor = !h->esq->cor;
	}

	if(h->dir != NULL){
		h->dir->cor = !h->dir->cor;
	}
}

// Rotações

NO* rotacionar_esquerda(NO* root){
	NO* novoRoot = root->dir;
	root->dir = novoRoot->esq;
	novoRoot->esq = root;
	novoRoot->cor = root->cor;
	root->cor = RED;
	return novoRoot;
}

NO* rotacionar_direita(NO* root){
	NO* novoRoot = root->esq;
	root->esq = novoRoot->dir;
	novoRoot->dir = root;
	novoRoot->cor = root->cor;
	root->cor = RED;

	return novoRoot;
}


// Movendo nós vermelhos.


NO* move2_esq_red(NO* root){
	troca_cor(root);

	if(cor_no(root->dir->esq) == RED){
		root->dir = rotacionar_direita(root->dir);
		root = rotacionar_esquerda(root);
		troca_cor(root);
	}

	return root;
}


NO* move2_dir_red(NO* root){
	troca_cor(root);

	if(cor_no(root->esq->esq) == RED){
		root = rotacionar_esquerda(root);
		troca_cor(root);
	}

	return root;
}


// Balancear

NO* balancear(NO* root){
	if(cor_no(root->dir) == RED){
		root = rotacionar_esquerda(root);
	}

	// filho a direita e neto à esquerda, dois casos, 
	if(root->esq != NULL && cor_no(root->dir) == RED &&
		cor_no(root->esq->esq) == RED){
		root = rotacionar_direita(root);
}

if(cor_no(root->esq) == RED && cor_no(root->dir) == RED){
	troca_cor(root);
}

return root;
}


int insere_arvllrb(ARVLLRB* raiz, int chave){
	int resp;

	*(raiz) = insereNO(*raiz, chave, &resp);

	if((*raiz) != NULL)
		(*raiz)->cor = BLACK;

	return resp;
}


NO* insereNO(NO* root, int chave, int *resp){
	if(root == NULL){
		NO* novo = (NO*) malloc(sizeof(NO));

		if(!novo){
			*resp = 0;
			return NULL;
		}

		novo->chave = chave;
		novo->cor = RED;
		novo->dir = novo->esq = NULL;
		*resp = 1;
		return novo;
	}

	if(chave == root->chave)
		*resp = 0;
	else{
		if(chave < root->chave)
			root->esq = insereNO(root->esq, chave, resp);
		else 
		root->dir = insereNO(root->dir, chave, resp);
	}

	if(cor_no(root->dir) == RED && cor_no(root->esq) == BLACK){
		root = rotacionar_esquerda(root);
	}

	if(cor_no(root->esq) == RED && cor_no(root->esq->esq) == RED){
		root = rotacionar_direita(root);
	}

	if(cor_no(root->esq) == RED && cor_no(root->dir) == RED){
		troca_cor(root);
	}

	return root;
}

int remove_arvllrb(ARVLLRB *root, int chave){
	if(consulta_arvllrb(root, chave)){
		NO* h = *root;

		*root = remove_no(h, chave);
		if(*root != NULL)
			(*root)->cor = BLACK;
		return 1;
		
	}else{
		return 0;
	}
}

NO* remove_no(NO* root, int chave){
	if(chave < root->chave){
		if(cor_no(root->esq) == BLACK && cor_no(root->esq->esq) == BLACK)
			root = move2_esq_red(root);

		root->esq = remove_no(root->esq, chave);
	}
	else{
		// condição normal para rotacionar
		if(cor_no(root->esq) == RED)
			root = rotacionar_direita(root);


		if(chave == root->chave && (root->dir == NULL)){
			free(root);
			return NULL;
		}

		if(cor_no(root->dir) == BLACK && cor_no(root->dir->esq) == BLACK)
			root = move2_dir_red(root);

		if(chave == root->chave){
			NO* sucessor = procuraMenor(root->dir);
			root->chave = sucessor->chave;
			root->dir = removerMenor(root->dir);
		}else
			root->dir = remove_no(root->dir, chave);
	}
	return balancear(root);
}



NO* removerMenor(NO* root){
	if(root->esq == NULL){
		free(root);
		return NULL;
	}
	if(cor_no(root->esq) == BLACK && cor_no(root->esq->esq) == BLACK)
		root = move2_esq_red(root);

	root->esq = removerMenor(root->esq);

	return balancear(root);
}

NO* procuraMenor(NO* root){
	NO* busca_no = root;

	while(busca_no && busca_no->esq)
		busca_no = busca_no->esq;

	return busca_no;
}