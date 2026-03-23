#include <stdio.h>
#include <string.h>

//Diz se o caractere é vogal.
int eVogal(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
    }

//1 Defina uma fun¸c˜ao int contaVogais (char *s) que conta quantas vogais uma string tem.
int contaVogais (char *s) {
    int count = 0;

    for(int i = 0; s[i] != '\0'; i++) {
        if(s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U' ||
        s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
        count ++;
        }
    }
    return count;
}

int contaVogais2 (char *s) {
    int count = 0;

    for(int i = 0; s[i] != '\0'; i++) {
        if (eVogal(s[i])) count++; 
    }
    return count; 
}

/*
Defina uma fun¸c˜ao int retiraVogaisRep (char *s) que remove de uma string todas as repe-
tições consecutivas de vogais. A fun¸c˜ao dever´a retornar o n´umero de vogas removidas. 
Por exemplo, se a string a == "Estaa e umaa string coom duuuplicadoos", depois de invocarmos
retiraVogaisRep a, a string a dever´a ter o valor "Esta e uma string com duplicados".

• Para evitar fazer muitos deslocamentos de caracteres, apresente uma defini¸c˜ao que usa um
array auxiliar onde a string resultante será construída. No final ter´a que copiar essa string
de volta para o array argumento.

• Altere a fun¸c˜ao que definiu acima de forma a não precisar de usar o array auxiliar.
*/
int retiraVogaisRep(char *s) {
    if(s[0] == '\0') return 0;

    int j = 1; //Começa no segundo carater
    int removidos = 0;

    for (int i = 1; s[i] != '\0'; i++) {
        // Se for uma vogal e for igual à anterior, nós "pulamos" (removemos)
        if (eVogal(s[i]) && s[i] == s[i-1]) {
            removidos++;
        } else {
            s[j] = s[i];
            j++;
        }
    }
    s[j] = '\0'; // Finaliza a nova string

    return removidos;
}

//Sem copiar
int retiraVogaisRep2(char *s) {
    char aux[strlen(s) + 1]; // Array auxiliar
    int j = 1;         // Índice para o aux
    int removidos = 0;

    for (int i = 1; s[i] != '\0'; i++) {
        // Se for uma vogal e for igual à anterior, nós "pulamos" (removemos)
        if (eVogal(s[i]) && s[i] == s[i-1]) {
            removidos++;
        } else {
            aux[j++] = s[i];
        }
    }
    aux[j] = '\0'; // Finaliza a nova string

    strcpy(s, aux); // Copia de volta para a original
    return removidos;
}

int main() {
    char texto[] = "Programacaao Imperativa";
    
    int total = contaVogais(texto);
    int total2 = contaVogais2(texto);
    int remove = retiraVogaisRep2(texto);

    char a = 'a';
    printf("%d\n", eVogal(a));
    
    printf("Numero de vogais: %d\n", total);
    printf("Numero de vogais: %d\n", total2);
    printf("Numero de vogais retiradas: %d\n", remove);
    
    return 0;
}