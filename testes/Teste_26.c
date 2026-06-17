#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
1. Strings (3 valores)
Defina uma função int parentesis_ok (char exp[]) que, dada uma string onde está
armazenada uma expressão aritmética com parêntesis, testa se os parêntesis estão
corretos. Por exemplo, se a expressão for "31 + ((2 - 13) - x) + 114" a função
deve retornar verdadeiro (1), enquanto que para a expressão "31 + (2 - (13 + 4)))
+ ((2 - x) + 114" deve retornar falso (0).
*/

int parentesis_ok (char exp[]) {
    int count = 0;

    for(int i = 0; exp[i] != '\0'; i++) {
        if(exp[i] == '(') {
            count++; // Abriu um parêntese
        } 
        else if(exp[i] == ')') {
            count--; // Fechou um parêntese
            
            // SEGREDO DE EXAME: Se o count ficou negativo, 
            // significa que fechámos um parêntese a mais (Ex: "abc)(" )
            if (count < 0) {
                return 0; 
            }
        }
    } 

    // Se no fim o count for exatamente 0, está perfeito!
    if(count == 0) {
        return 1;
    } else {
        return 0; // Sobraram parênteses abertos por fechar (Ex: "((abc" )
    }
}

/*
2. Arrays (3 valores)
Assuma que existe uma função int random(int N) que devolve um número aleatório
entre 0 e N-1. Defina uma função void sorteia(int a[], int N) que, dado N > 0,
preenche o array a, de tamanho N, com todos os números de 0 a N-1, colocados em
posições aleatórias. No final, cada um desses números deve aparecer exatamente uma
vez no array. Por exemplo, se N == 5, o array poderá ficar com os valores {3, 0, 4,
1, 2} ou {1, 4, 2, 0, 3}, mas não poderá ficar com {1, 1, 2, 3, 4}. Tente
minimizar o número de invocações à função random.
*/
int _random(int N) {
    return rand() % N; 
}

void sorteia(int a[], int N) {
    int i, j;

    for(i=0; i < N; i++) {
        a[i] = i; // Preencher o array
    }

    for(i = N -1; i > 0; i--) {
        j = _random(i+1);

        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

void sorteia(int a[], int N) {
    int i, j;

    for(i=0; i < N; i++) {
        a[i] = i;
    }

    for(i=N-1; i > 0; i--) {
        j = random(i+1);
        swap(a, i, j);
    }
}

/*
1. Defina a função int minInd (int v[], int N) que, dado um array v com N
elementos (N>0) calcula um índice do array onde está armazenado o menor
elemento do array v.
*/
int minInd (int v[], int N) {
    int i;
    int min = 0;

    for(i=1; i < N; i++) {
        if(v[i] < v[min]) {
            min = i;
        }
    }
    return min;
}

/*
2. Defina a função void minSort (int v[], int N) que ordena um array de N
inteiros por sucessivas chamadas à função minInd.
*/
void minSort (int v[], int N) {
    int i, temp;

    for(i = 0; i < N; i++) {

       int min = i + minInd(v + i, N-1);

       if(min != i) {
        temp = v[i];
        v[i] = v[min];
        v[min] = temp;
       }
    }
}

void swap(int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


void minSortSwap(int v[], int N) {
    int i, min;

    for(i = 0; i < N-1; i++) {
        min = minInd(v + i, N - i);
        swap(v,i,min+i);
    }
}



/*
4. Listas Ligadas (3 valores)
Defina uma função int quantosMaiores (LInt l) que, dada uma lista não vazia,
calcula quantas vezes ocorre na lista o maior elemento.
*/

typedef struct no {
    int valor;
    struct no *prox;
} *LInt;

int quantosMaiores(LInt l) {
    int count = 1;
    int max = l->valor;
    LInt atual = l->prox;

    while(atual != NULL) {
        if (atual->valor > max) {
            count = 1;
            max = atual->valor;
        } else if (atual->valor == max) {
            count++;
        }
        atual = atual->prox;
    }
    return count;
}

int quantosMaioresOtimizada(LInt l) {
    int max = l->valor;
    int count = 0;

    LInt atual = l->prox;

    while(atual != NULL) {
        if(atual->valor > max) {
            max = atual->valor;
            count = 1;
        } else if (atual->valor == max) {
            count++;
        }
        atual = atual->prox;
    }
    return count;
}

/*
5. Ordenação de Listas (3+2=5 valores)
1. Defina a função LInt retiraMaior (LInt *l) que retira da lista *l o nodo
onde se encontra o maior elemento da lista. A função retorna o endereço do nodo
removido.
*/
LInt retiraMaior (LInt *l) {
    LInt anterior = NULL;
    LInt atual = *l;

    LInt prevMax = NULL;
    LInt maxMode = *l;

    while(atual != NULL) {
        if(atual->valor > maxMode->valor) {
            maxMode = atual;
            prevMax = anterior;
        }

        anterior = atual;
        atual = atual->prox;
    }
    if(prevMax == NULL) {
        return maxMode->prox;
    } else {
        prevMax->prox = maxMode->prox;
    }
    maxMode->prox = NULL;

    return maxMode;
}

/*
2. Defina a função LInt maxSort (LInt l) que ordena uma lista por sucessivas
chamadas à função retiraMaior
*/
LInt maxSort (LInt l) {
    LInt maxMode = NULL;
    LInt novaLista = NULL;

    while(l != NULL) {
        maxMode = retiraMaior(&l);
        maxMode->prox = novaLista;
        novaLista = maxMode;
    }
    return novaLista;
}

/*
Relembre a função void mirror (ABin a) que inverte uma árvore binária. Uma árvore
diz-se simétrica se for igual à sua inversa. Defina a função int simetrica (ABin a)
que testa se uma árvore é simétrica
(por exemplo, a árvore apresentada
abaixo é simétrica).*/

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;

int espelha(ABin esq, ABin dir) {
    if(esq == NULL && dir == NULL) return 1;

    if(esq == NULL || dir == NULL) return 0;

    return (esq->valor == dir->valor) && espelha(esq->esq,dir->dir) && espelha(esq->dir,dir->esq);
}

int simetrica(ABin a) {
    if (a == NULL) return 1;

    return espelha(a->esq, a->dir);
}

int main() {
    // Casos de teste do teu enunciado
    char exp1[] = "31 + ((2 - 13) - x) + 114)";
    int array1[] = {45, 12, 89, 2, 55, 7, 34};

    // Teste 1
    printf("%s\n", exp1);
    printf("%d\n", parentesis_ok(exp1));
    printf("%d\n", minInd(array1, 6));
}