#include <stdlib.h> // Obrigatório para o malloc
#include <string.h>
/*
1. Implemente a função int perfeito(int x) que testa se um número
inteiro é perfeito, isto é, se é igual à soma dos seus divisores próprios. Por
exemplo, 28 é um número perfeito, uma vez que os seus divisores
próprios são 1, 2, 4, 7 e 14 (1+2+4+7+14==28).
*/
int perfeito(int x) {
    int soma = 0;

    for(int i = 0; i < x; i++) {
        if(x % i == 0) {
            soma += i;
        }
    }

    if(soma == x) {
        return 1;
    } else {
        return 0;
    }
} 

/*
2. Implemente a função void ordena(Ponto pos[], int N) que dado um
array com N pontos ordena esses pontos por ordem crescente da distância
à origem. Por exemplo se o array for {{3,3},{2,1},{-1,0}} depois de
ordenado deverá ficar com o conteúdo {{-1,0},{2,1},{3,3}}. O tipo
Ponto é definido da seguinte forma (note que as coordenadas dos pontos
são números inteiros).
*/
typedef struct {
    int x,y;
} Ponto;

int distanciaOrigem(Ponto p) {
    return ((p.x * p.x) + (p.y * p.y));
}

void ordena(Ponto pos[], int N) {

    for(int i = 0; i < N - 1; i++) {
        for(int j = i + 1; j < N; j++) {
            if(distanciaOrigem(pos[i]) > distanciaOrigem(pos[j])) {
                Ponto temp = pos[i];
                pos[i] = pos[j];
                pos[j] = temp;
            }
        }
    }
}


/*
3. Apresente uma definição da função int depth(ABin a, int x) que
devolve o menor nível a que um elemento x se encontra na árvore (ou -1
se x não se encontra na árvore). Considere a definição usual do tipo ABin.
Considere ainda que a raiz se encontra no nível 0.
*/

typedef struct abin_nodo {
int valor;
struct abin_nodo *esq, *dir;
} *ABin;

// Função Auxiliar que leva o nível atual na viagem
int depthAux(ABin a, int x, int nivelAtual) {
    if (a == NULL) return -1;
    if (a->valor == x) return nivelAtual;

    int esq = depthAux(a->esq, x, nivelAtual + 1);
    int dir = depthAux(a->dir, x, nivelAtual + 1);

    if (esq != -1 && dir != -1) {
        if (esq < dir) {
            return esq; 
        } else {
            return dir;
        }
    }
    
    if (esq != -1) {
        return esq;
    } else {
        return dir;
    }
}

// A função principal que o professor pediu apenas chama a auxiliar a começar no nível 0
int depth(ABin a, int x) {
    return depthAux(a, x, 0);
}

/*
4. Implemente a função int wordle(char secreta[], char
tentativa[]) que dada uma palavra secreta que se pretende descobrir e
uma tentativa com o mesmo tamanho devolve o número de caracteres na
palavra tentativa em que o utilizador já acertou. Ambas as palavras só
contêm letras minúsculas. A função deve também modificar a tentativa
substituindo todas as letras que não tem correspondente na palavra
secreta por um '*' e convertendo para maiúscula as letras que estão na
posição certa. Por exemplo se a palavra secreta for "laranja" e a
tentativa for "cerejas" a função deve devolver 1 e alterar a tentativa para
"**R*ja*" (apenas o 'r' está na posição certa e os caracteres 'j' e
'a' aparecem no segredo noutras posições). Se a tentativa for "bananas"
a função deve devolver 3 e alterar a tentativa para "*A*ANa*"
*/

int wordle(char secreta[], char tentativa[]) {
    // CORREÇÃO 1: Mudado de int para char
    char aux[1000]; 
    int tamanho = strlen(secreta);
    int acertos = 0;

    for(int i = 0; i < tamanho; i++) {
        if(secreta[i] == tentativa[i]) {
            aux[i] = secreta[i] - 32;
            acertos++;
        } else {
            int filtro = 0;

            for(int j = 0; j < tamanho; j++) {
                if(secreta[j] == tentativa[i]) {
                    // CORREÇÃO 3: Removido o acertos++ daqui de dentro
                    filtro = 1;
                    break; // Dica: podes parar o ciclo mal encontres uma
                }
            }

            if(filtro == 1) {
                aux[i] = tentativa[i];
            } else {
                // CORREÇÃO 2: Mudado de "*" para '*'
                aux[i] = '*'; 
            }
        }
    }

    // CORREÇÃO 4: Fechar, copiar e retornar
    aux[tamanho] = '\0'; // Garante que o aux é uma string válida
    strcpy(tentativa, aux); // Passa o resultado para a tentativa original
    
    return acertos;
}

/*
5. Implemente a função LInt periodica(char s[]) que dada uma string
com uma sequência infinita periódica de dígitos constrói uma lista (circular)
com esses dígitos. Assuma que a parte da sequência que se repete
indefinidamente está representada entre parênteses e aparece sempre no
final da string. Assuma também a definição usual do tipo LInt. Por
exemplo, se a string for "34(56)" deverá ser construída a seguinte lista.
*/
typedef struct lint_nodo {
    int valor;
    struct lint_nodo *prox;
} *LInt;

LInt periodica(char s[]) {
    LInt head = NULL;         // Guarda o início absoluto da lista (o 1º nó)
    LInt aux = NULL;          // Ponteiro para o último nó que foi colado
    LInt inicio_loop = NULL;  // Guarda o nó onde a repetição recomeça (ex: o 5)
    
    int dentro_parentesis = 0; // Sinalizador (0 = Falso, 1 = Verdadeiro)

    for (int i = 0; s[i] != '\0'; i++) {
        
        // FASE 2: Encontrámos o início da repetição
        if (s[i] == '(') {
            dentro_parentesis = 1; // Ativa o alarme! O próximo nó será o início do loop
        } 
        // FASE 3: Encontrámos o fim da string/período
        else if (s[i] == ')') {
            break; // Já lemos tudo o que importava, podemos sair do ciclo
        } 
        // FASE 1: É um número, vamos criar o nó
        else {
            // 1. Aloca memória para o novo nó
            LInt novo = (LInt)malloc(sizeof(struct lint_nodo));
            
            // 2. Converte o caractere (ex: '3') para o número inteiro real (3)
            novo->valor = s[i] - '0'; 
            novo->prox = NULL;

            // 3. Cola o nó na lista
            if (head == NULL) {
                // Se for o primeiríssimo nó, o head agarra-o para sempre
                head = novo;
                aux = novo;
            } else {
                // Se já existirem nós, colamos à frente do último (aux)
                aux->prox = novo;
                aux = novo; // O aux avança para o novo último nó
            }

            // 4. Se o alarme do '(' foi ativado, memoriza ESTE nó
            if (dentro_parentesis == 1) {
                inicio_loop = novo;    // Guardámos o endereço do nó (ex: o 5)
                dentro_parentesis = 2; // Passa a 2 para não voltar a entrar aqui
            }
        }
    }

    // O GRANDE TRUQUE: Fechar o círculo
    // Se a string tinha parêntesis, o 'aux' está parado no último nó (o 6)
    // Obrigamos o seu 'prox' a apontar de volta para o 'inicio_loop' (o 5)
    if (inicio_loop != NULL) {
        aux->prox = inicio_loop;
    }

    // Devolvemos a locomotiva do comboio!
    return head; 
}