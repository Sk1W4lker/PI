#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
1. Implemente uma função int pesquisa(int x, int a[], int N) que, 
dado um array a ordenado de tamanho N, calcula em que índice desse array 
se encontra o elemento x. Se x não estiver no array deve devolver -1. Será 
valorizada a eficiência da função.
*/

int pesquisa(int x, int a[], int N) {

    for(int i = 0; i < N; i++) {
        if(a[i] == x) {
            return i;
        } 
    }
    return -1;
}

/*
2. Implemente de forma iterativa uma função void duplicaTodos(LInt l)
que duplica todos os elementos de uma lista. Se a lista tiver os valores [1,2,3]
deverá ficar com os valores [1,1,2,2,3,3].
*/

typedef struct lint_nodo {
    int valor;
    struct lint_nodo *prox;
} *LInt;

void duplicaTodos(LInt l) { 
    LInt atual = l;

    while(atual != NULL) {
        LInt novo = (LInt) malloc(sizeof(struct lint_nodo));
        novo->valor = atual->valor; // O novo nó recebe o valor 1
        // 1. O novo aponta para onde o atual apontava (o nó 2)
        novo->prox = atual->prox;   // novo->prox passa a ser o nó 2
        // 2. O atual deixa de apontar para o 2 e passa a apontar para o novo
        atual->prox = novo;         // atual->prox passa a ser o nó novo (o segundo 1)
        // 3. O atual avança para o nó 2 (que guardámos em novo->prox)
        atual = novo->prox;         // atual passa a ser o nó 2
    }
}

/*
 3. Implemente uma função int expande(char s[]) que, dada uma string 
num formato compacto onde cada caracter é seguido de um dígito, expande 
essa string repetindo cada caracter o número de vezes indicado pelo dígito 
que o segue. A função deve devolver o tamanho da string expandida. Por 
exemplo, dada a string "x3y1z4" a função deve expandi-la para "xxxyzzzz". 
Assuma que a string s tem espaço suficiente para armazenar a string 
expandida. 
*/
#include <string.h>

int expande(char s[]) {
    int len_original = strlen(s);
    int tam_final = 0;

    // 1. Descobrir o tamanho final da string expandida
    // Saltamos de 2 em 2 porque os dígitos estão nas posições ímpares (1, 3, 5...)
    for (int i = 1; i < len_original; i += 2) {
        int repeticoes = s[i] - '0'; // Transforma o caractere (ex: '3') num número (3)
        tam_final += repeticoes;
    }

    // Definimos os nossos dois ponteiros para a fase de escrita
    int escreve = tam_final;      // Onde vamos escrever (começa no fim da nova string)
    int le = len_original - 1;    // De onde vamos ler (começa no fim da string antiga)

    // Colocamos já o terminador de string no novo final correto
    s[escreve] = '\0';
    escreve--;

    // 2. Expandir de trás para a frente
    while (le >= 0) {
        int repeticoes = s[le] - '0'; // Lemos o dígito (ex: 4)
        le--;                         // Recuamos para o caractere correspondente (ex: 'z')
        char caractere = s[le];
        le--;                         // Recuamos para o próximo dígito para a próxima volta

        // Escrevemos o caractere o número de vezes indicado pelo dígito
        for (int j = 0; j < repeticoes; j++) {
            s[escreve] = caractere;
            escreve--;
        }
    }

    return tam_final;
}

/* 
5. Defina uma função int todosIguais(ABin a, int n) que testa se 
todos os valores no nível n de uma árvore são iguais (se não houver nenhum 
nodo a esse nível a função deve retornar verdadeiro). Serão valorizadas 
soluções que percorrem poucas vezes a árvore. 
*/
int todosIguaisAux(ABin a, int n, int *primeiro_valor) {
    // Se a árvore está vazia, não há nós para falharem o teste.
    // O enunciado diz: "se não houver nenhum nodo a esse nível retorna verdadeiro (1)"
    if (a == NULL) {
        return 1;
    }

    // SE CHEGÁMOS AO NÍVEL N!
    if (n == 0) {
        // Se for o PRIMEIRO nó que encontramos neste nível
        if (*primeiro_valor == -1) {
            *primeiro_valor = a->valor; // Guardamos o valor dele como padrão
            return 1;
        } 
        // Se já não for o primeiro, comparamos com o padrão
        else {
            return (a->valor == *primeiro_valor);
        }
    }

    // SE AINDA NÃO CHEGÁMOS AO NÍVEL N, continuamos a descer (n - 1)
    // Primeiro tentamos o lado esquerdo
    int esq_ok = todosIguaisAux(a->esq, n - 1, primeiro_valor);
    
    // Se a esquerda já falhou (devolveu 0), não vale a pena perder tempo na direita!
    // Isto cumpre o requisito de "percorrer poucas vezes a árvore" (Short-circuit)
    if (!esq_ok) return 0;

    // Se a esquerda passou, vamos testar a direita
    return todosIguaisAux(a->dir, n - 1, primeiro_valor);
}

// A função oficial que o teu professor pediu
int todosIguais(ABin a, int n) {
    int referencia = -1; // -1 vai significar "ainda não encontrámos ninguém no nível n"
    return todosIguaisAux(a, n, &referencia);
}