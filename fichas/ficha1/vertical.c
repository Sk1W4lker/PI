#include <stdio.h>

void triangulo(int dimensao) {
    int i, j;

    for(i=0; i < dimensao ; i++){
        for(j=0; j <= i; j++) {
            putchar('#');
        }
        putchar('\n');
    }
    
    for (i=dimensao-1; i > 0; i--) {
        for(j=0; j < i; j++) {
        putchar('#');
    }
    putchar('\n');
    }
}
