#include <stdio.h>

//Qual é o máximo divisor do número 19875920 que também é primo?

int main() {
    long int n = 18863598;
    long int maior_primo = 0;

    for(long int i = 2; i * i <= n; i++) {
        while(n % i == 0) {
            maior_primo = i;
            n = n / i;
        }
    }

    // se no final n > 1, então n também é primo
    if(n > 1) {
        maior_primo = n;
    }

    printf("Maior divisor primo: %ld\n", maior_primo);

    return 0;
}

//Um número natural n maior que 1 diz-se primo se tiver exatamente dois divisores positivos distintos: 1 e n.
//Quantos números primos existem no intervalo [4037644,4137659]?
