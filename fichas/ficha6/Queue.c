#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

// Static queues 
/*
q->length é a quantidade de elementos atualmente na fila.
q->front é o índice de onde está o primeiro elemento.
q->values[Max] número de valores.
*/


//inicializa uma queue (passa a representar uma queue vazia)
void SinitQueue (SQueue q){
	if(q != NULL) {
		q->front = 0;
		q->length = 0;
	}
}

//testa se uma queue  ́e vazia
int  SisEmptyQ (SQueue q){
    if(q != NULL) {
		if(q->length == Max) {
			return 1;
		}
	}
	return 0;
}

/*
acrescenta x ao fim de q; a fun ̧c ̃ao deve retornar
0 se a opera ̧c ̃ao fˆor feita com sucesso (i.e., se a queue ainda n ̃ao estiver cheia) e 1 se a
opera ̧c ̃ao n ̃ao fˆor poss ́ıvel (i.e., se a queue estiver cheia).
*/
int  Senqueue (SQueue q, int x){
	if(q->length == q->front) {
		return 1;
	}
	int posicao_final = (q->front + q->length) % Max; //Calcular a próxima posição livre (o fim da fila) de forma circular

	q->values[posicao_final] = x;
	q->length++;
	return 0;
}

/*
remove de uma queue o elemento que est ́a no
in ́ıcio. A fun ̧c ̃ao dever ́a colocar no endere ̧co x o elemento removido. A fun ̧c ̃ao dever ́a
retornar 0 se a opera ̧c ̃ao for poss ́ıvel (i.e. a queue n ̃ao est ́a vazia) e 1 em caso de erro
(queue vazia) */
int  Sdequeue (SQueue q, int *x) {
	
	if(q->length == Max) {
		return 1;
	}

	*x = q->values[q->front];
	q->front = (q->front + 1) % Max;
	q->length--;
	return 0;
}

/*coloca no endere ̧co x o elemento que est ́a no in ́ıcio
da queue (sem modificar a queue). A fun ̧c ̃ao dever ́a retornar 0 se a opera ̧c ̃ao for poss ́ıvel
(i.e. a queue n ̃ao est ́a vazia) e 1 em caso de erro (queue vazia).*/
int  Sfront (SQueue q, int *x) {
	
	if(q != NULL) {
		if(q->length == Max) {
			return 1;
		}
		*x = q->values[q->front];
	}
	return 0;
}

void ShowSQueue (SQueue q){
    int i, p;
    printf ("%d Items: ", q->length);
    for (i=0, p=q->front; i<q->length; i++) {
        printf ("%d ", q->values[p]);
        p = (p+1)%Max;
    }
    putchar ('\n');
}

// Queues with dynamic arrays

int dupQueue (DQueue q) {
}

void DinitQueue (DQueue q) {
	if(q != NULL) {
		q->front = 0;
		q->length = 0;
		q->size = Max;
		q->values = (int *) malloc(q->size * sizeof(int));
	};
}

int  DisEmptyQ (DQueue s) {
	if(s != NULL) {
		if(s->length == 0) {
			return 1;
		}
	}
	return 0;
}
/*
Acrescenta x ao fim de uma dinQueue.
Se estiver cheia, duplica o tamanho do array realocando os elementos.
Retorna 0 em caso de sucesso e 1 se faltar memória no sistema.
*/
int Denqueue (DQueue q, int x) {
    if (q == NULL) return 1;

    // 1. VERIFICAR SE A QUEUE ESTÁ CHEIA
    if (q->length == q->size) {
        int novo_tamanho = q->size * 2;
        
        // Alocar um array totalmente novo com o dobro da capacidade
        int *novo_array = (int *) malloc(novo_tamanho * sizeof(int));
        if (novo_array == NULL) {
            return 1; // Erro: Falha de memória do sistema
        }

        // Copiar os elementos da fila antiga para o início do novo array
        // Começamos no 'front' antigo e vamos copiando por ordem FIFO
        for (int i = 0; i < q->length; i++) {
            int indice_antigo = (q->front + i) % q->size;
            novo_array[i] = q->values[indice_antigo];
        }

        // Libertar a memória do array antigo que já não precisamos
        free(q->values); // (ou q->values, dependendo de como chamaste)
        q->values = novo_array;

        // Como reorganizámos os elementos a começar do zero:
        q->front = 0; 
        q->size = novo_tamanho;
    }

    // 2. INSERIR O ELEMENTO (Agora garantidamente há espaço)
    int posicao_final = (q->front + q->length) % q->size;
    q->values[posicao_final] = x;
    q->length++;

    return 0; // Sucesso!
}

/*
Remove de uma dinQueue o elemento que está no início.
A função deverá colocar no endereço x o elemento removido.
A função deverá retornar 0 se a operação for possível (queue não vazia) 
e 1 em caso de erro (queue vazia ou inválida).
*/
int Ddequeue (DQueue q, int *x) {
    // 1. Validar se a estrutura existe e se não está vazia
    if (q == NULL || q->length == 0) {
        return 1; // Erro: queue vazia ou inválida
    }

    // 2. Colocar no endereço x o elemento que está no início (front)
    *x = q->values[q->front];

    // 3. Avançar o front de forma circular usando o q->size atual da estrutura
    // Se o front chegar ao fim do array alocado, volta para o índice 0
    q->front = (q->front + 1) % q->size;

    // 4. Decrementar o número de elementos atualmente na queue
    q->length--;

    return 0; // Sucesso
}

/*
Coloca no endereço x o elemento que está no início da
dinQueue (sem modificar a queue). A função deverá retornar 0 se a operação for possível (i.e. a
queue não está vazia) e 1 em caso de erro (queue vazia).
*/
int Dfront (DQueue q, int *x) {
    // 1. Validar se a estrutura existe e se tem elementos para ler
    if (q == NULL || q->length == 0) {
        return 1; // Erro: queue vazia ou inválida
    }

    // 2. Copiar o valor do início (front) para o endereço x
    // Como apenas lemos o valor, o q->front e o q->length NÃO se alteram
    *x = q->values[q->front];

    return 0; // Sucesso
}

void ShowDQueue (DQueue q){
    int i, p;
    printf ("%d Items: ", q->length);
    for (i=0, p=q->front; i<q->length; i++) {
        printf ("%d ", q->values[p]);
        p = (p+1)%q->size;
    }
    putchar ('\n');
}
