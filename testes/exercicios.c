#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Parte 1: Strings e Arrays
1. [Strings - 3 valores] Defina a função void remove_parentesis(char s[]) que, dada uma string, remove todos os caracteres que se encontram dentro de parêntesis, incluindo os próprios parêntesis. Modifique a string original.

2. [Arrays - 3 valores]
Defina a função void particiona(int v[], int N) que coloca todos os números pares no lado esquerdo do array e os ímpares no lado direito. Não é necessário que fiquem ordenados, apenas separados entre si. Pode usar funções auxiliares se achar necessário.

Parte 2: Listas Ligadas
Considere a definição usual do tipo LInt:

C
typedef struct lint_nodo {
    int valor;
    struct lint_nodo *prox;
} *LInt;
3. [Remoção Múltipla - 4 valores]
Defina a função int apagaMinimos(LInt *l) que encontra o valor mínimo da lista e apaga todas as suas ocorrências, devolvendo o número de nós apagados. Não se esqueça de libertar a memória dos nós removidos.

4. [Extração Destrutiva - 3 valores]
Defina a função LInt retiraMenor(LInt *l) que retira destrutivamente (sem alocar nem libertar memória) o nó com o menor valor da lista, devolvendo o apontador para esse mesmo nó.

5. [Ordenação em Cascata - 3 valores]
Usando obrigatoriamente a função definida na alínea anterior, defina LInt minSort(LInt l) que ordena a lista de forma estritamente Crescente.

Parte 3: Árvores Binárias
Considere a definição usual do tipo ABin:

C
typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;
6. [Mutação Física - 4 valores]
Defina a função void espelha(ABin a) que inverte fisicamente uma árvore binária (ou seja, a sub-árvore esquerda passa para a direita e vice-versa, descendo por todos os níveis da árvore original).

Boa sorte! Quando terminares o teu código, queres enviá-lo para eu fazer o papel de professor e corrigir os teus apontadores, ou preferes focar-te apenas num exercício específico de cada vez?
*/
void remove_parentesis(char s[]) {
    int i, j;
    int filtro = 1;

    for(i=0; s[i] != '\0'; i++) {
        if(s[i] == '(') {
            filtro = 0;
        } else if (s[i] == ')') {
            filtro = 1;
        } else if (filtro == 1) {
            s[j] = s[i];
            j++;
        }
    }
    s[j] = '\0';
}

int main() {
    char exp1[] = "31 + ((2 - 13) - x) + 114)";

    printf("%s\n", exp1);
    printf("%d\n", remove_parentesis(exp1));

    return 0;
}

//2
void swap(int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void particiona(int v[], int N) {
    int i = 0;
    int j = N-1;

    while(i < j) {
        if(v[i] % 2 == 0) {
            i++;
        } else if (v[j] % 2 != 0) {
            j--;
        } else {
            swap(v, i, j);
            i++;
            j--;
        }
    }
}

//3
typedef struct no {
    int valor;
    struct no *prox;
} *LInt;

int apagaMinimos(LInt *l) {
    int min = (*l)->valor;
    LInt atual = (*l)->prox;

    while(atual != NULL) {
        if(atual->valor < min) {
            min = atual->valor;
        }
        atual = atual->prox;
        }
    
    int count = 0;
    LInt anterior = NULL;
    LInt atual = *l; // Redefino a função

    while(atual != NULL) {
        if(atual->valor == min) {
            count++;

            LInt temp = atual->prox;

            if(anterior == NULL) {
                *l = temp;
            } else {
                anterior->prox = temp;
            }
            free(atual);
            atual = temp;
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }

    return count;
}

LInt retiraMenor(LInt *l) {
    LInt atual = *l;
    LInt anterior = NULL;
    
    LInt alvo = *l;
    LInt ant_alvo = NULL;

    while(atual != NULL) {
        if(atual->valor <= alvo->valor) {
            alvo = atual;
            ant_alvo = anterior;
        }
        anterior = atual;
        atual = atual->prox;
    }

    if(ant_alvo == NULL) {
        *l = alvo->prox;
    } else {
        ant_alvo->prox = alvo->prox;
    }
    alvo->prox = NULL;
    return alvo;
}

LInt minSort(LInt l) {
    LInt lista = NULL;

    while(l != NULL) {
        LInt min = retiraMenor(&l);
        min->prox = lista;
        lista = min;
    }

    LInt atual = lista;
    LInt seguinte;
    LInt anterior = NULL;

    while(atual != NULL) {
        seguinte = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = seguinte;
    }

}

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;

void espelha(ABin a) {

    if(a != NULL) {
    espelha(a->esq);
    espelha(a->dir);
        ABin temp = a->esq;
        a->esq = a->dir;
        a->dir = temp;
    }
}

/*
Parte 1: Strings e Arrays
1. [Extraído do Teste 22]
Implemente a função void inc(char s[]) que, dada uma uma string s com um número em decimal, incrementa esse número numa unidade. Assuma que a string tem espaço suficiente para armazenar o número resultante.
Exemplo: se a string for "123" deverá ser modificada para "124". Se for "199" deverá ser modificada para "200".

2. [Extraído do Recurso 23]
Apresente uma definição da função int verifica(char frase[], int k) que testa se todas as palavras que ocorrem numa frase têm pelo menos k caracteres.  

Parte 2: Listas Ligadas
Considere a definição usual do tipo LInt:

C
typedef struct lint_nodo {
    int valor;
    struct lint_nodo *prox;
} *LInt;
3. [Extraído do Teste 24]
Defina uma função int maxCresc(LInt l) que calcula o comprimento da maior sequência crescente de elementos consecutivos numa lista.
Exemplo: se a lista for [ 1, 2, 3, 2, 1, 4, 10, 12, 5, 4], a função deverá retornar 4. Serão desvalorizadas soluções que consultem cada nodo da lista mais do que uma vez.

4. [Extraído do Recurso 22]
Implemente uma função void roda(LInt *l) que move o último elemento da lista para a cabeça da mesma (sem alocar nova memória).

Parte 3: Árvores Binárias
Considere a definição usual do tipo ABin:

C
typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;
5. [Extraído do Recurso 25]
Defina uma função ABin folhaMaisProfunda (ABin a) que, dada uma árvore binária não vazia, calcula o endereço de uma das folhas que está no nível mais profundo. (Dica: Podes criar uma função auxiliar para calcular a altura de cada ramo).

6. [Extraído do Teste 25]
Implemente a função int parentesco(ABin a, int x, int y) que dada uma árvore binária de procura (sem números repetidos) e dois números que pertencem à árvore, calcula o grau de parentesco entre eles (a distância entre eles na árvore).
*/

//2
int verifica(char frase[], int k) {
    int i;
    int tamanho = 0;

    for(i = 0; frase[i] != '\0'; i++) {
        if(frase[i] == ' ') {
            if(tamanho > 0) {
                if(tamanho < k) return 0;
                tamanho = 0;
            }  
        } else {
            tamanho++;
        }
    }
    if(tamanho > 0) {
        if(tamanho < k) return 0;
        tamanho = 0;
    }
    return 1;
}

//3
int maxCresc(LInt l) {
    if (l == NULL) return 0;
    int max = l->valor;
    LInt atual = l->prox;

    int count_Max = 1;
    int count = 1;

    while(atual != NULL) {
        if(atual->valor > max) {
            count++;
        } else {
            if(count > count_Max) count_Max = count;
            count = 1;
        }
        max = atual->valor;
        atual = atual->prox;
    }
    if(count > count_Max) count_Max = count;
    return count_Max;
}

void roda(LInt *l) {
    if(*l == NULL || (*l)->prox == NULL) return;

    LInt atual = *l;
    LInt anterior = NULL;

    while(atual->prox != NULL) {
        anterior = atual;
        atual = atual->prox;
    }

    anterior->prox = NULL;// O penultimo passa a ser o corte
    atual->prox = *l;// O ultimo aponta pro inicio
    *l = atual;
}

ABin altura(ABin a) {
    if (a == NULL) return 0;

    int altDir = altura(a->dir);
    int altEsq = altura(a->esq);

    if(altDir > altEsq) {
        return 1 + altDir;
    } else {
        return 1 + altEsq;
    }
}

ABin folhaMaisProfunda (ABin a) {
    //Caso base
    if(a->dir == NULL && a->esq == NULL) return a;

    //Auxiliar
    if(altura(a->esq) > altura(a->dir)) {
        return folhaMaisProfunda(a->esq);
    } else {
        return folhaMaisProfunda(a->dir);
    }
}
/*
Parte 1: Strings e Arrays
1. [Extraído do Recurso 24]
Implemente uma função int expande(char s[]) que, dada uma string num formato compacto onde cada carácter é seguido de um dígito, expande essa string repetindo cada carácter o número de vezes indicado pelo dígito que o segue. A função deve devolver o tamanho da string expandida. Assuma que a string s tem espaço suficiente para armazenar a string expandida.
Exemplo: dada a string "x3y1z4" a função deve expandi-la para "xxxyzzzz" e retornar 8.

Parte 2: O Grande Desafio em Cascata (Listas Ligadas)
Considere a definição usual do tipo LInt:

C
typedef struct lint_nodo {
    int valor;
    struct lint_nodo *prox;
} *LInt;
2. [Alínea A - Extração Destrutiva - 3.5 valores]
Defina a função LInt retiraMaior(LInt *l) que procura o nó com o maior valor dentro da lista *l, remove-o da lista original (fazendo a costura dos ponteiros em segurança, sem usar free) e devolve o apontador para esse nó isolado. Se a lista estiver vazia, devolve NULL.

3. [Alínea B - Ordenação por Extração - 2.5 valores]
Usando obrigatoriamente a função retiraMaior que desenvolveu na alínea anterior, defina a função LInt maxSortCrescente(LInt l).
Esta função deve ordenar a lista de forma estritamente Crescente.
(Atenção à rasteira: No Teste 26, ao colares os nós na cabeça da nova lista, ela ficava Decrescente. Aqui o objetivo é que fique Crescente! Pensa bem se deves colar na cabeça ou se tens de arranjar uma estratégia para colar no fim da nova lista).

Parte 3: Árvores Binárias
Considere a definição usual do tipo ABin:

C
typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;
4. [Extraído do Teste 22]
Implemente a função LInt caminho(ABin a, int x) que, dada uma árvore binária de procura a e um valor x, devolve uma lista ligada (LInt) com todos os valores desde a raiz até x (inclusive). Se x não existir na árvore, deve devolver NULL.

Agora sim, o padrão está completo. Por qual destas queres começar a dar nós nos neurónios? Escreve o código da primeira que escolheres e manda para aqui!
*/


int expande(char s[]) {
    int i, j =  0;
    char aux[1000];

    for(i = 0; s[i] != '\0'; i++) {
        if( (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') ) {
            while(s[i+1] > '0') {
               s[i+1] = s[i+1] - '1';

               aux[j] = s[i];
               j++;
            }
        }
    }
    aux[j] = '\0';

    for(i=0;i<=j;i++) {
        s[i] = aux[i];
    }

    return j;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
typedef struct {  
    int inf,sup;  
} Intervalo; 

void swap(Intervalo c[], int i, int j) {
    Intervalo temp = c[i];
    c[i] = c[j];
    c[j] = temp;
}

void ordena(Intervalo c[], int N) {
    int i, j, min; // Mantemos as tuas variáveis
    Intervalo temp;

    // O ciclo 'i' escolhe a casa que queremos preencher (primeiro a 0, depois a 1...)
    for(i = 0; i < N - 1; i++) {
        
        min = i; // No início de cada ronda, assumimos que o menor está na casa 'i'
        
        // O ciclo 'j' é o teu olheiro. Ele corre o resto do array à procura do menor
        for(j = i + 1; j < N; j++) {
            if(c[j].inf < c[min].inf) {
                min = j; // Se encontrar um menor, atualiza o índice
            }
        }
        
        // CORREÇÃO: O teu 'if' e o teu 'swap' vêm para AQUI (fora do ciclo j)
        // Só trocamos quando o olheiro 'j' terminar de ver o array todo!
        if(min != i) {
            temp = c[i];
            c[i] = c[min];
            c[min] = temp;
        }
    }
}

int cardinalidade(Intervalo c[], int N) {
    if(N <= 0) return 0;
    int i;
    int count = 0;
    int inicio = c[0].inf;
    int fim = c[0].sup;

    for(i = 1; i < N; i++) {
        // Se o intervalo se sobrepõe ou toca no bloco atual
        if(c[i].inf <= fim) {
            if(c[i].sup > fim) {
                fim = c[i].sup; // Estica o bloco
            }
        } else {
                count += (fim - inicio + 1); // Fecha e contabiliza o bloco que ficou para trás
                inicio = c[i].inf; // Inicia um novo bloco com o intervalo atual
                fim = c[i].sup;
            }
        }
    count += (fim - inicio + 1); // Contabiliza o último bloco que ficou na memória
    return count;
    }
    

void camel2snake(char *id) {
    int i, j;
    int aux[100];

    for(i = 0; id[i] != '\0'; i++) {
        if(id[i] >= 'A' && id[i] <= 'Z') {
            aux[j] = id[i] - 32;
            j++;
            aux[j] = '_';
            j++;
        } else {
            aux[j] = id[i];
            j++;
        }
    }
    aux[j] = '\0';
    strcpy(id, aux);
}

////
typedef struct no { 
    int valor; 
    struct no *prox; 
} *LInt;


LInt arrayToList (int v[], int N) {
    int i;
    LInt lista = NULL;

    for(i = 0; i < N; i++) {
        LInt novo = malloc(sizeof(struct no));
        novo->valor = v[i];
        novo->prox = lista;
        lista = novo;
    }
}

int apagaUltimo(LInt *l, int x) {
    LInt atual = *l;
    LInt anterior = NULL;

    LInt alvo = *l;
    LInt anterior_alvo = NULL;

    if(*l == NULL) return 0;

    while(atual != NULL) {
        if(atual->valor == x) {
            alvo = atual;
            anterior_alvo = anterior;
        }
        anterior = atual;
        atual = atual->prox;
    }

    if(alvo == NULL) return 0;

    if(anterior_alvo == NULL) {
        *l = alvo->prox;
    } else {
        anterior_alvo->prox = alvo->prox;
    }
    free(alvo);
    return 1;
}   

int distanciaR(ABin a, int x) {
    if(a->valor == x) return 0;

    if (x < a->valor) {
        int res = distancia(a->esq, x);
        if (res == -1) return -1; // Se não encontrou lá abaixo, propaga o -1
        return 1 + res;           // Se encontrou, soma 1 passo ao resultado que veio lá de baixo
    } else {
        int res = distancia(a->dir, x);
        if (res == -1) return -1; // Se não encontrou, propaga o -1
        return 1 + res;           // Se encontrou, soma 1 passo
    }
}

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
    if(a == NULL) return -1;

    while(a != NULL) {
    if(x < a->valor && y < a->valor) {
        a = a->esq;
    } 
    else if(x > a->valor && y > a->valor) {
        a = a->dir;
    } 
    
    else {
        break;
        }
   }
   return(distancia(a,x) + distancia(a,y));
}

//////
int existe (int x, Intervalo c[], int N) {
    int i;

    for(i = 0; i < N; i++) {
        if(x >= c[i].inf && x <= c[i].sup) {
            return 1;
        }
    }
    return 0;
}

int acrescenta (Intervalo a, Intervalo c[], int N) {
    Intervalo pilha[1000];
    int j = 0;
    int ja_inseriu_a = 0;

    for(int i = 0; i < N; i++) {
        if(a.sup <= c[i].inf && ja_inseriu_a == 0) {
            pilha[j] = a;
            j++;
            ja_inseriu_a = 1;
        }
        pilha[j] = c[i];
        j++;
    }
    if(ja_inseriu_a == 0) {
        pilha[j] = a; //Inserir no ultimo
        j++;
    }

    for(int i = 0; i < j; i++) {
        c[i] = pilha[i];
    }

    return j;
}

//
#include <ctype.h> // Para usar o isalpha()

void invertePals(char *frase) {
    int i = 0;

    // 1. Percorrer a frase toda
    while (frase[i] != '\0') {
        
        // Se encontrarmos o início de uma palavra (uma letra)
        if (isalpha(frase[i])) {
            int inicio = i;
            int fim = i;

            // 2. O 'fim' avança enquanto continuar a ver letras
            while (frase[fim] != '\0' && isalpha(frase[fim])) {
                fim++;
            }
            // Rasteira: o 'fim' parou no carater que já NÃO é letra (ou no \0).
            // O último carater da palavra está uma posição atrás!
            fim--; 

            // 3. O SWAP TRADICIONAL (Inverter a palavra no sítio)
            // Guardamos o 'fim' na variável 'j' para não estragar a contagem do ciclo principal
            int j = fim; 
            int k = inicio;
            
            while (k < j) {
                char temp = frase[k];
                frase[k] = frase[j];
                frase[j] = temp;
                
                k++;
                j--;
            }

            // 4. Saltamos o 'i' para o fim desta palavra para não reprocessar as mesmas letras
            i = fim;
        }
        
        i++; // Avança para o próximo caráter da frase
    }
}

int listToArray (LInt l, int v[], int N) {
    int i;
    for(i = 0; i < N && l != NULL; i++) {
        v[i] = l->valor;
        l = l->prox;
    }
    return i;
}

int removeMenores(LInt *l) {
    if (*l == NULL) return 0; // 

    LInt anterior = *l;
    LInt atual = (*l)->prox;
    int count = 0; 

    while (atual != NULL) {
        if(atual->valor < anterior->valor) { 
            LInt temp = atual->prox;
            anterior->prox = temp;
            free(atual);
            atual = temp;
            count++;
        } else { 
            anterior = atual;
            atual = atual->prox;
        } // Fecho do else
    } 
    return count; 
}

int altura(ABin a) {
    if(a == NULL) return 0;

    int altEsq = altura(a->esq);
    int altDir = altura(a->dir);

    if(altEsq > altDir) {
        return 1 + altEsq;
    } else {
        return 1 + altDir;
    }
}

ABin folhaMaisProfunda (ABin a) {
    if (a == NULL) return NULL;

    if(a->esq == NULL && a->dir == NULL) return a;

    int altEsq = altura (a->esq);
    int altDir = altura(a->dir);

    if(altEsq > altDir) {
        return folhaMaisProfunda(a->esq);
    } else {
        return folhaMaisProfunda(a->dir);
    }
}

//{1,2,3,4,5,6} e se r == 2 então o array deverá ficar com os valores 
//{3,4,5,6,1,2}
void rodaEsq(int a[], int N, int r) {
    int temp[r];

    for(int i = 0; i < r; i++) {
        temp[i] = a[i]; // temp = {1,2}
    }

    for(int i = 0; i < N-r; i++) {
        a[i] = a[i+r]; //a[i] = {3,4,5,6,5,6}
    }

    for(int i = 0; i < r; i++) {
        a[N-r+i] = temp[i]; //a[N-r+i] = {3,4,5,6,1,2}
    }
}

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

int delete(int n, LInt *l) {
    LInt atual = *l;
    LInt anterior = NULL;

    while(n > 0 && atual != NULL) {
        anterior = atual;
        atual = atual->prox;
        n--;
    }

    if(atual == NULL) return 0;

    if(anterior = NULL) {
        *l = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual);
    return l;
}

int maxCresc(LInt l) {
    if(l == NULL) return 0;

    LInt anterior = l;
    LInt atual = l->prox;
    int count = 1;
    int max = 1;

    while(atual != NULL) {
        if(anterior->valor < atual->valor) {
            count++;
        } else {
            if (count > max) max = count;
            count = 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    if(count > max) max = count;
    return max;
}

int parentesisOk(char exp[]) {
    int pilha[100];
    int i, j;
    int filtro = 0;

    for(i = 0; exp[i] != '\0'; i++) {
        if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
            pilha[j] = exp[i];
            j++;
        } else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {

            if(j == 0) return 0;

            char ultimo = pilha[j-1];

            if((exp[i] == ')' && ultimo == '(') || (exp[i] == '[' && ultimo == ']') || (exp[i] == '{' && ultimo == '}')) {
                j--;
            } else {
                return 0;
            }
        }
    }
    return (j == 0);
}

int quantosMaiores(LInt l) {
    int count = 0;
    int max = l->valor;
    LInt atual = l->prox;

    while(atual != NULL) {
        if(atual->valor > max) {
            int count = 0;
            max = atual->valor;
        } else if(atual->valor == max) {
            count++;
        }
    }
}