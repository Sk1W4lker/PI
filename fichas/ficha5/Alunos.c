#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Alunos.h"

void dumpV (int v[], int N){
    int i;
    for (i=0; i<N; i++) printf ("%d ", v[i]);
}

void imprimeAluno (Aluno *a){
    int i;
    printf ("%-5d %s (%d", a->numero, a->nome, a->miniT[0]);
    for(i=1; i<6; i++) printf (", %d", a->miniT[i]);
    printf (") %5.2f %d\n", a->teste, nota(*a));
}

//1
int nota (Aluno a){
    int sum = 0;
    
    // Usa ponto (.) porque 'a' é uma struct, não um ponteiro
    for(int i = 0; i < 6; i++) {
        sum += a.miniT[i]; 
    }

    // Usa ponto aqui também e cuidado com a vírgula (usa ponto 0.8)
    float j = (a.teste * 0.8) + ((sum + 8) * 0.2);
    
    return (int)j; 
}

//2
int procuraNum (int num, Aluno t[], int N){
    for(int i = 0; i < N; i++) {
        if(t[i].numero == num) return i;
    }

    return -1;
}

//3
void ordenaPorNum(Aluno t[], int N) {
    int i, j;
    Aluno temp; // Variável temporária para a troca

    for (i = 0; i < N - 1; i++) {
        for (j = i + 1; j < N; j++) {
            // Se o número do aluno na posição i for maior que o da posição j
            if (t[i].numero > t[j].numero) {
                // Troca as posições (o tal "Swap")
                temp = t[i];
                t[i] = t[j];
                t[j] = temp;
            }
        }
    }
}

//4
void criaIndPorNum (Aluno t[], int N, int ind[]) {
    int i, j, tempInd;

    // 1. Inicializar o array de índices: {0, 1, 2, ..., N-1}
    for (i = 0; i < N; i++) {
        ind[i] = i;
    }

    // 2. Ordenar o array de ÍNDICES baseado nos números dos alunos em t
    for (i = 0; i < N - 1; i++) {
        for (j = i + 1; j < N; j++) {
            // Comparamos os alunos nas posições apontadas por ind[i] e ind[j]
            if (t[ind[i]].numero > t[ind[j]].numero) {
                
                // TROCAMOS APENAS OS ÍNDICES (inteiros)
                tempInd = ind[i];
                ind[i] = ind[j];
                ind[j] = tempInd;
            }
        }
    }
}

//5
void imprimeTurmaInd(int ind[], Aluno t[], int N) {
    for (int i = 0; i < N; i++) {
        //imprimeAluno(t + ind[i]);// Anda t posições pra frente Exemplo t + 3
        imprimeAluno(&t[ind[i]]);
    }
}

//6
int procuraInd (int num, Aluno t[], int N, int ind[]) {
    int esquerda = 0;
    int direita = N - 1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        
        // ACESSO INDIRETO: usamos o ind[meio] para chegar ao aluno em t
        if (t[ind[meio]].numero == num) {
            return ind[meio]; // Encontrou! Retorna o índice real do aluno em t
        }
        
        if (t[ind[meio]].numero < num) {
            esquerda = meio + 1; // Procura na direita
        } else {
            direita = meio - 1;  // Procura na esquerda
        }
    }

    return -1; // Não encontrou
}

//7
void criaIndPorNome (Aluno t[], int N, int ind[]) {
    int i, j, temp;

    // 1. Inicializar o array de índices {0, 1, 2, ..., N-1}
    for (i = 0; i < N; i++) {
        ind[i] = i;
    }

    // 2. Ordenar o array de índices baseado no NOME
    for (i = 0; i < N - 1; i++) {
        for (j = i + 1; j < N; j++) {
            
            // Comparamos as strings: se strcmp der > 0, o nome em i é "maior" que em j
            if (strcmp(t[ind[i]].nome, t[ind[j]].nome) > 0) {
                
                // Troca os índices
                temp = ind[i];
                ind[i] = ind[j];
                ind[j] = temp;
            }
        }
    }
}