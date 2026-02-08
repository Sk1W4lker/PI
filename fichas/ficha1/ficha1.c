#include <stdio.h>

/* 
Exercício 1 

1)12 16
2)0 1 (uninitialized variable y)
3)A 65
  B 66 2 50
  b 98
4)100 200
5)128 -99
  129 -99

--------------------------------------------------------

Exercicio 2

1) a)3 5
   b)66
   c)... overflow
   d)_#_#_#_#_#_#_#_#_#_#
   e)abcdefg
     bcdefg
     cdefg
     defg
     efg
     fg
     g

   f)
     1
     01
     11
     001
     101
     011
     111
     0001
     1001
     0101
     1101
     0011
     1011
     0111 
     1111

*/

// 2)

void quadrado(int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            putchar('#');
        }
        putchar('\n');
    }
}

// 3)

void xadrez(int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if((i + j) % 2) putchar('_');
            else putchar('#');
        }
        putchar('\n');
    }
}
//3
void trianguloVertical(int dimensao) {
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

void trianguloHorizontal(int n) {
    for (int i = 1; i <= n; i++) {

        int espacos = n - i;
        int hashes  = 2 * i - 1;

        for (int s = 0; s < espacos; s++)
            putchar(' ');

        for (int h = 0; h < hashes; h++)
            putchar('#');

        putchar('\n');
    }
}



//4
void circulo(int r) {
    int count = 0;

    for (int y = r; y >= -r; y--) {
        for (int x = -r; x <= r; x++) {

            if (x*x + y*y <= r*r) {
                putchar('#');
                count++;
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}

int main() {
  quadrado(5);
  xadrez(5);
  trianguloVertical(5);
  trianguloHorizontal(5);

  return 0;
}