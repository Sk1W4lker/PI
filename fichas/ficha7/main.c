#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"

void libertaLista (Palavras l){
    Palavras temp = NULL;

    while(l != NULL) {
        temp = l->prox;

        if(l->palavra != NULL) {
            free(l);
        }

        l = temp;
    }
}

// calcula quantas palavras (diferentes) existem armazenadas.
int quantasP (Palavras l){
    int count = 0;

    while(l != NULL) {
        count++;
        l = l->prox;
    }

    return count;
}

//escreve no ecran, uma por linha, todas as palavras armazenadas, bem como o n ́umero de ocorrˆencias.
void listaPal (Palavras l){
    while(l != NULL) {
        printf("%s %d", l->palavra, l->ocorr);
        l = l->prox;
    }
}
//determina qual a  ́ultima palavra da lista.
char *ultima (Palavras l){
    if(l == NULL) return NULL;

    while(l->prox != NULL) {
        l = l->prox;
    }

    return (l->palavra);
}

Palavras acrescentaInicio (Palavras l, char *p){
    Palavras nova = (Palavras) malloc(sizeof(struct celula));

    if(nova == NULL) {
        return l;
    }

    nova->palavra = strdup(p);
    nova->ocorr = 1;

    nova->prox = l;

    return nova;
}

Palavras acrescentaFim (Palavras l, char *p){
    Palavras nova = (Palavras) malloc(sizeof(struct celula));
    if(nova == NULL) return l;

    nova->palavra = strdup(p);
    nova->ocorr = 1;
    nova->prox = NULL;
    
    if(l == NULL) return nova;

    Palavras atual = l;
    while(atual->prox != NULL) {
        atual = atual->prox;
    }
    
    atual->prox = nova;
    return l;
}

Palavras acrescenta (Palavras l, char *p) {
    Palavras atual = l;

    // 1. Procurar se a palavra já existe na lista
    while (atual != NULL) {
        if (strcmp(atual->palavra, p) == 0) {
            atual->ocorr++; // Encontrou! Incrementa o contador
            return l;       // Devolve a lista sem criar nós novos
        }
        atual = atual->prox;
    }

    // 2. Se chegou aqui, a palavra NÃO existe (ou a lista estava vazia)
    Palavras nova = (Palavras) malloc(sizeof(struct celula));
    if (nova == NULL) return l; // Segurança de memória

    nova->palavra = strdup(p);
    nova->ocorr = 1;
    
    // Inserimos no início: o próximo do 'nova' é a cabeça antiga (l)
    nova->prox = l; 

    // ATENÇÃO: Agora 'nova' é o primeiro elemento da lista,
    // por isso temos de retornar este novo ponteiro!
    return nova; 
}

struct celula * maisFreq (Palavras l){
    struct celula *mais = l;
    Palavras atual = l->prox;

    while(atual != NULL) {
    if(atual->ocorr > mais->ocorr) {
        mais = atual;
        }
    atual = atual->prox;
    }
    return mais;
}

int main () {
    Palavras dic = NULL;

    char * canto1 [44] = {"as", "armas", "e", "os", "baroes", "assinalados",
                          "que", "da", "ocidental", "praia", "lusitana", 
                          "por", "mares", "nunca", "de", "antes", "navegados",
                          "passaram", "ainda", "alem", "da", "taprobana",
                          "em", "perigos", "e", "guerras", "esforcados",
                          "mais", "do", "que", "prometia", "a", "forca", "humana",
                          "e", "entre", "gente", "remota", "edificaram", 
                          "novo", "reino", "que", "tanto", "sublimaram"};

    printf ("\n_____________ Testes _____________\n\n");

    int i; struct celula *p;
    for (i=0;i<44;i++)
        dic = acrescentaFim (dic, canto1[i]);

    printf ("Foram inseridas %d palavras\n", quantasP (dic));
    printf ("palavras existentes:\n");
    listaPal (dic);
    printf ("última palavra inserida: %s\n", ultima (dic));

    libertaLista (dic);

    dic = NULL;

    srand(42);
    
    for (i=0; i<1000; i++)
        dic = acrescenta (dic, canto1 [rand() % 44]);
    
    printf ("Foram inseridas %d palavras\n", quantasP (dic));
    printf ("palavras existentes:\n");
    listaPal (dic);
    printf ("última palavra inserida: %s\n", ultima (dic));
    
    p = maisFreq (dic);
    //printf ("Palavra mais frequente: %s (%d)\n", p->palavra, p->ocorr);
    
    printf ("\n_________ Fim dos testes _________\n\n");

    return 0;
}

