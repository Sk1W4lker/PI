#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//1 - Defina um programa que lˆe (usando a fun ̧c ̃ao scanf uma sequˆencia de n ́umeros inteiros terminada com o n ́umero 0 e imprime no ecran o maior elemento da sequˆencia
void maior() {
    int largest = INT_MIN, num = INT_MIN;
    printf("Insira uma lista de valores (0 é para parar)\n");
    while(1) {
        assert(scanf("%d", &num) == 1);
        if(num == 0) break;
        if (num > largest) largest = num;
    }
    printf("O maior valor inserido é: %d\n", largest);
}

//2 - lê (usando a fun ̧c ̃ao scanf uma sequˆencia de n ́umeros inteiros terminada com o n ́umero 0 e imprime no ecran a m ́edia da sequˆencia.
void media() {
    int soma = 0, num = 0, count = 0;
    printf("Insira uma lista de valores (0 é para parar)\n");
    while(1) {
        assert(scanf("%d", &num) == 1);
        if(num == 0) break;
        soma += num;
        count++;
    }
    int media = 0;
    if (count > 0) media = soma / count;
    printf("A média é: %d\n", media);
}

//3 - lê (usando a função scanf uma sequência de numeros inteiros terminada com o numero 0 e imprime no ecran o segundo maior elemento.
void segundoMaior() {
    int largest = INT_MIN, num = INT_MIN;
    int segundo;
    printf("Insira uma lista de valores (0 é para parar)\n");
    while(1) {
        assert(scanf("%d", &num) == 1);
        if(num == 0) break;
        if (num > largest) {
         segundo = largest;
         largest = num;
        }
    }
    printf("O segundo maior valor inserido é: %d\n", segundo);
}

//4 - calcula o n ́umero de bits iguais a 1 usados na representa ̧c ̃ao bin ́aria de um dado n ́umero n.
int bitsUm(unsigned int n) {
    // Condição de continuação/paragem: 
    // Se o número ainda for maior que 0, significa que ainda há bits válidos para analisar.
    if (n > 0)
        /* Aqui acontecem 3 coisas em simultâneo:
         1. (n & 1): Olha para o último bit da direita. Devolve 1 se for '1', ou 0 se for '0'.
         2. (n >> 1): Desloca os bits do número uma casa para a direita (descarta o que acabámos de ver).
         3. bitsUm(...): Chama novamente a função com o novo número e soma o resultado ao bit atual.
        */
        return (n & 1) + bitsUm(n >> 1);
    else
        // Caso Base: Se o n chegou a 0, já não há mais bits '1' para contar. 
        // Retornamos 0 para terminar e começar a somar a cadeia de chamadas para trás.
        return 0;
}

//5 - calcula o n ́umero de bits a 0 no final da representa ̧c ̃ao bin ́aria de um n ́umero
int trailingZ(unsigned int n) { // Exemplo: 10010100 -> tem 2 zeros à direita
    
    // 1. Caso base especial: O número é 0 (todos os bits são zero)
    // Retorna 8 (ou 32, dependendo do tamanho do inteiro exigido no exercício)
    if (n == 0)
        return 8; 
        
    // 2. Caso base principal: O último bit da direita é 1
    // Se encontrámos um '1', a sequência de zeros à direita acabou. Retornamos 0.
    if (n & 1)
        return 0;
        
    // 3. Passo recursivo: O último bit é 0
    // Somamos 1 ao nosso total e chamamos a função novamente, mas com os bits
    // empurrados uma casa para a direita (n >> 1), descartando o zero que já contámos.
    else
        return 1 + trailingZ(n >> 1);
}

//6 - Defina uma fun¸c˜ao int qDig (unsigned int n) que calcula o n´umero de d´ıgitos necess´arios para escrever o inteiro n em base decimal. Por exemplo, qDig (440) deve retornar 3.
int qDig (unsigned int n) {
    if (n / 10 < 1) return 1;
    else return 1 + qDig(n/10);
}

//7 - Apresente uma defini¸c˜ao da fun¸c˜ao pr´e-definida em C char *strcat (char s1[], char s2[]) que concatena a string s2 a s1 (retornando o endere¸co da primeira).
char *strcatM(char s1[], char s2[]) {
    int i, j;

    for(i = 0; s1[i] != '\0'; i++);
    for(j = 0; s2[j] != '\0'; j++) {
            s1[i+j] = s2[j]; 
    }
    s1[i+j] = '\0';
    return s1;
    }

//8 - Apresente uma defini¸c˜ao da fun¸c˜ao pr´e-definida em C char *strcpy (char *dest, char source[]) que copia a string source para dest retornando o valor desta ´ultima.
char *strcpy (char *dest, char source[]) {
    int i;

    for(i=0; source[i]; i++) {
        dest[i] = source[i];
    }
    dest[i] = '\0';
    return dest;
}

/*9 - Apresente uma defini ̧c ̃ao da fun ̧c ̃ao pr ́e-definida em C int strcmp (char s1[], char s2[])
que compara (lexicograficamente) duas strings. O resultado dever ́a ser
•0 se as strings forem iguais
•<0 se s1 < s2
•>0 se s1 > s2
*/
int strcmpM(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i] && s1[i] != '\0'; i++);
    return (s1[i] - s2[i]);
}

//10 - Apresente uma defini¸c˜ao da fun¸c˜ao pr´e-definida em C char *strstr (char s1[], char s2[]) que determina a posi¸c˜ao onde a string s2 ocorre em s1. A fun¸c˜ao dever´a retornar NULL caso s2 n˜ao ocorra em s1
#include <stddef.h>

char *strstrM(char s1[], char s2[]) {
    int i, j;

    if (s2[0] == '\0') return s1;

    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            // Usamos um IF para testar as letras.
            // Se as letras forem diferentes, o 'break' mata este ciclo 'for' de dentro 
            // e o programa volta ao ciclo de fora para testar a próxima posição 'i'.
            if (s1[i + j] != s2[j]) {
                break; 
            }
        }
        // Se o ciclo de dentro terminou porque o 'j' chegou ao '\0' (e não por causa do break),
        // significa que todas as letras eram iguais!
        if (s2[j] == '\0') {
            return &s1[i];
        }
    }

    return NULL;
}

//11 - Defina uma fun ̧c ̃ao void strrev (char s[]) que inverte uma string.
void strrev (char s[]) {
    int tamanho;

    for(tamanho=0; s[tamanho] != '\0'; tamanho++);
    char rev[tamanho];
    for(int i=0; i < tamanho; i++) rev[i] = s[tamanho - i - 1];
    for(int i=0; i < tamanho; i++) s[i] = rev[i];
}

//12 - Defina uma fun ̧c ̃ao void strnoV (char s[]) que retira todas as vogais de uma string.

int eVogal(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
    }

void strnoV (char s[]) {
    int i, j;

    for(i = 0; s[i] != '\0'; i++){
        if (!eVogal(s[i])) {
            s[j] = s[i];
            j++;
        }
    }
    s[j] = '\0';
}

//13 - "liberdade, igualdade e fraternidade", a invoca ̧c ̃ao de truncW (txt, 4) deve fazer com que passe a estar l ́a armazenada a string "libe igua e frat"
void truncW(char t[], int n) {
    int i, j = 0, cont = 0;

    // O Leitor 'i' percorre a frase
    for(i = 0; t[i] != '\0'; i++) {
        
        // Se for um separador (espaço, parágrafo ou tabulação)
        if(t[i] == ' ' || t[i] == '\n' || t[i] == '\t') {
            t[j] = t[i]; // O Escritor copia o espaço para manter as palavras separadas!
            j++;         // O Escritor avança
            cont = 0;    // Resetamos o contador de letras da palavra
        } 
        // Se for uma letra
        else {
            if(cont < n) {
                t[j] = t[i]; // O Escritor só copia a letra se ainda não passámos do limite 'n'
                j++;
            }
            cont++; // Aumentamos o contador de letras da palavra atual
        }
    }
    
    // Fechamos a string onde o Escritor parou
    t[j] = '\0';
}

//14

//AUXILIAR
int countChar(char s[], char x) {
    int count = 0; // 2. Inicializamos a 0 para limpar o lixo de memória!

    for(int i = 0; s[i] != '\0'; i++) {
        if (s[i] == x) count++;
    }
    return count;
}

char charMaisfreq(char s[]) {
    // Proteção: se a string for vazia, devolve o terminador nulo
    if (s[0] == '\0') return '\0';

    int i;
    int freq = countChar(s, s[0]);
    char acc = s[0]; // 3. O 'acc' arranca logo com a primeira letra!

    for(i = 0; s[i] != '\0'; i++) {
        // Chamamos a função apenas uma vez por letra para o computador não fazer trabalho a dobrar
        int contagemAtual = countChar(s, s[i]); 
        
        if (contagemAtual > freq) {
            freq = contagemAtual;
            acc = s[i]; // Guardamos a nova letra campeã
        }
    }
    return acc;
}

//15
int iguaisConsecutivos (char s[]) {
    int i;
    int count = 1;
    int acc = 1;

    if (s[0] == '\0') return 0;
    for(i=1; s[i] != '/0'; i++) {
        if (s[i] == s[i-1]) {
        count++;
        } else { 
        count = 1;
        if(count > acc) acc = count;
        }
    }
    return acc;
}

//16
int difConsecutivos (char s[]) {
    int i;
    int count = 1;
    int acc = 1;

    if (s[0] == '\0') return 0;
    for(i=1; s[i] != '/0'; i++) {
        if (s[i] != s[i-1]) {
        count++;
        } else { 
        count = 1;
        if(count > acc) acc = count;
        }
    }
    return acc;
}

//17
int maiorPrefixo (char s1 [], char s2 []) {
    int i;
    for(i = 0; s1[i] == s2[i] && s1[i]; i++);
    return i;
}

//18
int maiorSufixo (char s1 [], char s2 []) {
    int i = 0, j = 0, conta = 0;
    // 1. Descobrir o tamanho de s1
    while (s1[i] != '\0') i++;
    
    // 2. Descobrir o tamanho de s2
    while (s2[j] != '\0') j++;

    // 3. Recuar os índices para a última letra real (antes do \0)
    i--; 
    j--;

    // 4. Comparar de trás para a frente
    // Paramos se os índices chegarem a -1 (início da string) 
    // ou se as letras forem diferentes
    while (i >= 0 && j >= 0 && s1[i] == s2[j]) {
        conta++;
        i--;
        j--;
    }

    return conta;
}

//19
int sufPref (char s1[], char s2[]) {
    int i;
    int j = 0;

    for(i=0; s1[i] != '\0'; i++) {
        if(s1[i] == s2[j]){
            j++;
        } else {
            j = 0;
        }
    }
    return j;
}
//20
int contaPal(char s[]) {
    int cont = 0, i, pal = 1;
    /*
    pal == 1 -> esta em palavra mas nao contou
    pal == -1 -> esta em palavra e ja contou
    pal == 0 -> nao esta em palavra
    */
    for (i = 0; s[i] != '\0'; i++) {
        if (isspace(s[i]))
            pal = 0;
        else if (pal == 0)
            pal = 1;
        if (pal > 0) {
            cont++;
            pal = -1;
        }
    }
    return cont;
}

//21
int contaVogais (char s[]) {
    int i;
    int count = 0;

    for(i=0;s[i]!='\0';i++) {
        if(eVogal(s[i])) count++;
    } 
    return count;
}

/*22 Defina uma fun ̧c ̃ao int contida (char a[], char b[]) que testa se todos os caracteres da
primeira string tamb ́em aparecem na segunda. Por exemplo, contida ("braga","bracara
augusta") deve retornar verdadeiro enquanto que contida ("braga","bracarense") deve
retornar falso
*/

//AUXILIAR
int pertence (char s[], char x) {
    int i;

    for(i=0; s[i] != '\0'; i++) {
        if(s[i] == x) return 1;
    }
    return 0;
}

int contida (char a[], char b[]) {
    int i;
    
    for(i=0; a[i] != '/0'; i++) {
        if (!pertence(b, a[i])) return 0;
    }
    return 1;
}

//23 Defina uma fun ̧c ̃ao int palindorome (char s[]) que testa se uma palavra  ́e palındrome,
//i.e., lˆe-se de igual forma nos dois sentidos.

int palindorome (char s[]) {
    int j = strlen(s) - 1;
    int p = strlen(s) / 2;

    for(int i=0; i < p; i++) {
        s[i] != s[j];
        j--;
        return 0;
    }
    return 1;
}

//24
/*
Defina uma fun ̧c ̃ao int remRep (char x[]) que elimina de uma string todos os caracteres
que se repetem sucessivamente deixando l ́a apenas uma c ́opia. A fun ̧c ̃ao dever ́a retornar o
comprimento da string resultante. Assim, por exemplo, ao invocarmos a fun ̧c ̃ao com uma
vector contendo "aaabaaabbbaaa", o vector deve passar a conter a string "ababa" e a fun ̧c ̃ao
dever ́a retornar o valor 5.
*/
int remRep (char x[]) {
    int i;
    int j = 1;

    if (strlen(x) == 0) return 0;
    for(i = 1; x[i] != '\0'; i++) {
        if(x[i] != x[i-1]) {
            x[j] = x[i];
            j++;
        }
    }
    x[j] = '\0';
    return j;
}

//25
/*
Defina uma fun ̧c ̃ao int limpaEspacos (char t[]) que elimina repeti ̧c ̃oes sucessivas de espa ̧cos
por um  ́unico espa ̧co. A fun ̧c ̃ao deve retornar o comprimento da string resultante.
*/
int limpaEspacos(char t[]) {
    if (!(*t))
        return 0;
    int i, j = 1;
    for (i = 1; t[i] != '\0'; i++)
        if (!(isspace(t[i]) && isspace(t[i - 1]))) {
            t[j] = t[i];
            j++;
        }
    t[j] = '\0';
    return j;
}

//26
void insere(int v[], int N, int x) {
    int i = N;
    
    while (i > 0 && v[i - 1] > x) {
        v[i] = v[i - 1];
        i--;
    }
    
    v[i] = x; // Aqui o 'i' ainda existe e tem a posição correta
}

//27
void merge(int r[], int a[], int b[], int na, int nb) {
    int i = 0;
    int j = 0;
    int k = 0;

    // 1º Passo: Comparar as duas listas enquanto ambas tiverem elementos
    while (i < na && j < nb) {
        if (a[i] <= b[j]) {
            r[k] = a[i]; // Copia do vetor 'a'
            i++;         // Avança no vetor 'a'
        } else {
            r[k] = b[j]; // Copia do vetor 'b'
            j++;         // Avança no vetor 'b'
        }
        k++; // Avança sempre no vetor de destino 'r'
    }

    // 2º Passo: Se o vetor 'b' acabou primeiro, copiamos o que sobrou do 'a'
    while (i < na) {
        r[k] = a[i];
        i++;
        k++;
    }

    // 3º Passo: Se o vetor 'a' acabou primeiro, copiamos o que sobrou do 'b'
    while (j < nb) {
        r[k] = b[j];
        j++;
        k++;
    }
}

/*
28
Defina uma fun ̧c ̃ao int crescente (int a[], int i, int j) que testa se os elementos do
vector a, entre as posi ̧c ̃oes i e j (inclusiv ́e) est ̃ao ordenados por ordem crescente. A fun ̧c ̃ao
deve retornar 1 ou 0 consoante o vector esteja ou n ̃ao ordenado.
*/

int crescente (int a[], int i, int j) {
    for(i; i<j; i++) {
        if(a[i] > a[i+1]) return 0; // quando esta errado
    }
    return 1;
}

/*
29 Defina uma fun ̧c ̃ao int retiraNeg (int v[], int N) que retira os n ́umeros negativos de
um vector com N inteiros. A fun ̧c ̃ao deve retornar o n ́umero de elementos que n ̃ao foram
retirados.
*/
int retiraNeg (int v[], int N) {
    int i;
    int j = 0;

    for(i=0;i<N;i++){
        if(v[i] > 0) {
        v[j] = v[i];
        j++;
        }
    }
    v[j] = '\0';
    return j;
}

/*
30
Defina uma fun ̧c ̃ao int menosFreq (int v[], int N) que recebe um vector v com N ele-
mentos ordenado por ordem crescente e retorna o menos frequente dos elementos do
vector. Se houver mais do que um elemento nessas condi ̧c ̃oes deve retornar o que come ̧ca por
aparecer no  ́ındice mais baixo.
*/
int menosFreq(int v[], int N) {
    // 1. Proteger contra array vazio
    if (N <= 0) return -1; // Retorna -1 (ou outro valor de erro adequado)
    
    int freq = 1;
    int menosFreq = N + 1; // Iniciar com um valor superior ao máximo possível
    int elemento = v[0];
    
    // 2. Começar no índice 1 e comparar com o anterior para evitar sair do array
    for (int i = 1; i < N; i++) {
        if (v[i] == v[i-1]) {
            freq++;
        } else {
            // Quando a sequência muda, verificamos se é a menos frequente
            if (freq < menosFreq) {
                menosFreq = freq;
                elemento = v[i-1];
            }
            freq = 1; // Reset à frequência para o novo elemento
        }
    }
    
    // 3. Verificar a última sequência de elementos
    if (freq < menosFreq) {
        elemento = v[N-1];
    }
    
    return elemento;
}

/*
31 Defina uma fun ̧c ̃ao int maisFreq (int v[], int N) que recebe um vector v com N elemen-
tos ordenado por ordem crescente e retorna o mais frequente dos elementos do vector.
Se houver mais do que um elemento nessas condi ̧c ̃oes deve retornar o que come ̧ca por aparecer
no  ́ındice mais baixo.
*/
int maisFreq (int v[], int N) {
    int i;
    int freq = 1;
    int freqMax = 0;
    int elemento = v[0];

    for(i=1;i<N;i++) {
        if(v[i] == v[i-1]) {
         freq++;
    } else {
        if (freq > freqMax) {
            freqMax = freq;
            elemento = v[i-1];
            }
        freq = 1;
        }
    }

    if (freq > freqMax) {
        elemento = v[i-1];
    }
    
    return elemento;
}

/*
32) Defina uma fun ̧c ̃ao int maxCresc (int v[], int N) que calcula o comprimento da maior
sequˆencia crescente de elementos consecutivos num vector v com N elementos. Por exemplo
se o vector contiver 10 elementos pela seguinte ordem: 1, 2, 3, 2, 1, 4, 10, 12, 5, 4,
a fun ̧c ̃ao dever ́a retornar 4, correspondendo ao tamanho da sequˆencia 1, 4, 10, 12
*/
int maxCresc (int v[], int N) {
    int i;
    int freq = 1;
    int freqMax = 1;

    for(i=1;i<N;i++) {
        if(v[i] > v[i-1]){
            freq++;
        } else {
            if(freq > freqMax) {
                freqMax = freq;
                 }
        freq = 1;
            }
        }
    if (freq > freqMax) {
        freqMax = freq;
    }
    return freqMax;
}

/*
33. Defina uma fun ̧c ̃ao int elimRep (int v[], int n) que recebe um vector v com n inteiros e
elimina as repeti ̧c ̃oes. A fun ̧c ̃ao dever ́a retornar o n ́umero de elementos do vector resultante.
Por exemplo, se o vector v contiver nas suas primeiras 10 posi ̧c ̃oes os n ́umeros {1, 2, 3, 2,
1, 4, 2, 4, 5, 4}, a invoca ̧c ̃ao elimRep (v,10) dever ́a retornar 5 e colocar nas primeiras
5 posi ̧c ̃oes do vector os elementos {1,2,3,4,5}.
*/
//Auxiliar

int elem (int v[], int n, int x) {
    int i;

    for(i=0; i<n; i++) {
        if(v[i] == x) return 1;
    }
    return 0;
}

int elimRep (int v[], int n) {
    int i;
    int j = 1;

    for(i=1; i < n; i++)
    if(!elem(v,i,v[i])) {
        v[j] = v[i];
        j++;
    } 
    return j;
}

/*
34. Defina uma fun ̧c ̃ao int elimRepOrd (int v[], int n) que recebe um vector v com n in-
teiros ordenado por ordem crescente e elimina as repeti ̧c ̃oes. A fun ̧c ̃ao dever ́a retornar o
n ́umero de elementos do vector resultante.
*/
int elimRepOrd (int v[], int n) {
    int i;
    int j = 1;

    for(i=1;i<n;i++) {
        if(v[i] != v[i-1]) {
            v[j] = v[i];
            j++;
        }
    }
    return j;
}

/*
35. Defina uma fun ̧c ̃ao int comunsOrd (int a[], int na, int b[], int nb) que calcula quan-
tos elementos os vectores a (com na elementos) e b (com nb elementos) tˆem em comum. As-
suma que os vectores a e b est ̃ao ordenados por ordem crescente.
*/
int comunsOrd(int a[], int na, int b[], int nb) {
    int i = 0;
    int j = 0;
    int count = 0;

    // Enquanto não chegarmos ao fim de nenhum dos arrays
    while (i < na && j < nb) {
        if (a[i] == b[j]) {
            count++;
            i++; // Encontrou igual, avançamos os dois
            j++;
        } 
        else if (a[i] < b[j]) {
            i++; // O 'a' está atrasado, avançamos o 'a'
        } 
        else {
            j++; // O 'b' está atrasado, avançamos o 'b'
        }
    }
    
    return count;
}

/*
36. Defina uma fun ̧c ̃ao int comuns (int a[], int na, int b[], int nb) que calcula quantos
elementos os vectores a (com na elementos) e b (com nb elementos) tˆem em comum. Assuma
que os vectores a e b n ̃ao est ̃ao ordenados e defina a fun ̧c ̃ao sem alterar os vectores.
*/
// Verifica se x existe no array a[] de tamanho n
int elem1(int a[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (a[i] == x) return 1;
    }
    return 0;
}

// Conta quantos elementos distintos são comuns a a[] e b[]
int comuns(int a[], int na, int b[], int nb) {
    int count = 0;

    for (int i = 0; i < na; i++) {
        int jaContado = elem1(a, i, a[i]);  // a[i] já apareceu antes em a[]?
        int estaEmB   = elem1(b, nb, a[i]); // a[i] existe em b[]?

        if (!jaContado && estaEmB) {
            count++;
        }
    }

    return count;
}

/*
37. Defina uma fun ̧c ̃ao int minInd (int v[], int n) que, dado um vector v com n inteiros,
retorna o  ́ındice do menor elemento do vector.
*/
 int minInd (int v[], int n) {
    int i;
    int ind = 0;

    for(i=1;i<n;i++) {
        if(v[i] < v[ind]) {
            ind = i;
        }
    }
    return i;
}

/*
38. Defina uma fun ̧c ̃ao void somasAc (int v[], int Ac [], int N) que preenche o vector Ac
com as somas acumuladas do vector v. Por exemplo, na posi ̧c ̃ao Ac[3] deve ser calculado
como v[0]+v[1]+v[2]+v[3].
*/
void somasAc (int v[], int Ac[], int N) {
    if (N <= 0) return; // Como a função é void, usamos apenas 'return;' para sair

    Ac[0] = v[0];

    for(int i=1;i<N;i++) {
        if(Ac[i] = v[i] + Ac[i-1]);
    }
}

/*
39. Defina uma fun ̧c ̃ao int triSup (int N, float m [N][N]) que testa se uma matriz quadra-
da  ́e triangular superior, i.e., que todos os elementos abaixo da diagonal s ̃ao zeros.
*/
int triSup (int N, float m [N][N]){
    int i,j;
    for(i=0; i < N; i++){
        for(j=0; j < N; j++){
        if(i > j && m[i][j] != 0){ // é mais facil ver se sao diferente
            return 0;
        }
        }
    }
    return 1;
}

/*
40. Defina uma fun ̧c ̃ao void transposta (int N, float m [N][N]) que transforma uma ma-
triz na sua transposta
*/
void transposta (int N, float m [N][N]) {

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < i; j++) {
            if(i != j) {
                int temp = m[i][j];
                m[i][j] = m[j][i];
                m[j][i] = temp;
            }
        }
    }
}

/*
41. Defina uma fun ̧c ̃ao void addTo (int N, int M, int a [N][M], int b[N][M]) que adi-
ciona a segunda matriz `a primeira.
*/
void addTo(int N, int M, int a[N][M], int b[N][M]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            a[i][j] += b[i][j];
}

/*
42. Uma forma de representar conjuntos de  ́ındices consiste em usar um array de inteiros contendo
1 ou 0 consoante esse  ́ındice perten ̧ca ou n ̃ao ao conjunto. Assim o conjunto {1,4,7}seria
representado por um array em que as primeiras 8 posi ̧c ̃oes conteriam {0,1,0,0,1,0,0,1}.
Apresente uma defini ̧c ̃ao da fun ̧c ̃ao int unionSet (int N, int v1[N], int v2[N], int
r[N]) que coloca no array r o resultado da uni ̃ao dos conjuntos v1 e v2
*/
int unionSet(int N, int v1[N], int v2[N], int r[N]) {
    int i, cont = 0;
    for (i = 0; i < N; i++) {
        r[i] = (v1[i] || v2[i]);
        cont += r[i];
    }
    return cont;
}

/*
43. Uma forma de representar conjuntos de  ́ındices consiste em usar um array de inteiros contendo
1 ou 0 consoante esse  ́ındice perten ̧ca ou n ̃ao ao conjunto. Assim o conjunto {1,4,7}seria
representado por um array em que as primeiras 8 posi ̧c ̃oes conteriam {0,1,0,0,1,0,0,1}.
Apresente uma defini ̧c ̃ao da fun ̧c ̃ao int intersectSet (int N, int v1[N], int v2[N],
int r[N]) que coloca no array r o resultado da intersec ̧c ̃ao dos conjuntos v1 e v2.
*/
int intersectSet(int N, int v1[N], int v2[N], int r[N]) {
    int i, cont = 0;
    for (i = 0; i < N; i++) {
        r[i] = (v1[i] && v2[i]);
        cont += r[i];
    }
    return cont;
}

/*
44. Uma forma de representar multi-conjuntos de  ́ındices consiste em usar um array de inteiros
contendo em cada posi ̧c ̃ao o n ́umero de ocorrˆencias desse  ́ındice. Assim o multi-conjunto
{1,1,4,7,7,7}seria representado por um array em que as primeiras 8 posi ̧c ̃oes conteriam
{0,2,0,0,1,0,0,3}.
Apresente uma defini ̧c ̃ao da fun ̧c ̃ao int intersectMSet (int N, int v1[N], int v2[N],
int r[N]) que coloca no array r o resultado da intersec ̧c ̃ao dos multi-conjuntos v1 e v2.
*/
int intersectMSet (int N, int v1[N], int v2[N],int r[N]) {
    int count = 0;
    for(int i = 0; i < N; i++) {
        if( v1[i] < v2[i]){
            r[i] = v1[i];
        }
        else {
            r[i] = v2[i];
        }
        count += r[i]; 
    }
    return count;
}


/*
45. Uma forma de representar multi-conjuntos de  ́ındices consiste em usar um array de inteiros
contendo em cada posi ̧c ̃ao o n ́umero de ocorrˆencias desse  ́ındice. Assim o multi-conjunto
{1,1,4,7,7,7}seria representado por um array em que as primeiras 8 posi ̧c ̃oes conteriam
{0,2,0,0,1,0,0,3}
*/
int unionMSet(int N, int v1[N], int v2[N], int r[N]) {
    int count = 0;
    
    for (int i = 0; i < N; i++) {
        // Agora queremos o MAIOR número (o máximo)
        if (v1[i] > v2[i]) {
            r[i] = v1[i];
        } else {
            r[i] = v2[i];
        }
        
        // Continuamos a somar tudo para saber o tamanho total
        count += r[i]; 
    }
    
    return count;
}

/*
46. Uma forma de representar multi-conjuntos de  ́ındices consiste em usar um array de inteiros
contendo em cada posi ̧c ̃ao o n ́umero de ocorrˆencias desse  ́ındice. Assim o multi-conjunto
{1,1,4,7,7,7}seria representado por um array em que as primeiras 8 posi ̧c ̃oes conteriam
{0,2,0,0,1,0,0,3}.
Apresente uma defini ̧c ̃ao da fun ̧c ̃ao int cardinalMSet (int N, int v[N]) que calcula a
n ́umero de elementos do multi-conjunto v.
*/
int cardinalMSet(int N, int v[N]) {
    int cont = 0;
    for (int i = 0; i < N; i++)
        cont += v[i];
    return cont;
}

/*
47. Considere as seguintes defini ̧c ̃oes para representar as posi ̧c ̃oes e movimentos de um robot.
Defina a fun ̧c ̃ao Posicao posFinal (Posicao inicial, Movimento mov[], int N) que,
dada uma posi ̧c ̃ao inicial e um array com N movimentos, calcula a posi ̧c ̃ao final do robot
depois de efectuar essa sequˆencia de movimentos.
*/

typedef enum movimento {Norte, Oeste, Sul, Este}Movimento;
typedef struct posicao {
                int x, y;
            }Posicao;

Posicao posFinal(Posicao inicial, Movimento mov[], int N) {
    for (int i = 0; i < N; i++) {
        switch (mov[i]) {
            case Norte:
                inicial.y++;
                break;
            case Sul:
                inicial.y--;
                break;
            case Oeste:
                inicial.x--;
                break;
            case Este:
                inicial.x++;
                break;
            default:
                break;
        }
    }
    return inicial;
}

/*
48. Considere as seguintes defini ̧c ̃oes para representar as posi ̧c ̃oes e movimentos de um robot.
Defina a fun ̧c ̃ao int caminho (Posicao inicial, Posicao final, Movimento mov[], int
N) que, dadas as posi ̧c ̃oes inicial e final do robot, preenche o array com os movimentos sufi-
cientes para que o robot passe de uma posi ̧c ̃ao para a outra.
A fun ̧c ̃ao dever ́a preencher no m ́aximo N elementos do array e retornar o n ́umero de elementos
preenchidos. Se n ̃ao for poss ́ıvel atingir a posi ̧c ̃ao final com N movimentos, a fun ̧c ̃ao dever ́a
retornar um n ́umero negativo.
*/
int caminho(Posicao inicial, Posicao final, Movimento mov[], int N) {
    int i;
    for (i = 0; i < N && (inicial.x != final.x || inicial.y != final.y); i++) {
        if (inicial.x > final.x) {
            mov[i] = Oeste;
            inicial.x--;
        } else if (inicial.x < final.x) {
            mov[i] = Este;
            inicial.x++;
        } else if (inicial.y > final.y) {
            mov[i] = Sul;
            inicial.y--;
        } else {
            mov[i] = Norte;
            inicial.y++;
        }
    }
    if (inicial.x != final.x || inicial.y != final.y) return -1;
    else return i;
}

/*
49. Considere o seguinte tipo para representar a posi ̧c ̃ao de um robot numa grelha.
Defina a fun ̧c ̃ao int maisCentral (Posicao pos[], int N) que, dado um array com N
posi ̧c ̃oes, determina o  ́ındice da posi ̧c ̃ao que est ́a mais perto da origem (note que as coor-
denadas de cada ponto s ̃ao n ́umeros inteiros).
*/

// AUXILIAR
float dist(Posicao pos) { 
    return sqrt(pow(pos.x, 2) + pow(pos.y, 2)); }

int maisCentral(Posicao pos[], int N) {
    int i = 1, acc = 0;
    float d = dist(pos[0]);
    
    // Abrir chavetas para incluir o if e o i++ no ciclo!
    while (i < N) { 
        if (dist(pos[i]) < d) {
            d = dist(pos[i]);
            acc = i;
        }
        i++; // O 'i' avança no final de cada verificação
    }
    
    return acc;
}



/*
50. Considere o seguinte tipo para representar a posi ̧c ̃ao de um robot numa grelha.
Defina a fun ̧c ̃ao int vizinhos (Posicao p, Posicao pos[], int N) que, dada uma posi ̧c ̃ao
e um array com N posi ̧c ̃oes, calcula quantas dessas posi ̧c ̃oes s ̃ao adjacentes `a posi ̧c ̃ao dada.
*/
// AUXILIAR
int manDist(int x, int y, int x0, int y0) { return abs(x - x0) + abs(y - y0); }

int vizinhos(Posicao p, Posicao pos[], int N) {
    int i = 0, cont = 0;
    
    while (i < N) {
        // Primeiro verificamos a posição atual
        if (manDist(pos[i].x, pos[i].y, p.x, p.y) == 1) {
            cont++;
        }
        // Só depois avançamos para a próxima!
        i++; 
    }
    
    return cont;
}

int main() {
    //maior();
    //media();
    //segundoMaior();
    //unsigned int num3 = 1048576;
    //printf("%d\n", qDig(num3));
    
    return 0;
}