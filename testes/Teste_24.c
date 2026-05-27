#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*1. Adapte a função fizzbuzz definida abaixo por forma a devolver quantos
números são impressos entre a primeira linha do tipo FizzBuzz e a primeira
linha do tipo Buzz que se lhe segue? Se não aparecer nenhuma linha do tipo
Buzz depois de uma linha do tipo FizzBuzz deve devolver -1.
*/

//int fizz(int n) {...}
//int buzz(int n) {...}
int fizzbuzz(int n) {
    int filtro = 0; // 0 = Ainda não viu FizzBuzz, 1 = Já viu o primeiro FizzBuzz
    int streak = 0; // Contador de linhas impressas intermédias

    for (int i = 0; i < n; i++) {
        
        // Caso 1: Linha FizzBuzz (Agora tratada como linha normal se o filtro já estiver ativo)
        if (fizz(i) && buzz(i)) {
            printf("FizzBuzz\n");
            
            if (filtro == 1) {
                streak++; // AGORA CONTA: se já vimos um FizzBuzz antes, este acumula na streak
            } else {
                filtro = 1; // Ativa o filtro no primeiríssimo FizzBuzz
            }
        } 
        // Caso 2: Linha Fizz
        else if (fizz(i)) {
            printf("Fizz\n");
            if (filtro == 1) streak++;
        } 
        // Caso 3: Linha Buzz (O único fim da linha real!)
        else if (buzz(i)) {
            printf("Buzz\n");
            
            if (filtro == 1) {
                return streak; // Só sai do programa aqui, quando imprime "Buzz"
            }
        } 
        // Caso 4: Linha com o número normal
        else {
            printf("%d\n", i);
            if (filtro == 1) streak++;
        }
    }

    // Se o ciclo acabou e nunca apareceu o "Buzz" para fechar
    if (filtro == 1) {
        return -1;
    }

    return 0; 
}

/*
2. Implemente a função void rodaEsq(int a[], int N, int r) por forma
a rodar os elementos de um array com N inteiros r posições para a esquerda
(assuma que r < N). Por exemplo, se o array tiver o conteúdo
{1,2,3,4,5,6} e se r == 2 então o array deverá ficar com os valores
{3,4,5,6,1,2}. Tente minimizar o número de escritas no array.
*/
void rodaEsq(int a[], int N, int r) {
    int temp[r];

    for(int i = 0; i < r; i++) {
        temp[i] = a[i];
    }

    for(int i = 0; i < N-r; i++) {
        a[i] = a[i+r];
    }

    for(int i = 0; i < r; i++) {
        a[N-r+i] = temp[i];
    }
}

/*
3. Implemente de forma iterativa a função int delete(int n, LInt *l)
que apaga o n-ésimo elemento de uma lista ligada (para n == 0 a função
deverá remover o primeiro elemento). Se tal não for possível a função deverá
devolver um código de erro.
*/
typedef struct lint_nodo {
    int valor;
    struct lint_nodo *prox;
} *LInt;

int delete(int n, LInt *l) {
    LInt atual = *l;
    LInt anterior = NULL;

    while(n > 0 && atual != NULL) {
        anterior = atual;
        atual = atual->prox;
        n--;
    }

    if(atual == NULL) return 0;

    if(anterior == NULL) {
        *l = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual);
    return 1;
}

/*
4. Defina uma função int maxCresc(LInt l) que calcula o comprimento da
maior sequência crescente de elementos consecutivos numa lista. Por
exemplo, se a lista for [ 1, 2, 3, 2, 1, 4, 10, 12, 5, 4], a função deverá retornar
4. Serão desvalorizadas soluções que consultem cada nodo da lista mais do
que uma vez.
*/
int maxCresc(LInt l) {
    // AJUSTE 1: Segurança contra listas vazias
    if (l == NULL) return 0;

    int atual;
    int count = 1;
    int max = 1;

    atual = l->valor;
    l = l->prox; // AJUSTE 4: Adicionado o ';' que faltava

    while(l != NULL) {
        // AJUSTE 2: Mudado o sinal para verificar se o próximo é MAIOR
        if(l->valor > atual) {
            count++;
        } else {
            // A sequência quebrou! Guardamos o recorde se for o caso
            if(count > max) {
                max = count;
            }
            // AJUSTE 3: Fazemos o reset do contador para 1 (o elemento atual)
            count = 1;
        }
        
        atual = l->valor;
        l = l->prox;
    }
    
    // Esta tua verificação final está perfeita! 
    // Garante que se a maior sequência for até ao último nó, ela é contabilizada.
    if(count > max) {
        max = count;
    }

    return max;
}

/*
5. Implemente uma função ABin folhaEsq(ABin a) que devolve a folha
mais à esquerda de uma árvore (ou NULL se não tem nenhuma folha). Uma
folha é um nodo em que ambas as sub-árvores são vazias.
*/

typedef struct abin_nodo {
    int valor;
    struct abin_nodo *esq, *dir;
} *ABin;

ABin folhaEsq(ABin a) {

    while(a->esq != NULL || a->dir != NULL) {
        if(a->esq != NULL) {
            a = a->esq;
        } else {
            a = a->dir;
        }
    }
    return a;
}

/*
6. Defina uma função int parentesisOk(char exp[]) que, dada uma
string onde está armazenada uma expressão aritmética com vários tipos de
parêntesis, testa se os parêntesis estão corretos. Por exemplo, se a
expressão for "3 + [2 - (3 - x)] + 4" a função deve retornar verdadeiro,
enquanto que para a expressão "3 + [2 - (3 - x]) + 4" deve retornar
falso. Considere 3 tipos de parêntesis: '(',')','[',']', e '{','}'
*/
int parentesisOk(char exp[]) {
    char pilha[1000];
    int topo = 0;

    for(int i = 0; exp[i] != '\0'; i++) {
        // Se for abertura, empilha
        if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
            pilha[topo] = exp[i];
            topo++;
        } 
        // Se for fecho, valida com o topo da pilha
        else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {

            if(topo == 0) return 0; // Tentou fechar sem nada aberto -> Erro!

            char ultimo = pilha[topo - 1];

            // Compara se o fecho condiz com a abertura correta (usando ==)
            if((exp[i] == ')' && ultimo == '(') ||
               (exp[i] == ']' && ultimo == '[') || 
               (exp[i] == '}' && ultimo == '{')) {
                topo--; // Par correto! Desempilha
            } else {
                return 0; // Par errado ou cruzado -> Erro!
            }
        }
    }
    
    // Se a pilha terminar vazia, está tudo bem
    return (topo == 0); 
}