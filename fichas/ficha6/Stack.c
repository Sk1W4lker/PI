#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// Static stacks 
//inicializa uma stack (passa a representar uma stack vazia)
void SinitStack (SStack s){
	if(s != NULL) {
		s->sp = 0;
	}
}

// Testa se uma stack  ́e vazia
int  SisEmpty (SStack s){
	if(s != NULL && s->sp == 0) {
	return 1;
	}
	return 0;
}

/*
acrescenta x ao topo de s; a fun ̧c ̃ao deve retornar 0 se
a opera ̧c ̃ao fˆor feita com sucesso (i.e., se a stack ainda n ̃ao estiver cheia) e 1 se a opera ̧c ̃ao
n ̃ao fˆor poss ́ıvel (i.e., se a stack estiver cheia).*/
int  Spush (SStack s, int x){
	int r = 0;
	
	if(s != NULL) {
		if(s->sp == Max) {
			r = 1;
		} else {
			s->values[s->sp] = x; //s->sp aponta sempre pro proximo livre;
			s->sp++;
		}
	}
	return r;
}

/*
 remove de uma stack o elemento que est ́a no topo. A
fun ̧c ̃ao dever ́a colocar no endere ̧co x o elemento removido. A fun ̧c ̃ao dever ́a retornar 0 se a
opera ̧c ̃ao for poss ́ıvel (i.e. a stack n ̃ao est ́a vazia) e 1 em caso de erro (stack vazia)
*/
int  Spop (SStack s, int *x) {
	int r=0;

	if(s->sp == 0) {
		r = 1;
	} else {
		s->sp--;
		*x = s->values[s->sp];
	}

	return r;
}
/*
coloca no endere ̧co x o elemento que est ́a no topo da
stack (sem modificar a stack). A fun ̧c ̃ao dever ́a retornar 0 se a opera ̧c ̃ao for poss ́ıvel (i.e. a
stack n ̃ao est ́a vazia) e 1 em caso de erro (stack vazia)
*/
int  SStop (SStack s, int *x) {
	int r=0;

	if(s->sp == 0) {
		r = 1;
	} else {
		*x = s->values[s->sp-1];
		r = 0;
	}

	return r;
}

void ShowSStack (SStack s){
    int i;
    printf ("%d Items: ", s->sp);
    for (i=s->sp-1; i>=0; i--) 
        printf ("%d ", s->values[i]);
    putchar ('\n');
}

// Stacks with dynamic arrays

int dupStack (DStack s) {
	int r = 0, i;
	int *t = malloc (2*s->size*sizeof(int));

	if (t == NULL) r = 1;
	else {
		for (i=0; i<s->size; i++) 
			t[i] = s->values[i];
		free (s->values);
		s->values = t;
		s->size*=2;
	}
	return r;
}

void DinitStack (DStack s) {
	if(s != NULL) {
		s->size = Max;
		s->sp = 0;
		s->values = (int *) malloc(s->size * (sizeof (int)));
	}
}

int  DisEmpty (DStack s) {
	if(s != NULL) {
		if(s->sp == 0) return 1;
	}
	return 0;
}

int  Dpush (DStack s, int x){
	if(s != NULL) {
		if(s->sp == s->size) {
			int novo_tamanho = 2 * s->size;
			int *temp = (int *) realloc(s->values, novo_tamanho * sizeof(int));

			s->values = temp;
			s->size = novo_tamanho;
		}
		s->values[s->sp] = x;
		s->sp++;

		return 0;
	}
	return 1;
}

int  Dpop (DStack s, int *x){
	if(s != NULL) {
		if(s->sp == s->size) {
			return 0;
		}
		*x = s->values[s->sp];
		s->sp--;
		return 0;
	}
	
	return 1;
}

/*coloca no endere ̧co x o elemento que est ́a no topo da
stack (sem modificar a stack). A fun ̧c ̃ao dever ́a retornar 0 se a opera ̧c ̃ao for poss ́ıvel (i.e. a
stack n ̃ao est ́a vazia) e 1 em caso de erro (stack vazia).*/
int  Dtop (DStack s, int *x){
if(s != NULL) {
	if(s->sp == 0) {
		return 1;
	}
	*x = s->values[s->sp - 1];
	return 0; 
	}
	return 1;
}

void ShowDStack (DStack s){
    int i;
    printf ("%d Items: ", s->sp);
    for (i=s->sp-1; i>=0; i--) 
        printf ("%d ", s->values[i]);
    putchar ('\n');
}
