#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
1. Implemente a função int nesimo(int a[], int N, int i) que dado 
um array de tamanho N > 0 e um inteiro 0 < i <= N devolve o i-ésimo 
menor elemento do array. Por exemplo, se i == 1 a função deve retornar o 
menor elemento do array. 
*/

int nesimo(int a[], int N, int i) {
int min;

    for(int pos = 0; pos < N-1; pos++) {
            min = pos;        
        for (int j = i + 1; j < N; j++) {
            if(a[min] > a[j]) {
                min = j;
            }
        }
        if(min != pos) {
            int temp = a[min];
            a[min] = a[pos];
            a[pos] = temp;
        }
    }
    return a[i-1];
}

/*
2. Implemente a função LInt removeMaiores(LInt l, int x) que remove 
de uma lista ordenada l todos os elementos maiores que x, devolvendo 
a lista resultante. Considere a definição usual do tipo LInt. 
*/

typedef struct LInt_nodo { 
    int valor; 
    struct LInt_nodo *prox; 
} *LInt;

LInt removeMaiores(LInt l, int x) {
    LInt atual = l;
    LInt anterior = NULL;

    while(atual != NULL) {
        if(atual->valor <= x) {
            anterior = atual;
            atual = atual->prox;
        } else {
            LInt aux = atual->prox;

            if (anterior == NULL) {
                l = aux; 
            } else {
            anterior->prox = aux;
        }
        free(atual);
        atual = aux;
        }
    }
    return l;
}

/*
3. Implemente a função LInt caminho(ABin a, int x) que, dada uma 
árvore binária de procura a e um valor x, devolve uma lista com todos os 
valores desde a raiz até x (inclusivé). Se x não existir na árvore, deve 
devolver NULL. Considere a definição usual do tipo ABin (o tipo LInt foi 
dado na questão anterior). 
*/
typedef struct ABin_nodo { 
    int valor; 
    struct ABin_nodo *esq, *dir; 
} *ABin; 

LInt caminho(ABin a, int x) {
    if(a == NULL) return NULL;

    if(a->valor == x) {
        LInt novo = (LInt) malloc(sizeof(struct ABin_nodo));
        novo->valor = a->valor;
        novo->prox = NULL;
        return novo;
    }

    LInt resto = NULL;

    if(x < a->valor) {
        resto = caminho(a->esq, x);
    } else {
        resto = caminho(a->dir, x);
    }

    if (resto == NULL && a->valor != x) {
        return NULL; 
    }

    LInt novo = (LInt) malloc(sizeof(struct ABin_nodo));
    novo->valor = a->valor;
    novo->prox = resto;

    return novo;
}

/*
4. Implemente a função void inc(char s[]) que, dada uma uma string s 
com um número em decimal, incrementa esse número numa unidade. 
Assuma que a string tem espaço suficiente para armazenar o número 
resultante. Por exemplo, se a string for "123" deverá ser modificada para 
"124". Se for "199" deverá ser modificada para "200".
*/
#include <string.h>

void inc(char s[]) {
    int len = strlen(s);
    int i = len - 1; // Começa no último dígito (unidades)

    // Percorre de trás para a frente enquanto apanhar '9's
    while (i >= 0 && s[i] == '9') {
        s[i] = '0'; // O '9' vira '0'
        i--;        // Passa para o dígito da esquerda (o "vai um")
    }

    // Se parámos porque encontrámos um dígito entre '0' e '8'
    if (i >= 0) {
        s[i] = s[i] + 1; // Ex: '2' + 1 vira '3'
    } 
    // SE o 'i' chegou a -1, significa que o número era só '9's (ex: "99" virou "00")
    else {
        // Temos de mover todos os caracteres uma casa para a direita
        // para dar espaço ao '1' no início. Inclui o '\0'!
        for (int j = len; j >= 0; j--) {
            s[j + 1] = s[j];
        }
        s[0] = '1'; // Coloca o '1' à frente de tudo (ex: "00" vira "100")
    }
}

/*
5. Implemente a função int sacos(int p[], int N, int C) que, dado 
um array com os pesos de N produtos que se pretende comprar num 
supermercado, e a capacidade C dos sacos desse supermercado,  
determine o número mínimo de sacos necessários para transportar todos 
os produtos. Por exemplo, se os pesos dos produtos forem 
{3,6,2,1,5,7,2,4,1} e C == 10, então bastam 4 sacos. Se os pesos 
forem {3,3,3,3,5,5,11} e C == 11, então bastam 3 sacos. Em geral, 
para descobrir este mínimo teria que testar todas as possíveis maneiras 
de ensacar os produtos. Se não conseguir implementar essa estratégia 
óptima, implemente outra que devolva uma aproximação razoável.
*/
int sacos(int p[], int N, int C) {
    // 1. Ordenar os pesos do maior para o menor (Selection Sort)
    for (int i = 0; i < N - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < N; j++) {
            if (p[j] > p[max_idx]) {
                max_idx = j;
            }
        }
        int temp = p[max_idx];
        p[max_idx] = p[i];
        p[i] = temp;
    }

    // Array para guardar o peso atual de cada saco aberto
    // No pior cenário possível, precisaríamos de N sacos (1 para cada produto)
    int sacos_abertos[N]; 
    int num_sacos = 0; // Quantos sacos já usamos

    // 2. Tentar colocar cada produto num saco
    for (int i = 0; i < N; i++) {
        int colocado = 0;

        // Tenta meter nos sacos que já estão abertos
        for (int j = 0; j < num_sacos; j++) {
            if (sacos_abertos[j] + p[i] <= C) {
                sacos_abertos[j] += p[i]; // Coloca o produto no saco j
                colocado = 1;
                break; // Já está ensacado, passamos ao próximo produto
            }
        }

        // Se não coube em nenhum saco aberto, temos de abrir um novo!
        if (colocado == 0) {
            sacos_abertos[num_sacos] = p[i]; // Primeiro produto do novo saco
            num_sacos++; // Contabiliza o novo saco aberto
        }
    }

    return num_sacos;
}