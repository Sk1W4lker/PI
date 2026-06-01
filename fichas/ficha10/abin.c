#include "abin.h"

ABin newABin (int r, ABin e, ABin d) {
   ABin a = malloc (sizeof(struct nodo));
   if (a!=NULL) {
      a->valor = r; a->esq = e; a->dir = d;
   }
   return a;
}

ABin RandArvFromArray (int v[], int N) {
   ABin a = NULL;
    int m;
    if (N > 0){
    	m = rand() % N;
    	a = newABin (v[m], RandArvFromArray (v,m), RandArvFromArray (v+m+1,N-m-1));
    }
    return a;	
}


// Questão 1 remove o nodo mais `a esquerda de uma  ́arvore (retornando esse nodo).
ABin removeMenor (ABin *a){
    if(*a == NULL) return NULL;

    ABin *atual = a;

    while((*atual)->esq != NULL) {
        a = &((*atual)->esq);
    }
    ABin temp = *atual;
    *atual = temp->dir;

    return temp;
}

void removeRaiz(ABin *a) {
    ABin min = removeMenor(&((*a)->dir));

    if (*a != NULL) {
        if (min != NULL) {
            min->esq = (*a)->esq;
            min->dir = (*a)->dir;
        } else {
            // direita é nula
            min = (*a)->esq;
        }
        free(*a);
    }
    *a = min;
}

int removeElem (ABin *a, int x){
    while(*a != NULL && (*a)->valor != x) {
        if(x < (*a)->valor) {
            a = ((*a)->esq);
        } else {
            a = ((*a)->dir);
        }

        if(*a != NULL) {
            removeRaiz(a);
            return 0;
        }
    }
    return 1;
}

// Questão 2
void rodaEsquerda (ABin *a){
    ABin b = (*a)->dir;
    (*a)->dir = b->esq;
    b->esq = (*a);
    *a = b;
}
void rodaDireita (ABin *a){
    ABin b = (*a)->esq;
    (*a)->esq = b->dir;
    b->dir = *a;
    *a = b;
}

void promoveMenor(ABin *a) {
    if (*a != NULL && (*a)->esq != NULL) {
        promoveMenor(&((*a)->esq));
        rodaDireita(a);
    }
}

void promoveMaior(ABin *a) {
    if (*a && (*a)->dir) {
        promoveMaior(&((*a)->dir));
        rodaEsquerda(a);
    }
}

ABin removeMenorAlt (ABin *a){
    return NULL;
}

// Questão 3
int constroiEspinhaAux (ABin *a, ABin *ult){
    return (-1);
}
int constroiEspinha (ABin *a){
    ABin ult;
    return (constroiEspinhaAux (a,&ult));
}

ABin equilibraEspinha (ABin *a, int n) {
	return NULL;
}

void equilibra (ABin *a) {
}
