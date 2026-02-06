#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main(void)
{
  int nota = 0;
 
  srand(time(NULL));
  nota = 8 + rand() % 11; //restos de 11 [1,10]
 
  printf("Eu vou tirar boa nota a PI: %d\n", nota);
  return 0;
}

/*
- um compilador é um programa que transforma código-fonte em ficheiros executáveis (programas);
- exemplos de compiladores são o gcc ou clang;
- gcc -Wall -o primeiro primeiro.c
- ./primeiro
*/
