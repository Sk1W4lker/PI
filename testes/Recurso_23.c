#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
1. Implemente a função int isFib(int x) que testa se um número x 
pertence à sequência de Fibonacci (0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 
144, ...).  
*/
int isFib(int x) {
    if(x < 0) return 0;

    if(x == 0 || x == 1) return 1;

    int a = 0; // Primeiro termo
    int b = 1; // Segundo termo
    int proximo = a + b; // Terceiro termo (1)

    while(proximo > x) {
        a = b;
        b = proximo;
        proximo = a+b;
    }

    if(x == proximo){
        return 1;
    } else {
        return 0;
    }
}

/*
2. Implemente a função int moda(Aluno turma[], int N) que, dado um 
array com a informação de N alunos, calcula a nota final mais frequente. 
Se houver mais do que uma nota final com a frequência máxima, devolva 
uma delas. Se a nota final mais frequente for “Reprovado” então deve 
devolver 0. O teste vale 80% da nota final e os mini-testes 20%. 
*/
typedef struct { 
    float teste, minis; 
} Aluno; 

int moda(Aluno turma[], int N) {
    int max_frequencia = 0;
    int nota_moda = 0;

    for(int i = 0; i < N; i++) {
        int nota_atual = (int)(turma[i].teste * (0.8) + turma[i].minis * (0.2));
        if (nota_atual < 10) nota_atual = 0;

        int count = 0;

        for (int j = 0; j < N; j++) {
            int outra_nota = (int)(turma[i].teste * (0.8) + turma[i].minis * (0.2));
            if(outra_nota < 10) outra_nota = 0;

            if(nota_atual == outra_nota) count++;
        } 
        // Se esta nota apareceu mais vezes do que a maior que tínhamos visto, atualizamos
        if (count > max_frequencia) {
            max_frequencia = count;
            nota_moda = nota_atual;
        }
    }
    return nota_moda;
}

/*
3. Apresente uma definição iterativa da função int take(int n, LInt *l) 
que, dado um inteiro n e uma lista ligada de inteiros l, apaga de l todos os 
nodos para além do n-ésimo (libertando o respectivo espaço). Se a lista 
tiver n ou menos nodos, a função não altera a lista. A função deve 
devolver o número de nodos apagados. 
*/
typedef struct lint_nodo { 
    int valor; 
    struct lint_nodo *prox; 
} *LInt; 

#include <stdlib.h>

int take(int n, LInt *l) {
    // Caso Base 1: Se o n for 0, significa que não queremos nenhum elemento.
    // Apagamos a lista toda e a nova lista passa a ser NULL.
    if (n <= 0) {
        int apagados = 0;
        LInt atual = *l;
        while (atual != NULL) {
            LInt aux = atual->prox;
            free(atual);
            atual = aux;
            apagados++;
        }
        *l = NULL; // A lista agora ficou vazia
        return apagados;
    }

    LInt atual = *l;

    // 1. Caminhar até ao n-ésimo nó (ou até a lista acabar)
    // Começamos em n > 1 porque queremos parar EXATAMENTE em cima do n-ésimo nó
    while (atual != NULL && n > 1) {
        atual = atual->prox;
        n--;
    }

    // Se o ciclo acabou e a lista terminou antes do tempo (ou mesmo no fim),
    // significa que a lista tinha n ou menos nós. Não há nada para apagar!
    if (atual == NULL || atual->prox == NULL) {
        return 0;
    }

    // 2. O Corte de Giz
    LInt resto = atual->prox; // 'resto' aponta para o início do lixo que vamos apagar
    atual->prox = NULL;      // Cortamos a ligação! O n-ésimo nó passa a ser o FIM da lista

    // 3. Limpar o lixo da memória RAM e contar
    int apagados = 0;
    while (resto != NULL) {
        LInt aux = resto->prox; // Guarda o próximo antes de destruir o atual (regra de ouro!)
        free(resto);
        resto = aux;
        apagados++;
    }

    return apagados;
}

/*
4. Apresente uma definição da função int verifica(char frase[], int 
k) que testa se todas as palavras que ocorrem numa frase têm pelo 
menos k caracteres.
*/
int verifica(char frase[], int k) {
    int i = 0;
    int tamanho_palavra = 0;

    // Percorre a string até ao fim
    while (frase[i] != '\0') { 
        // Se NÃO for um espaço (ou tabulador/quebra de linha), estamos dentro de uma palavra
        if (frase[i] != ' ' && frase[i] != '\t' && frase[i] != '\n') {
            tamanho_palavra++; 
        } else { // Se for um separador, significa que uma palavra pode ter acabado aqui
            // Só validamos se o tamanho_palavra for maior que 0 (evita contar espaços seguidos)
            if (tamanho_palavra > 0) {
                if (tamanho_palavra < k) {
                    return 0; // Encontrámos uma palavra curta demais! Aborta e dá falso.
                }
                tamanho_palavra = 0; // Faz reset para a próxima palavra
            }
        }
        i++;
    }
    // Temos de fazer uma última validação para a palavra que ficou pendente no fim da string.
    if (tamanho_palavra > 0 && tamanho_palavra < k) {
        return 0;
    }

    // Se o programa percorreu a frase toda e nunca fez 'return 0', então todas são válidas!
    return 1;
}

/*
Implemente a função ABin reconstroi(char s[]) que dada uma string 
com uma string com uma travessia pré-order de uma árvore de dígitos, 
onde os apontadores nulos aparecem marcados com um '*', reconstrói a 
árvore original. Por exemplo, se a string for "34**52**5*6**" deverá ser 
devolvida a seguinte árvore. 
*/

typedef struct abin_nodo { 
    int valor; 
    struct abin_nodo *esq, *dir; 
} *ABin;

ABin reconstroi(char s[]) {

    if(s[0] == '\0') {
        return NULL;
    }

    char c = s[0];

    int i = 0;
    
    while(s[i] != '\0') {
        // Vamos puxar todas as letras uma posição para a esquerda.
        s[i] = s[i+1];
        i++;
    }

    if(c == "*") return NULL;

    ABin nova = malloc(sizeof(struct ABin_nodo));
    nova->valor = c - '0'; //Transforma letra em número.
    nova->esq = reconstroi(s);
    nova->dir = reconstroi(s);

    return nova;
}