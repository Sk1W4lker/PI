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
2. Defina uma fun ̧c ̃ao int retiraVogaisRep (char *s) que remove de uma string todas as repe-
ti ̧c ̃oes consecutivas de vogais. A fun ̧c ̃ao dever ́a retornar o n ́umero de vogas removidas. Por e-
xemplo, se a string a == "Estaa e umaa string coom duuuplicadoos", depois de invocarmos
retiraVogaisRep a, a string a dever ́a ter o valor "Esta e uma string com duplicados"
*/

//Array auxiliar
int retiraVogaisRep (char *s) {
    int i, j = 0;
    int len = strlen(s);
    int aux[len + 1];
    int count = 0;

    for(i = 0; s[i] != '\0'; i++) {
        if(eVogal(s[i]) && s[i] == s[i+1]) {
            count++;
        } else {
            aux[j] = s[i];
            j++;
        }
    }
    
    aux[j] = '\0';
    strcpy(s, aux);
    return count;
}

//Sem array auxiliar
int retiraVogaisRep (char *s) {
    int i, j = 0;
    int count = 0;

    // Se a string for vazia, não há nada a fazer
    if (s[0] == '\0') return 0;

    for (i = 0; s[i] != '\0'; i++) {
        // Se a letra atual é vogal E é igual à PRÓXIMA
        if (eVogal(s[i]) && s[i] == s[i+1]) {
            count++; // Saltamos esta letra (o j não avança)
        } else {
            // Se não é repetida (ou se é a última do bloco repetido)
            // Escrevemos a letra atual na posição de escrita 'j'
            s[j] = s[i];
            j++;
        }
    }

    // Colocamos o terminador no novo fim da string
    s[j] = '\0';

    return count;
}

/*
3. Defina uma fun ̧c ̃ao int duplicaVogais (char *s) que duplica todas as vogais de uma string.
A fun ̧c ̃ao deve retornar o n ́umero de caracteres acrescentados. Assuma que o array recebido
como argumento tem capacidade para armazenar o resultado pretendido
*/

//Com array auxiliar
int duplicaVogais (char *s) {
    int i, j = 0;
    int len = strlen(s);
    int aux[(len *2) + 1];
    int count = 0;

    for(i = 0; s[i] != '\0'; i++) {
        if(eVogal(s[i])) {
            aux[j] = s[i];
            aux[j+1] = s[i];
            j += 2;
            count++;
        } else {
            aux[j] = s[i];
            j++;
        }
    }
    
    aux[j] = '\0';
    strcpy(s, aux);
    return count;
}

//Sem array auxiliar
int duplicaVogais (char *s) {
    int i, count = 0;
    int len = strlen(s);

    // 1. Contar vogais para saber o espaço extra necessário
    for (i = 0; s[i] != '\0'; i++) {
        if (eVogal(s[i])) count++;
    }

    // O novo índice de escrita começa no novo fim da string
    int j = len + count; 
    s[j] = '\0'; // Colocamos o novo terminador
    j--;         // Apontamos para a última posição de escrita real

    // 2. Percorrer a string original de trás para a frente
    for (i = len - 1; i >= 0; i--) {
        if (eVogal(s[i])) {
            // Se for vogal, escrevemos duas vezes
            s[j] = s[i];
            s[j - 1] = s[i];
            j -= 2;
        } else {
            // Se for consoante, escrevemos apenas uma vez
            s[j] = s[i];
            j--;
        }
    }

    return count;
}

//Arrays ordenados

//1)
int ordenado (int v[], int N) {
    int i;

    for(i=1;i<N;i++) {
        if(v[i] < v[i-1]) {
            return 0;
        }
    }
    return 1;
}

//2)
void merge (int a[], int na, int b[], int nb, int r[]) {
    int i = 0, j = 0, k = 0;

    while(i < na && j < nb) {
        if(a[i] < b[i]) {
            r[k] = a[i];
            i++;
        } else {
            r[k] = b[j];
            j++;
        }
        k++;
    }

    while(i < na) {
        r[k] = a[i];
        i++;
        k++;
    } 

    while(j < nb) {
        r[k] = b[j];
        i++;
        k++;
    }
}

//3
int partition (int v[], int N, int x) {
    int aux[N];
    int i, j = 0;
    int menores = 0;

    // 1. Primeira passagem: copiar os menores ou iguais a x
    for (i = 0; i < N; i++) {
        if (v[i] <= x) {
            aux[j] = v[i];
            j++;
            menores++;
        }
    }

    // 2. Segunda passagem: copiar os restantes (maiores que x)
    for (i = 0; i < N; i++) {
        if (v[i] > x) {
            aux[j] = v[i];
            j++;
        }
    }

    // 3. Copiar tudo de volta para o array original v
    for (i = 0; i < N; i++) {
        v[i] = aux[i];
    }

    return menores; // Retorna quantos elementos ficaram na primeira parte
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