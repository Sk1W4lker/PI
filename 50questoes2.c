#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Listas Ligadas
Considere o seguinte tipo para representar listas ligadas de inteiros
*/

typedef struct lligada {
    int valor;
    struct lligada *prox;
} *LInt;

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;

/*
1. Apresente uma definição não recursiva da função int length (LInt) que calcula o comprimento de uma lista ligada
*/
int length(LInt l) {
    int count = 0;

    while (l != NULL) {
        count++;
        l = l->prox; // Avança para o próximo elemento
    }

    return count;
}

/*
2. Apresente uma definição não recursiva da função void freeL (LInt) que liberta o espaço ocupado por uma lista
*/
void freeL(LInt l) {
    LInt temp = NULL;

    while (l != NULL) {
        temp = l->prox; // Guarda a referência do próximo antes de libertar o atual
        free(l);        // Liberta o nó atual
        l = temp;       // Avança para o próximo
    }
}

/*
3. Apresente uma definição não recursiva da função void imprimeL (LInt) que imprime no ecran os elementos de uma lista (um por linha)
*/
void imprimeL (LInt l) {
    printf("[ ");
    while(l != NULL) {
        printf("%d ", l->valor); // Imprime o valor da estrutura
        l = l->prox;             // Avança para o próximo
    }
    printf("]\n");
}

/*
4. Apresente uma definição não recursiva da função LInt reverseL (LInt) que inverte uma lista (sem criar uma nova lista).
*/
LInt reverseL(LInt l) {
    LInt build = NULL;
    LInt temp = NULL;

    while (l != NULL) {
        temp = l->prox;   // Guarda o resto da lista
        l->prox = build;  // O nó atual passa a apontar para o que já foi invertido
        build = l;        // A nova cabeça da lista passa a ser o nó atual
        l = temp;         // Avança na lista original
    }

    return build;
}

/*
5. Apresente uma definição não recursiva da função void insertOrd (LInt *l, int) que insere ordenadamente um elemento numa lista ordenada.
*/
void insertOrd(LInt *l, int v) {
    // Percorre a lista enquanto o valor atual for menor que v
    while (*l != NULL && (*l)->valor < v) {
        l = &((*l)->prox);
    }

    // Aloca memória para o novo nó
    LInt temp = malloc(sizeof(struct lligada));
    if (temp != NULL) {
        temp->valor = v;
        temp->prox = *l; // O novo nó aponta para o elemento atual/maior
        *l = temp;       // O ponteiro anterior passa a apontar para este novo nó
    }
}

/*
6. Apresente uma definição não recursiva da função int removeOneOrd (LInt *, int) que remove um elemento de uma lista ordenada. Retorna 1 caso o elemento a remover não exista, 0 no outro caso.
*/
int removeOneOrd (LInt *l, int v) {
    // Procura o elemento v ou o fim da lista
    while(*l != NULL && (*l)->valor < v) {
        l = &((*l)->prox);
    }

    // Se encontrou o elemento
    if(*l != NULL && (*l)->valor == v) {
        LInt temp = (*l)->prox;
        free(*l);   // Liberta a memória do nó
        (*l) = temp; // Liga o anterior ao próximo elemento
        return 0;
    }
    return 1;
}

/*
7. Defina uma função void merge (LInt *r, LInt a, LInt b) que junta duas listas ordenadas (a e b) numa única lista ordenada (*r).
*/
void merge (LInt *r, LInt a, LInt b) {
    while(a != NULL && b != NULL){
        if(a->valor < b->valor) {
            *r = a;      // O resultado aponta para o nó de a
            a = a->prox;
        } else {
            *r = b;      // O resultado aponta para o nó de b
            b = b->prox;
        }
        r = &((*r)->prox); // Avança o ponteiro de inserção
    }
    // Conecta o que sobrou de qualquer uma das listas
    if(a != NULL) {
        *r = a;
    } else {
        *r = b;
    }
}

/*
8. Defina uma função void splitQS (LInt l, int x, LInt *mx, LInt *Mx) que, dada uma lista ligada l e um inteiro x, parte a lista em duas (retornando os endereços dos primeiros elementos da lista em *mx e *Mx): uma com os elementos de l menores do que x e a outra com os restantes.
*/
void splitQS (LInt l, int x, LInt *mx, LInt *Mx) {
    while(l != NULL) {
        if (l->valor < x) {
            *mx = l;             // Adiciona à lista de menores
            mx = &((*mx)->prox);
        } else {
            *Mx = l;             // Adiciona à lista de restantes
            Mx = &((*Mx)->prox);
        }
        l = l->prox;
    }
    *mx = *Mx = NULL; // Termina ambas as listas com NULL
}

/*
9. Defina uma função LLig parteAmeio (LLig *l) que, parte uma lista não vazia *l a meio.
*/
LInt parteAmeio (LInt *l) {
    int metade = length(*l) / 2;
    LInt out = *l;   // A primeira metade começa no início
    LInt * temp = l;

    while (metade > 0) {
        metade--;
        temp = &((*temp)->prox);
    }
    *l = *temp;     // A lista original passa a ser a segunda metade
    *temp = NULL;   // Corta a ligação da primeira metade para fechar a lista

    return out;     // Retorna a primeira metade
}

/*
10. Apresente uma definição não recursiva da função int removeAll (LInt *, int) que remove todas as ocorrências de um dado inteiro de uma lista, retornando o número de células removidas.
*/
int removeAll (LInt *l, int x) {
    int count = 0;

    while (*l != NULL) { 
        if((*l)->valor == x) {
            int temp = ((*l)->prox); // Nota: temp deveria ser LInt para armazenar o ponteiro
            free(*l);
            *l = temp;
            count++;
        } else {
            l = &((*l)->prox);
        }
    }
    return count;
}

/*
11. Apresente uma definição da função int removeDups (LInt *) que remove os valores repetidos de uma lista (deixando apenas a primeira ocorrência).
*/
int removeDups(LInt *l) {
    int total = 0;
    while (*l != NULL) {
        // Para cada elemento, remove todas as suas cópias que aparecem depois dele
        total += removeAll(&((*l)->prox), (*l)->valor);
        l = &((*l)->prox);
    }
    return total;
}

/*
12. Apresente uma definição da função int removeMaiorL (LInt *) que remove (a primeira ocorrência) o maior elemento de uma lista não vazia, retornando o valor desse elemento.
*/
int removeMaiorL(LInt *l) {
    int resultado = 0;
    LInt *max = l;

    // Procura o endereço do ponteiro para o maior valor
    while(*l != NULL) {
        if((*l)->valor > (*max)->valor) {
            max = l;
        }
        l = &((*l)->prox);
    }

    LInt temp = ((*max)->prox);
    resultado = ((*max)->valor);
    free(*max);   // Liberta o nó com o maior valor
    *max = temp;  // Re-liga a lista

    return resultado;
}

/*
13. Apresente uma definição não recursiva da função void init (LInt *) que remove o último elemento de uma lista não vazia (libertando o correspondente espaço).
*/
void init (LInt *l) {
    // Percorre a lista até encontrar o ponteiro para o último nó
    while(*l != NULL && (*l)->prox != NULL) {
        l = &((*l)->prox);
    }

    free(*l);   // Liberta o último nó
    *l = NULL;  // O ponteiro do penúltimo nó (ou cabeça) passa a ser NULL
}

/*
14. Apresente uma definição não recursiva da função void appendL (LInt *, int) que acrescenta um elemento no fim da lista.
*/
void appendL (LInt *l, int x) {
    // Percorre até ao ponteiro que guarda o NULL final
    while(*l != NULL) {
        l = &((*l)->prox);
    }

    // Aloca espaço e insere o novo nó no fim
    *l = malloc(sizeof(struct lligada));
    if (*l != NULL) {
        (*l)->valor = x;
        (*l)->prox = NULL;
    }
}

/*
15. Apresente uma definição da função void concatL (LInt *a, LInt b) que acrescenta a lista b à lista *a.
*/
void concatL (LInt *a, LInt b) {
    // Percorre até ao fim da lista a
    while(*a != NULL) {
        a = &((*a)->prox);
    }
    // Faz o NULL da lista a apontar para o início da lista b
    *a = b;
}

/*
16. Apresente uma definição da função LInt cloneL (LInt) que cria uma nova lista ligada com os elementos pela ordem em que aparecem na lista argumento.
*/
LInt cloneL (LInt l) {
    LInt temp = NULL;
    LInt *build = &temp; // Ponteiro para onde o novo nó será construído

    while (l != NULL) {
        *build = malloc(sizeof(struct lligada)); // Cria a caixa
        (*build)->valor = l->valor;              // Copia o valor
        l = l->prox;                             // Avança na lista original
        build = &((*build)->prox);               // Avança para o próximo campo prox
    }
    
    *build = NULL; // Escreve NULL na última seta para fechar a lista

    return temp;
}

/*
17. Apresente uma definição não recursiva da função LInt cloneRev (LInt) que cria uma nova lista ligada com os elementos por ordem inversa.
*/
LInt cloneRev(LInt l) {
    LInt temp = NULL;
    LInt build = NULL;

    while (l != NULL) {
        build = malloc(sizeof(struct lligada));
        build->valor = l->valor;
        build->prox = temp; // O novo nó aponta para o que já foi construído (inserção à cabeça)
        temp = build;
        l = l->prox;
    }

    return temp;
}

/*
18. Defina uma função int maximo (LInt l) que calcula qual o maior valor armazenado numa lista não vazia.
*/
int maximo(LInt l) {
    int max = l->valor;
    l = l->prox;

    while (l != NULL) {
        if (l->valor > max) {
            max = l->valor;
        }
        l = l->prox;
    }

    return max;
}

/*
20. Apresente uma definição iterativa da função int drop (int n, LInt *l) que apaga os n primeiros elementos.
*/
int drop(int n, LInt *l) {
    int count = 0;
    LInt temp = NULL;

    while (*l != NULL && n > 0) {
        n--;
        count++;
        temp = (*l)->prox;
        free(*l); // Liberta o nó atual
        *l = temp; // A cabeça da lista passa a ser o próximo
    }

    return count;
}

/*
21. Defina uma função LInt Nforward (LInt l, int N) que dá o endereço do elemento N posições à frente numa lista circular.
*/
LInt Nforward (LInt l, int N) {
    if(l == NULL) {
        return NULL;
    }
    while(N > 0) {
        l = l->prox;
        N--;
    }
    return l;
}

/*
22. Defina uma função int listToArray (LInt l, int v[], int N) que preenche o array v com elementos da lista.
*/
int listToArray (LInt l, int v[], int N) {
    int count = 0;

    while(l != NULL && count < N) {
        v[count] = l->valor;
        count++;
        l = l->prox;
    }
    return count;
}

/*
23. Defina uma função LInt arrayToList(int v[], int N) que constrói uma lista a partir de um array.
*/
LInt arrayToList(int v[], int N) {
    LInt temp = NULL;
    LInt * build = &temp;

    for (int i = 0; i < N; i++) {
        *build = malloc(sizeof(struct lligada));
        (*build)->valor = v[i];
        build = &((*build)->prox);
    }

    *build = NULL;

    return temp;
}

/*
24. Defina uma função LInt somasAcL (LInt l) que constrói uma lista contendo as somas acumuladas.
*/
LInt somasAcL (LInt l) {
    LInt temp = NULL;
    LInt * build = &temp;
    int sum = 0;

    while(l != NULL) {
        *build = malloc(sizeof(struct lligada));
        sum += l->valor;
        (*build)->valor = sum;
        build = &((*build)->prox);
        l=l->prox;
    }
    *build = NULL;

    return temp;
}

/*
25. Defina uma função void remreps (LInt l) que elimina valores repetidos de uma lista ordenada.
*/
void remreps(LInt l) {
    if (l != NULL) {
        int current = l->valor;
        LInt *build = &l;
        build = &((*build)->prox);
        LInt temp = NULL;

        while(*build != NULL) {
            if((*build)->valor == current){
                temp = ((*build)->prox);
                free(*build);
                *build = temp;
            } else {
                current = (*build)->valor;
                build = &((*build)->prox);
            }
        }
    }
}

/*
26. Defina uma função LInt rotateL (LInt l) que coloca o primeiro elemento de uma lista no fim.
*/
LInt rotateL(LInt l) {
    if (l == NULL || l->prox == NULL) {
        return l;
    }

    LInt *temp = &l;

    while (*temp != NULL) {
        temp = &((*temp)->prox);
    }

    LInt out = l->prox;
    l->prox = NULL;
    *temp = l;

    return out;
}

/*
27. Defina uma função LInt parte (LInt l) que separa elementos de posições ímpares e pares.
*/
LInt parte(LInt l) {
    LInt y = NULL, *ytemp = &y, *ltemp = &l;

    if (l != NULL) {
        int i = 1;
        ltemp = &(*ltemp)->prox;
        l = l->prox;

        while (l != NULL) {
            if (i % 2 == 0) {
                *ltemp = l;
                ltemp = &((*ltemp)->prox);
            } else {
                *ytemp = l;
                ytemp = &((*ytemp)->prox);
            }

            l = l->prox;
            i++;
        }

        *ltemp = *ytemp = NULL;
    }
    return y;
}

/*
28. Apresente uma definição da função int altura (ABin) que calcula a altura de uma árvore binária.
*/
int altura (ABin a) {
    // 1. Caso Base (Árvore Vazia)
    if (a == NULL) {
        return 0;
    }
    
    // 2. Passo Recursivo
    int altEsq = altura(a->esq);
    int altDir = altura(a->dir);
    
    // 3. Decisão
    if (altEsq > altDir) {
        return 1 + altEsq;
    } else {
        return 1 + altDir;
    }
}

/*
29 Defina uma função ABin cloneAB (ABin) que cria uma cópia de uma árvore.
*/
ABin cloneAB (ABin a) {
    if(a == NULL) return NULL; 

    ABin temp = malloc(sizeof(struct nodo));
    temp->valor = a->valor;
    temp->esq = cloneAB(a->esq);
    temp->dir = cloneAB(a->dir);
    
    return temp;
}

/*
30 Defina uma função void mirror (ABin *) que inverte uma árvore (efeito espelho).
*/
void mirror(ABin *a) {
    if(a != NULL && *a != NULL) {
        ABin temp = (*a)->esq;
        (*a)->esq = (*a)->dir;
        (*a)->dir = temp;

        mirror(&((*a)->esq));
        mirror(&((*a)->dir));
    }
}

/*
31. Defina a função void inorder (ABin, LInt *) que cria uma lista ligada a partir de uma travessia inorder.
*/
void inorder (ABin a, LInt *l) {
    if(a!=NULL) {
        inorder(a->esq,l);

        *l = malloc(sizeof(struct lligada));
        (*l)->valor = a->valor;
        l = &((*l)->prox);

        inorder(a->dir,l);
    }
}

/*
32. Defina a função void preorder (ABin, LInt *) que cria uma lista ligada a partir de uma travessia preorder.
*/
void preorder(ABin a, LInt *l) {
    if (a != NULL) {
        *l = malloc(sizeof(struct lligada));
        (*l)->valor = a->valor;
        l = &((*l)->prox);
    
        preorder(a->esq, l);
        preorder(a->dir, l);
    } else {
        *l = NULL;
    }
}

/*
33. Defina a função void posorder (ABin, LInt *) que cria uma lista ligada a partir de uma travessia posorder.
*/
void posorder(ABin a, LInt *l) {
    if (a != NULL) {
        inorder(a->esq, l); // Nota: Original usava inorder para subárvores
        inorder(a->dir, l);

        *l = malloc(sizeof(struct lligada));
        (*l)->valor = a->valor;
        l = &((*l)->prox);
    }
}

/*
34. Apresente uma definição da função int depth (ABin a, int x) que calcula o nível de um elemento.
*/
int depthRec(ABin a, int x, int nivel) {
    if (a == NULL) return -1;
    if (a->valor == x) return nivel;

    int esq = depthRec(a->esq, x, nivel + 1);
    if (esq != -1) return esq;

    return depthRec(a->dir, x, nivel + 1);
}

int depth(ABin a, int x) {
    return depthRec(a, x, 0); // Original usava 0 como nível inicial
}

/*
35. Defina uma função int freeAB (ABin a) que liberta o espaço da árvore e retorna o número de nós.
*/
int freeAB (ABin a){
    if (a == NULL) return 0;

    int count = 1;
    count += freeAB(a->esq);
    count += freeAB(a->dir);
    free(a);

    return count;
}

/*
36. Defina uma função int pruneAB (ABin *a, int l) que remove elementos a profundidade superior a l.
*/
int pruneAB(ABin *a, int l) {
    if (l == 0) return freeAB(*a);
    // Nota: Original não verificava se *a era NULL antes de avançar recursivamente
    return pruneAB(&((*a)->esq), l - 1) + pruneAB(&((*a)->dir), l - 1);
}

/*
37. Defina uma função int iguaisAB (ABin a, ABin b) que testa se duas árvores são iguais.
*/
int iguaisAB (ABin a, ABin b) {
    if(a == NULL && b == NULL) return 1;
    if(a == NULL || b == NULL) return 0;
    return (a->valor == b->valor) && iguaisAB(a->esq, b->esq) && iguaisAB(a->dir, b->dir);
}

/*
38. Defina uma função LInt nivelL (ABin a, int n) que constrói uma lista com valores no nível n.
*/
void nivelLRec(ABin a, int n, LInt * build) {
    if (a != NULL && n > 0) {
        if (n == 1) {
            *build = malloc(sizeof(struct lligada));
            (*build)->valor = a->valor;
            build = &((*build)->prox);
        } else {
            nivelLRec(a->esq, n - 1, build);
            nivelLRec(a->dir, n - 1, build);
        }
    }
}

LInt nivelL(ABin a, int n) {
    LInt temp = NULL;
    nivelLRec(a, n, &temp);
    return temp;
}

/*
39. Defina uma função int nivelV (ABin a, int n, int v[]) que preenche o vetor v com elementos no nível n.
*/
int nivelV(ABin a, int n, int v[]) {
    if (a == NULL || n < 1) return 0;

    int count = 0;
    if (n == 1) {
        v[count] = a->valor;
        count++;
    } else {
        count += nivelV(a->esq, n - 1, v + count);
        count += nivelV(a->dir, n - 1, v + count);
    }

    return count;
}

/*
40. Defina uma função int dumpAbin (ABin a, int v[], int N) que preenche o array segundo travessia inorder.
*/
int dumpAbin(ABin a, int v[], int N) {
    if (a == NULL) return 0;

    int count = dumpAbin(a->esq, v, N);
    if (count < N) {
        v[count++] = a->valor;
        count += dumpAbin(a->dir, v + count, N - count); // Ajustado para não exceder N
    }

    return count;
}

/*
41. Defina uma função ABin somasAcA (ABin a) que calcula a árvore das somas acumuladas.
*/
ABin somasAcA(ABin a) {
    if (a == NULL) return NULL;

    ABin esq = somasAcA(a->esq);
    ABin dir = somasAcA(a->dir);

    ABin temp = malloc(sizeof(struct nodo));

    temp->valor = a->valor;
    if (esq != NULL) temp->valor += esq->valor;
    if (dir != NULL) temp->valor += dir->valor;

    temp->esq = esq;
    temp->dir = dir;

    return temp;
}

/*
42. Defina uma função int contaFolhas (ABin a) que conta os nodos folha.
*/
int contafolhas(ABin a) {
    if (a == NULL) return 0;

    if (a->esq == NULL && a->dir == NULL) return 1;

    return contafolhas(a->esq) + contafolhas(a->dir);
}

/*
43. Defina uma função ABin cloneMirror (ABin a) que cria uma árvore espelhada nova.
*/
ABin cloneMirror(ABin a) {
    ABin temp = NULL;
    if (a != NULL) {
        temp = (ABin)malloc(sizeof(struct nodo));

        temp->valor = a->valor;

        temp->esq = cloneMirror(a->dir);
        temp->dir = cloneMirror(a->esq);
    }

    return temp;
}

/*
44. Adiciona elemento a uma BST (não recursiva).
*/
int addOrd(ABin *a, int x) {
    while (*a != NULL) {
        if ((*a)->valor == x) {
            return 1;
        }
        else if ((*a)->valor < x) {
            a = &((*a)->dir);
        }
        else {
            a = &((*a)->esq);
        }
    }

    *a = malloc(sizeof(struct nodo));
    (*a)->valor = x;
    (*a)->esq = (*a)->dir = NULL;

    return 0;
}

/*
45. Testa se elemento pertence a uma BST (não recursiva).
*/
int lookupAB(ABin a, int x) {
    while (a != NULL) {
        if (a->valor == x) {
            return 1; 
        } 
        else if (a->valor < x) {
            a = a->dir; 
        } 
        else {
            a = a->esq; 
        }
    }

    return 0; 
}

/*
46. Calcula o nível de x numa BST.
*/
int depthOrd(ABin a, int x) {
    int nivel = 1;

    while (a != NULL) {
        if (a->valor == x) {
            return nivel;
        } 
        else if (a->valor < x) {
            a = a->dir; 
        } 
        else {
            a = a->esq; 
        }
        nivel++; 
    }

    return -1; 
}

/*
47. Calcula o maior elemento de uma BST (não recursiva).
*/
int maiorAB (ABin a) {
    while(a->dir != NULL) {
        a = a->dir;
    }
    return (a->valor);
}

/*
48. Remove o maior elemento de uma BST.
*/
void removeMaiorAB(ABin *a) {
    if (*a != NULL) {

        while ((*a)->dir != NULL) {
            a = &((*a)->dir);
        }

        ABin temp = (*a)->esq;
        free(*a);
        *a = temp;
    }
}

/*
49. Conta quantos elementos são maiores que x numa BST.
*/
int quantosMaiores(ABin a, int x) {
    if (a == NULL) return 0;

    if (a->valor > x)
        return 1 + quantosMaiores(a->esq, x) + quantosMaiores(a->dir, x);
    else
        return quantosMaiores(a->dir, x);
}

/*
50. Constrói uma BST a partir de uma lista ordenada.
*/
void listToBTree(LInt l, ABin *a) {
    if (l != NULL) {
        LInt temp = parteAmeio(&l);

        *a = malloc(sizeof(struct nodo));
        (*a)->valor = l->valor;
        (*a)->esq = (*a)->dir = NULL;

        listToBTree(temp, &((*a)->esq));
        listToBTree(l->prox, &((*a)->dir));
    }
}

/*
51. Testa se uma árvore é de procura.
*/
int deProcuraRec(ABin a, int *prev) {
    if (a == NULL) return 1;

    int cond = deProcuraRec(a->esq, prev);
    if (cond != 0) {
        if (prev == NULL) {
            prev = &(a->valor);
        }

        cond = a->valor >= *prev;
    }

    return cond && deProcuraRec(a->dir, prev);
}

int deProcura(ABin a) {
    return deProcuraRec(a, NULL);
}