#include <stdio.h>
/*
int x = 3, y = 5;
swapM (&x, &y);
printf ("%d %d\n", x, y);

2. Defina uma fun¸c˜ao void swapM (int *x, int *y) que
troca o valor de duas vari´aveis. Por exemplo, o c´odigo ao
lado dever´a imprimir no ecran 5 3
*/
void swapM (int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

//3. Defina uma funcao void swap (int v[], int i, int j) que troca o valor das posicoes i e j do vector v.
void swap (int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

//4. Defina umafun¸c˜ao int soma (int v[], int N) que calcula a soma dos elementos de um vector v com N inteiros
int soma (int v[], int N) {
    int sum = 0;

    for(int i=0; i<N-1; i++) {
        sum += v[i]; //sum = v[i] + sum
    }
    return sum;
}

//5. Defina uma fun¸c˜ao void inverteArray (int v[], int N) que inverte um array. Escreva duas
//vers˜oes, cada uma usando uma das fun¸c˜oes das al´ıneas anteriores.
void inverteArray (int v[], int N){
    for (int i = 0; i < N/2; i++) {
        //swap(v, i, N-1-i);
        swapM(&v[i], &v[N-i-1]);
    }
}

//6. Defina uma fun¸c˜ao int maximum (int v[], int N, int *m) que coloca em *m o maior dos elementos do vector v.
int maximum (int v[], int N, int *m) {
    if (N <= 0) return 1;
    else {
        *m = v[0];

        for(int i=0; i < N; i++) {
            if (v[i] > *m) *m = v[i];
        }
    }
    return 0;
} 

/*
7. Defina uma fun¸c˜ao void quadrados (int q[], int N) que preenche o vector q com os quadra-
dos dos primeiros N n´umeros naturais ({0,1,4,9,...}.
Note que, uma vez que (a + 1)2 = a2 + (2 ∗ a + 1) esta fun¸c˜ao n˜ao precisa de calcular o quadrado
de nenhum dos n´umeros explicitamente.
*/
void quadrados (int q[], int N) {
    for(int i = 0; i < N; i++) {
        q[i] = (i*i) + (2* i + 1);
    }
}

/*
8.
O triˆangulo de Pascal ´e uma forma de calcular os
coeficientes da expans˜ao do bin´omio de Newton.
Ao lado relembramos as 5 primeiras linhas.
Note que a linha n do triˆangulo tem n elementos
e que a linha n + 1 pode ser obtida a partir da
linha n usando o seguinte processo:

• acrescenta-se um 1 no final, i.e., coloca-se 1 na posi¸c˜ao n.
• para todos os elementos (desde n-1 at´e 1, por esta ordem) substitui-se o elemento nessa
posi¸c˜ao pela sua soma com o que est´a na posi¸c˜ao anterior.
*/
void pascal(int v[], int N){
    if(N==1) v[0] = 1;
    else {
        int ant[N-1];
        pascal(ant,N-1);

        v[0] = 1;
        v[N-1] = 1;

        for(int i = 1; i < N-1; i++) {
            v[i] = ant[i] + ant[i-1];
        }
    }
}

/*
(b) Adapte a funcao que definiu atras para, em vez de preencher um array com a linha N do
triangulo, escreva no ecran as N primeiras linhas do triangulo.
*/
void imprimePascal(int N) {
    int v[N];

    for(int n = 1; n <= N; n++) {
        
        v[N-1] = 1;

        for(int i = n-2; i > 0; i--) {
            v[i] = v[i] + v[i-1];
        }

        for(int i = 0; i < n; i++) {
            printf("%d", v[i]);
        }
        printf("\n");
    }
}

void dumpV(int v[], int N) {
    printf("[");
    for (int i = 0; i < N; i++)
        printf("%2d ", v[i]);
    printf("]\n");
}

int main() {
    int x = 3, y = 5;
    int max;
    int q[10];
    int v[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    inverteArray (v,10);
    dumpV (v,10);

    int z = soma (v,10);
    printf("%d\n", z);

    swapM (&x, &y);
    printf ("x = %d y = %d\n", x, y);

    (maximum(v, 10, &max) == 0);
    printf("Maximo = %d\n", max);
    
    swap (v, 0, 9);
    printf ("%d %d\n", v[0], v[9]);

    quadrados(q, 10);
    printf("Quadrados:\n");
    dumpV(q, 10);
}