#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct lint_nodo {
    int valor;
    struct lint_nodo *prox;
} *LInt;

// Inserir no fim da lista
void insert(int x, LInt *l) {
    LInt novo = malloc(sizeof(struct lint_nodo));
    novo->valor = x;
    novo->prox = NULL;

    if (*l == NULL) {
        *l = novo;
        return;
    }

    LInt atual = *l;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = novo;
}

int delete(int n, LInt *l) {
    LInt atual = *l;
    LInt anterior = NULL;

    while(atual != NULL && n > 0) {
        anterior = atual;
        atual = atual->prox;
        n--;
    }

    if (atual == NULL) return 0;

    if(anterior == NULL) {
        *l = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual);
    return 1;
}

// Imprimir lista
void print(LInt l) {
    if (l == NULL) {
        printf("[Lista vazia]\n");
        return;
    }
    while (l != NULL) {
        printf("%d", l->valor);
        if (l->prox != NULL) printf(" -> ");
        l = l->prox;
    }
    printf(" -> NULL\n");
}

int main() {
    LInt l = NULL;

    // Construir lista: 10 -> 20 -> 30 -> 40 -> 50
    insert(10, &l);
    insert(20, &l);
    insert(30, &l);
    insert(40, &l);
    insert(50, &l);

    printf("Lista inicial: ");
    print(l);

    // Apagar o primeiro elemento (n=0)
    printf("\nApagar índice 0 (valor 10):\n");
    int res = delete(0, &l);
    printf("Resultado: %d ", res);
    printf("| Lista atual: ");
    print(l);

    // Apagar elemento do meio (n=1, valor 30)
    printf("\nApagar índice 1 (valor 30):\n");
    res = delete(1, &l);
    printf("Resultado: %d ", res);
    printf("| Lista atual: ");
    print(l);

    // Apagar o último elemento (n=2, valor 50)
    printf("\nApagar índice 2 (valor 50):\n");
    res = delete(2, &l);
    printf("Resultado: %d ", res);
    printf("| Lista atual: ");
    print(l);

    // Tentar apagar índice negativo
    printf("\nApagar índice -1 (inválido):\n");
    res = delete(-1, &l);
    printf("Resultado: %d ", res);
    printf("| Lista atual: ");
    print(l);

    return 0;
}