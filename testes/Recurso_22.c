#include <stdio.h>

/*
1. Implemente de forma eficiente uma função int pesquisa (int a[],
int N, int x) que, dado um array ordenado de tamanho N > 0,
devolve um índice onde se encontra o valor x. Caso x não exista no array
a função deverá devolver -1
*/

int pesquisa (int a[], int N, int x) {
    int i;

    for(i = 0; i < N; i++) {
        if(a[i] == x) {
            return i;
        } 
    }
    return -1;
}

/*
2. Implemente uma função void roda (LInt *l) que move o último
elemento da lista para a cabeça da mesma (sem alocar nova memória).
Considere a definição usual do tipo LInt
*/

typedef struct LInt_nodo {
    int valor;
    struct LInt_nodo *prox;
} *LInt;

void roda (LInt *l){
    LInt atual = *l;
    LInt anterior = NULL;
    int ultimo = 0;

    if(*l == NULL) return NULL;

    while(atual->prox != NULL) {
        anterior = atual;
        atual = atual->prox;
    }

    anterior->prox = NULL;
    atual->prox = *l;
    *l = atual;
}

/*
3. Implemente uma função int apaga (ABin a, int n) que apaga n
nodos de uma árvore binária. O critério para escolha de quais os nodos a
apagar é livre. Se a árvore tiver menos do que n nodos então a deve
apagar todos. A função deve devolver o número de nós efetivamente
apagados. Considere a definição usual do tipo ABin.
*/
typedef struct ABin_nodo {
    int valor;
    struct ABin_nodo *esq, *dir;
} *ABin;

int apaga (ABin a, int n) {
    int apagados = 0;

    if(a == NULL || n <= 0) return 0;

    apagados += apaga(a->esq,n-1);
    apagados += apaga(a->dir,n-1);

    if(apagados < n) {
        free(a);
        apagados++;
    }

    return apagados;
}

/*
4. Implemente uma função void checksum (char s[]) que, dada uma
uma string s com um identificador só com dígitos, acrescenta-lhe um dígito
de controle no final calculado de acordo com o método de Luhn. Neste
método, o dígito de controle a incluir deve fazer com que a soma de todos
os dígitos (incluindo o próprio dígito de controle) seja um múltiplo de 10.
No entanto, no caso dos dígitos em posições pares (a começar do final) o
que deve ser somado são os dígitos do número correspondente ao seu
dobro. Por exemplo, dado o identificador "9871", a soma em questão
corresponde a 9+1+6+7+2 = 25 (note como o dígito 1 e 8 foram
substituídos, respectivamente, por 2 e 1+6). Como a soma é 25, o dígito
de controle a acrescentar deve ser 5, pelo que a string no final deverá ser
"98715"
*/

void checksum(char s[]) {
    int i, len = 0, sum = 0, digito_controlo;

    // 1. Descobrir o tamanho atual da string
    while (s[len] != '\0') {
        len++;
    }

    // 2. Percorrer a string de trás para a frente
    for (i = len - 1; i >= 0; i--) {
        int v = s[i] - '0'; // Converte o caracter para um número real

        // A posição a contar da direita (incluindo o novo dígito que vamos pôr)
        // é dada por (len - i + 1). Se o resto da divisão por 2 for 0, é par!
        if ((len - i + 1) % 2 == 0) {
            v = v * 2;
            if (v > 9) {
                v = v - 9; // O tal truque matemático (ex: 16 passa a 7)
            }
        }
        
        sum += v; // Acumular na soma total
    }

    // 3. Descobrir qual o dígito que falta para chegar a um múltiplo de 10
    int resto = sum % 10;
    if (resto == 0) {
        digito_controlo = 0; // Já é múltiplo, acrescenta 0
    } else {
        digito_controlo = 10 - resto; // Ex: se soma for 25, falta 5 para chegar aos 30
    }

    // 4. Acrescentar o dígito no final da string e "fechar" a string
    s[len] = digito_controlo + '0'; // Transforma o número de volta em caracter
    s[len + 1] = '\0';              // O \0 marca o novo fim da string
}

/*
5. Implemente uma função int escolhe (int N, int valor[], int
peso[], int C, int quant[]) cujo objetivo é determinar a quantidade
de produtos que um vendedor ambulante deve transportar. O vendedor
tem à sua disposição uma quantidade ilimitada de N produtos diferentes,
cujos valores e pesos estão guardados nos arrays valor e peso,
respectivamente, mas só tem capacidade para transportar C kg. A função
deve tentar maximizar o valor total dos produtos a transportar, valor este
que deve ser devolvido, e colocar no array quant a respectiva quantidade
de cada produto. Por exemplo, se tivermos 3 produtos com valores
[20,150,30] e pesos [2,10,3] e capacidade para 14 kg, então uma
escolha ideal de quantidades seria [2,1,0], correspondente ao valor total
de 190. Mesmo que não consiga implementar uma estratégia de escolha
óptima, implemente outra que ache razoável. O critério mais importante é
o peso total não ultrapassar a capacidade de transporte C
*/

int escolhe(int N, int valor[], int peso[], int C, int quant[]) {
    int i;
    int valor_total = 0;
    int c_restante = C;

    // 1. Limpar o array de quantidades (garantir que começa tudo a zero)
    for (i = 0; i < N; i++) {
        quant[i] = 0;
    }

    // 2. Continuar a tentar meter coisas enquanto houver espaço
    while (c_restante > 0) {
        int melhor_item = -1;
        float melhor_racio = -1.0;

        // Procurar o produto mais valioso "por quilo" que AINDA CAIBA
        for (i = 0; i < N; i++) {
            if (peso[i] <= c_restante) {
                float racio = (float)valor[i] / peso[i];
                
                if (racio > melhor_racio) {
                    melhor_racio = racio;
                    melhor_item = i;
                }
            }
        }

        // Se não encontrámos nenhum item que caiba no espaço que sobrou, paramos
        if (melhor_item == -1) {
            break;
        }

        // Calcular quantos produtos deste tipo conseguimos meter no espaço restante
        int quantidade_a_levar = c_restante / peso[melhor_item];
        
        // Atualizar os nossos registos
        quant[melhor_item] += quantidade_a_levar;
        c_restante -= quantidade_a_levar * peso[melhor_item];
        valor_total += quantidade_a_levar * valor[melhor_item];
    }

    // Devolver o lucro máximo obtido com esta estratégia
    return valor_total;
}

int main() {

int array1[] = {45, 12, 89, 2, 55, 7, 34};
printf("%d\n", pesquisa(array1, 7, 55));

}