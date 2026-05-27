#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*1. Um conjunto de inteiros pode ser representado como uma união de
intervalos. Por exemplo, o conjunto {1,2,3,4,5,6,10,11} pode ser representado
pela união dos intervalos [1..6] e [10..11], ou pela união dos intervalos [2..4],
[1..5], [10..11] e [4..6]. Implemente a função void ordena(Intervalo c[],
int N) que dado um conjunto c com N intervalos guardados num array,
ordena os respectivos intervalos pelo limite inferior. O tipo Intervalo está
declarado da seguinte forma.*/

typedef struct {
    int inf,sup;
} Intervalo;

void ordena(Intervalo c[], int N) {
    int min;
    Intervalo temp;

    for(int i = 0; i < N - 1; i++) {
        min = i;
        
        for(int j = i + 1; j < N; j++) {
            // AJUSTE 2: Mudado para '<' para ser mais eficiente
            if(c[j].inf < c[min].inf){
                min = j; 
            }
        }
        
        // AJUSTE 1: Corrigido de 'Min' para 'min' (minúsculo)
        if(min != i) {
            temp = c[i];
            c[i] = c[min];
            c[min] = temp;
        } 
    }
}

/*
2. Implemente a função int cardinalidade(Intervalo c[], int N), que
dado um conjunto c com N intervalos guardados num array e já ordenados de
forma crescente pelo limite inferior, devolve quantos inteiros estão contidos
nesse conjunto. No caso do conjunto ilustrado na questão anterior, a função
deve devolver 8
*/

int cardinalidade(Intervalo c[], int N) {
    if(N <= 0) return 0;
    int i;
    int count;
    int inicio = c[0].inf;
    int fim = c[0].sup;

    for(i=1;i<N;i++) {
        if(c[i].inf <= fim) {
            if(c[i].sup > fim) {
                fim = c[i].sup;
            }
        } else {
            count += (fim - inicio + 1);
            inicio = c[i].inf;
            fim = c[i].sup;
        }
    }
    count += (fim - inicio + 1);
}

/*
3. As duas convenções mais típicas para dar nomes a funções são
conhecidas por camel case e snake case. No camel case as várias palavras
de um identificador aparecem juntas, sendo que a primeira de cada palavra
(exceto na primeira) é escrita em maiúscula. No snake case os identificadores
são escritos sempre em minúsculas sendo as diferentes palavras separadas
pelo caracter '_'. Por exemplo, o identificador "apagaTodosMenores" está
escrito na convenção camel case e o identificador "apaga_todos_menores"
em snake case. Implemente a função void camel2snake(char *id), que
dada uma string com um identificador na convenção camel case o converte
para convenção snake case. Assuma que a string tem espaço para o
identificador resultante. Note que para converter um caracter de maiúscula
para minúscula basta somar-lhe 32.
*/


/*
3. As duas convenções mais típicas para dar nomes a funções são
conhecidas por camel case e snake case. No camel case as várias palavras
de um identificador aparecem juntas, sendo que a primeira de cada palavra
(exceto na primeira) é escrita em maiúscula. No snake case os identificadores
são escritos sempre em minúsculas sendo as diferentes palavras separadas
pelo caracter '_'. Por exemplo, o identificador "apagaTodosMenores" está
escrito na convenção camel case e o identificador "apaga_todos_menores"
em snake case. Implemente a função void camel2snake(char *id), que
dada uma string com um identificador na convenção camel case o converte
para convenção snake case. Assuma que a string tem espaço para o
identificador resultante. Note que para converter um caracter de maiúscula
para minúscula basta somar-lhe 32.
*/

void camel2snake(char *id) {
    char aux[200];
    int i = 0, j = 0; 

    while(id[i] != '\0') {
        if(id[i] >= 'A' && id[i] <= 'Z') {
            aux[j] = '_';      
            j++;               // Avança para a posição da letra
            aux[j] = id[i] + 32; // Guarda a letra convertida em minúscula
            j++;               // Avança para preparar o próximo caractere
        } else {
            aux[j] = id[i];    // Guarda a letra minúscula normal
            j++;               // Avança para preparar o próximo caractere
        }
        i++; // O 'i' avança sempre uma posição da string original
    }
    
    aux[j] = '\0'; // Fecha a string auxiliar corretamente
    strcpy(id, aux); // Copia o resultado final de volta para o ponteiro original
}

/*
4. Defina a função LInt arrayToList (int v[], int N) que constroi
uma lista com os elementos de um array, pela mesma ordem em que
aparecem no array. O tipo LInt está declarado da seguinte forma.
*/

typedef struct no {
    int valor;
    struct no *prox;
} *LInt;

LInt arrayToList (int v[], int N) {
    LInt lista = NULL;
    int i;

    for(i = N-1; i >= 0; N--) {
        LInt nova = (LInt) malloc(sizeof(struct no));
        nova->valor = v[i];
        nova->prox = lista;
        lista = nova;
    }
    return lista;
}

/*
5. Implemente a função int apagaUltimo(LInt *l, int x) que dada uma
lista não ordenada apaga a última ocorrência do número x. Se o número não
existir na lista deve devolver um código de erro
*/
int apagaUltimo(LInt *l, int x) {
    LInt anterior = NULL;
    LInt atual = *l; 

    LInt ant_alvo = NULL;
    LInt alvo = NULL;

    // Se a lista estiver vazia, retorna código de erro (0)
    if(*l == NULL) return 0;

    // Percorre a lista toda para encontrar a ÚLTIMA ocorrência
    while(atual != NULL) {
        if(x == atual->valor) {
            ant_alvo = anterior; // Memoriza o pai do último alvo visto
            alvo = atual;        // Memoriza o próprio último alvo visto
        }
        anterior = atual;
        atual = atual->prox;
    }
    
    // Se o ciclo acabou e o 'alvo' continua NULL, o número x não existe na lista
    if(alvo == NULL) return 0;

    // CORREÇÃO: Mudado de = para == 
    // Se o ant_alvo for NULL, significa que o alvo é o primeiríssimo nó da lista
    if(ant_alvo == NULL) {
        *l = alvo->prox;
    } else {
        ant_alvo->prox = alvo->prox; // Salta o nó alvo, ligando o anterior ao próximo
    }
    
    free(alvo); // Liberta a memória do nó apagado
    return 1;   // Sucesso!
}

/*
6. Implemente a função int parentesco(ABin a, int x, int y) que
dada uma árvore binária de procura (sem números repetidos) e dois números
que pertencem à árvore calcula o grau de parentesco entre eles (a distância
entre eles na árvore). Por exemplo, na árvore ilustrada abaixo, o grau de
parentesco entre 1 e 8 é 3. O tipo
ABin está declarado da seguinte
forma.
*/

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;

// A tua função auxiliar - IMPECÁVEL!
int distancia(ABin a, int x) {
    int passos = 0;
    while(a != NULL && a->valor != x) {
        if(x < a->valor) {
            a = a->esq;
            passos++;
        } else {
            a = a->dir;
            passos++;
        }
    }
    return passos;
}

int parentesco(ABin a, int x, int y) {
    if (a == NULL) return 0;

    while(a != NULL) {
        if(x < a->valor && y < a->valor) {
            a = a->esq;
        } 
        // Se AMBOS são maiores que o atual, o caminho de ambos vai para a direita
        else if (x > a->valor && y > a->valor) {
            a = a->dir;
        } 
        // Se se separarem (um para cada lado) ou se encontrámos um deles, este é o ancestral comum!
        else {
            break;
        }
    }
    
    // O 'a' agora é o ancestral comum mais próximo. 
    // Somamos a distância dele até x com a distância dele até y.
    return distancia(a, x) + distancia(a, y);
}

