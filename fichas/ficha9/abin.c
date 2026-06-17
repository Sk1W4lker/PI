#include "abin.h"

ABin newABin (int r, ABin e, ABin d) {
   ABin a = malloc (sizeof(struct nodo));
   if (a!=NULL) {
      a->valor = r; 
      a->esq = e; 
      a->dir = d;
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

//Calcula a altura de uma  ́arvore.
int altura (ABin a){
    if(a == NULL) return 0;

    int altDir = altura(a->dir);
    int altEsq = altura(a->esq);

    if(altEsq > altDir) {
        return 1 + altEsq;
    } else {
        return 1 + altDir;
    }
}

//calcula o n ́umero de folhas
int nFolhas (ABin a){

    if(a == NULL) return 0;

    if(a->esq == NULL && a->dir == NULL) return 1;

    return nFolhas(a->esq) + nFolhas(a->dir);
}

ABin maisEsquerda (ABin a){
    if(a == NULL) return NULL;

    while(a->esq != NULL) {
        a = a->esq;
    }
    return a;
}

//escreve no ecran os elementos da  ́arvore que est ̃ao ao n ́ıvel l (Considere que a raiz de uma  ́arvore se encontra no n ́ıvel 0).
void imprimeNivel (ABin a, int l){
    // 1. Validação de segurança obrigatória
    if (a == NULL) return; 

    // 2. Se chegámos ao nível pretendido, imprime e PARA (return)
    if(l == 0) {
        printf("%d ", a->valor);
        return; 
    }

    // 3. Se ainda não chegámos, continuamos a descer nos dois ramos
    imprimeNivel(a->esq, l - 1);
    imprimeNivel(a->dir, l - 1);
}
int procuraE (ABin a, int x){
    if(a == NULL) return 0;

    if(a->valor == x) return 1;

    return (procuraE(a->esq, x) || procuraE(a->dir, x));
}

struct nodo *procura (ABin a, int x){
    if(a == NULL) return NULL;

    if(a->valor == x) return a;

    if(x < a->valor) {
        return procura(a->esq, x);
    } else {
        return procura(a->dir, x);
    }
}

int nivel (ABin a, int x){

int count = 0;

while(a != NULL &&  a->valor != x) {
    if(x < a->valor) {
        a = a->esq;
    } else {
        a = a->dir;
    }
    count++;
    }

    if(a == NULL) return -1;

    return count;
}

//imprime no ecran, por ordem crescente, todos os elementos da  ́arvore que s ̃ao (estritamente) menores do que um dado valor.
void imprimeAte (ABin a, int x){
    if(a == NULL) return; 

    imprimeAte(a->esq, x);
    
    if(a->valor < x) {
        printf("%d ", a->valor);
        imprimeAte(a->dir, x);
    }
}

//ou
void imprimeAte (ABin a, int x) {
    ABin atual = a;
    ABin pilha[100];
    int topo = 0;

    while (atual != NULL || topo > 0) {
    //Vai guardando todos os numeros até chegar ao menor.
    while(a != NULL || topo > 0) {
      pilha[topo] = atual;
      topo++;
      atual = atual->esq;
    }


    topo--; //Passa a apontar pro ultimo elemento.
    atual = pilha[topo]; //Coloca o elemento no atual.

    if(a->valor == x) {
      return; //Acaba
    }
    printf("%d ", atual->valor);

    atual = atual->dir;
  }
}

// Isto é só para o compilador não chorar enquanto não fazes a função real
void dumpABin (ABin a, int N) {
    // Fica vazio por enquanto
}

void freeABin (ABin a) {
    if (a != NULL) {
        freeABin(a->esq);
        freeABin(a->dir);
        free(a);
    }
}