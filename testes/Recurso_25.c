/*
1. Um conjunto de inteiros pode ser representado como uma união de
intervalos. Por exemplo, o conjunto {1,2,3,4,5,6,10,11} pode ser representado
pela união dos intervalos [1..6] e [10..11]. Implemente a função int existe
(int x, Intervalo c[], int N) que dado um conjunto c com N intervalos
guardados num array, testa se o número x pertence a esse conjunto. Assuma
que o conjunto está representado de forma normalizada, não existindo
intervalos que se intersectam e estando os intervalos ordenados de forma
crescente. O tipo Intervalo está declarado da seguinte forma.
typedef struct {
int inf,sup;
} Intervalo;
*/

typedef struct {
    int inf,sup;
} Intervalo;

int existe (int x, Intervalo c[], int N) {
    for(int i = 0; i < N; i++) {
        if(x >= c[i].inf && x <= c[i].sup) {
            return 1; 
        }
    }
    return 0; 
}

/*
2. Implemente a função int acrescenta (Intervalo a, Intervalo c[],
int N), que dado um conjunto c com N intervalos guardados num array de
forma normalizada (ordenados de forma crescente e sem haver intervalos
que se intersectam), acrescenta o intervalo a a esse conjunto, mantendo a
representação normalizada. A função deve devolver o número de intervalos
usados para representar o conjunto resultante.
*/

int acrescenta (Intervalo a, Intervalo c[], int N) {
    Intervalo pilha[1000];
    int j = 0;
    int ja_inseriu_a = 0; // 0 = ainda não colámos o 'a', 1 = já colámos

    for(int i = 0; i < N; i++) {
        // Se o 'a' fica antes do c[i] e ainda não o inserimos, colamos o 'a' primeiro!
        if(a.sup <= c[i].inf && ja_inseriu_a == 0) {
            pilha[j] = a;
            j++;
            ja_inseriu_a = 1; // Marcamos que o 'a' já está na pilha
        }
        pilha[j] = c[i];
        j++;
    }

    if(ja_inseriu_a == 0) {
        pilha[j] = a;
        j++;
    }

    for(int k = 0; k < j; k++) {
        c[k] = pilha[k];
    }

    return j;
}

/*
3. Defina uma função void invertePals (char *frase) que inverte cada
uma das palavras de uma frase (assuma que uma palavra é uma sequência
de caracteres alfabéticos). Por exemplo, se char f[] = "Ser ou nao ser,
eis a questao.", após a invocação invertePals(f) o array f deve conter
a string "reS uo oan res, sie a oatseuq."
*/
// Função auxiliar simples para inverter um pedaço de texto entre dois índices
#include <string.h>

void invertePals(char *frase) {
    char aux[1000];
    strcpy(aux, frase); // Guardamos uma cópia da frase original no aux

    int i = 0; // Índice para ler do aux
    int j = 0; // Índice para escrever na frase

    while (aux[i] != '\0') {
        // Se encontrarmos uma letra, vamos ver até onde vai esta palavra
        if ((aux[i] >= 'a' && aux[i] <= 'z') || (aux[i] >= 'A' && aux[i] <= 'Z')) {
            int inicio = i;
            
            // Andamos para a frente para descobrir o fim da palavra
            while ((aux[i] >= 'a' && aux[i] <= 'z') || (aux[i] >= 'A' && aux[i] <= 'Z')) {
                i++;
            }
            int fim = i - 1;

            // Agora escrevemos a palavra de TRÁS PARA A FRENTE na frase!
            for (int k = fim; k >= inicio; k--) {
                frase[j] = aux[k];
                j++;
            }
        } 
        // Se não for uma letra (espaço, ponto, vírgula), copiamos igualzinho
        else {
            frase[j] = aux[i];
            j++;
            i++;
        }
    }
    frase[j] = '\0'; // Fecho obrigatório da string final
}
/*
. Defina a função int listToArray (LInt l, int v[], int N) que
dada uma lista l preenche o array v com os elementos da lista (sem alterar a
lista). A função deverá preencher no máximo N elementos e retornar o
número de elementos preenchidos. O tipo LInt está declarado da seguinte
forma.
*/
typedef struct no {
    int valor;
    struct no *prox;
} *LInt;

int listToArray (LInt l, int v[], int N) {
    int i = 0;

    for(i = 0; i < N && l != NULL; i++) {
        v[i] = l->valor;
        l = l->prox;
    }
    return i;
}

/*
5. Defina a função int removeMenores(LInt *l) que dada uma lista l
remove dessa lista todos os nós que tenham um valor estritamente menor
que o nó anterior na lista original. A função deve devolver o comprimento da
lista resultante
*/

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

/*
6. Defina uma função ABin folhaMaisProfunda (ABin a) que, dada uma
árvore binária não vazia, calcula o endereço de uma das folhas que está no
nível mais profundo. Na seguinte árvore poderia devolver o endereço de um
dos seguintes nós: 8,17 ou 21. O tipo ABin está declarado da seguinte forma.
*/
typedef struct nodo {
int valor;
struct nodo *esq, *dir;
} *ABin;

ABin altura (ABin a) {
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

    if(a->esq == NULL && a->dir == NULL) {
        return a;
    }

    if(altura(a->esq) > altura(a->dir)) {
        return folhaMaisProfunda(a->esq);
    } else {
        return folhaMaisProfunda(a->dir);
    }
}