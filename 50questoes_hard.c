//4, 5, 10,14,18,20,33,36,39,41,42,43,44,45,47,48,49,50

//4
int bitsUm (unsigned int n) {
    if(n > 0) {
        return ((n & 1) + bitsUm(n >> 1));
    } else {
        return 0;
    }

}

//5
int trailingZ(unsigned int n) { 
    if (n == 0) return 8;

    if (n & 1) {
        return 0;
    } else {
        return 1 + trailingZ(n >> 1);
    }
}

//10
*strstr (char s1[], char s2[]) {
    int i, j;

    for(i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
        if(s1[i+j] != s2[j]) {
            break;
        } 
    }
    if(s2[j] == '\0') {
        return &s1[i];
        }
    }
    return NULL;
}

//14

int contaChar(char s[], char x) {
    int i;
    int count = 0;

    for(i=0; s[i] != '\0'; i++) {
        if(s[i] == x) count++;
    }
}

char charMaisfreq (char s[]) {

    int i;
    int contagem = countChar(s,s[0]);
    char elemento = s[0];

    for(i=0; s[i] != '\0'; i++){
        int contagemAtual = countChar(s,s[i]);

        if (contagemAtual > contagem) {
        contagem = contagemAtual;
        elemento = s[i];
        }
    }
    return elemento;
}

//18
int maiorSufixo (char s1 [], char s2 []) {
    int i, j;
    int count = 0;

    for(i=0; s1[i] != '\0'; i++);
    for(j=0; s2[j] != '\0'; j++);

    i--;
    j--;

    while(i >= 0 && j >= 0 && s1[i] == s2[j]) {
        count++;
        i--;
        j--;
    }

    return count;
}

//20 -----
int contaPal (char s[]) {
    int pal = 1; //Estamos numa palavra mas não contou ainda
    int count = 0;

    for(int i=0; s[i] != '\0'; i++) {
        if(isspace(s[i])) {
            pal = 0; //Encontramos um espaço
        }
        else if (pal == 0) pal = 1; //Se tinha um espaço na iteração passada passa a ter uma palavra agora.
        if(pal > 0) { 
            count++;
            pal = -1; //Reseta a condição para não adicionar mais quando são duas ou mais letras juntas e contou como palavra.
        }
    }
    return count;
}

//33
int elem (int v[], int n, int x) {
    int i;

    for(i = 0; i < n; i++) {
        if(v[i] == x) return 1;
    }
    return 0;
}

int elimRep (int v[], int n) {
    int i, j;

    for(i = 0; i < n; i++) {
        if(!elem(v, n, v[i])) {
            v[j] = v[i];
            j++;
        }
    }
    return j;
}

//35
int comunsOrd (int a[], int na, int b[], int nb) {
    int i = 0;
    int j = 0;
    int count = 0;

    while (i < na && j < nb) {
        if(a[i] == a[j]) {
            count++;
            i++;
            j++;
        } else if (a[i] < b[j]) {
            i++;
        } else {
            j++;
        }
    }
    return count;
}

//36 ----
// Conta quantos elementos distintos são comuns a a[] e b[]
int comuns(int a[], int na, int b[], int nb) {
    int count = 0;

    for(int i = 0; i < na; i++) {
        int jaContado = elem(a, i, a[i]);
        int estaEmB = elem(b, nb, a[i]);

        if(!jaContado && estaEmB) {
            count++;
        }
    }
    count++;
}

//39
int triSup (int N, float m [N][N]) {
    int i, j;

    for(i=0; i < N; i++) {
        for(j=0; i < N; j++) {
            if(i > j && m[i][j] != 0) {
                return 0;
            } 
        }
    }
    return 1;
}

/*
| m[0][0] m[0][1] m[0][2] |
| m[1][0] m[1][1] m[1][2] |
| m[2][0] m[2][1] m[2][2] |
*/

//40
void transposta (int N, float m [N][N]) {
    int i;
    int j;
    int temp;

    for(i=0; i < N; i++) {
        for(j = 0; j < i; j++) { // Percorre apenas o triângulo inferior
        if(i != j) {
        temp = m[i][j];
        m[i][j] = m[j][i];
        m[j][i] = temp;
        }
    }
    }
}

//41
void addTo (int N, int M, int a [N][M], int b[N][M]) {

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            a[i][j] += b[i][j];
        }
    }
}

//42
int unionSet (int N, int v1[N], int v2[N], int r[N]) {
    int cont = 0;

    for(int i = 0; i < N; i++) {
        r[i] = (v1[i] || v2[i]);
        cont += r[i];
    }
    return cont;
}

//43
int intersectSet (int N, int v1[N], int v2[N], int r[N]) {
    int i;
    int count = 0;

    for(int i = 0; i < N; i++) {
        r[i] = (v1[i] && v2[i]);
        count += r[i];
    }
    return count;
}

//44
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
