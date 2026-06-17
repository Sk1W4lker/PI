#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Árvores Binárias - Structs

typedef struct ABin_nodo {
 int valor;
 struct ABin_nodo *esq, *dir;
} *ABin;

// Árvores Binárias - Teórica

// Uma árvore binária é uma estrutura de dados em que cada nó pode ter
// (até) dois "filhos": um à esquerda e outro à direita.
//
// Ao contrário das listas ligadas, que avançam sempre numa única direcção,
// as árvores permitem organizar a informação de forma hierárquica.
//
// As árvores aparecem em muitos contextos:
// - sistemas de ficheiros e pastas
// - expressão aritméticas
// - dicionários e tabelas de pesquisa
// - estruturas internas de compiladores e bases de dados
//
// Uma das grandes vantagens das árvores é que várias operações podem ser
// feitas de forma mais eficiente do que em listas ligadas, desde que a
// árvore esteja razoavelmente equilibrada. Por exemplo, procurar um valor
// pode obrigar a visitar muito menos nós.
//
// Além disso, as árvores são um excelente exemplo de estrutura recursiva:
// cada árvore é formada por uma raiz e por duas subárvores, que são também
// elas árvores. Por isso, muitas funções sobre árvores escrevem-se de forma
// natural com recursão.

// Árvore binária: cada nó guarda um valor e dois apontadores,
// um para a subárvore esquerda e outro para a subárvore direita.

// Cria uma nova raiz com valor x e com as subárvores 'e' e 'd'.
ABin mkroot(int x, ABin e, ABin d) {
  ABin new = malloc(sizeof(struct ABin_nodo));
  if(new == NULL) { 
    return NULL; 
  }

  new->valor = x;
  new->esq = e;
  new->dir = d;
  return new;
}

#if 0
 Constrói uma árvore (para a esquerda).

 Exemplo para v = [10, 20, 30, 40]:

           40
          /  \
         30  NULL
        /  \
       20  NULL
      /  \
     10  NULL
    /  \
 NULL  NULL

 Esta versão é útil para contrastar com a construção balanceada.
#endif

// A seguinte função calcula o número de elementos (nós) de uma árvore
int size(ABin a) {
  if(a == NULL) { 
    return 0; 
  }

  return 1 + size(a->esq) + size(a->dir);
}

//Calcula a profundidade (altura) da função:
int depth(ABin a) {
  int p_esq;
  int p_dir;

  if(a == NULL) { 
    return 0; 
  }

  p_esq = depth(a->esq);
  p_dir = depth(a->dir);

  if(p_esq > p_dir) { 
    return 1 + p_esq; 
  } else { 
    return 1 + p_dir; 
  }
}

// Travessias (InOrder, PreOrder, PostOrder)

// InOrder: esquerda, raiz, direita.
void print_in_order(ABin a) {
  if(a == NULL) {
     return; 
  }

  print_in_order(a->esq);
  printf("%d ", a->valor);
  print_in_order(a->dir);
  
  return;
}

// PreOrder: raiz, esquerda, direita.
void print_pre_order(ABin a) {
  if(a == NULL) { 
    return; 
  }
  
  printf("%d ", a->valor);
  print_pre_order(a->esq);
  print_pre_order(a->dir);
}

// PosOrder: esquerda, direita, raiz.
void print_post_order(ABin a) {
  if(a == NULL) { 
    return; 
  }

  print_post_order(a->esq);
  print_post_order(a->dir);
  printf("%d ", a->valor);
}

// Libertar Árvores

// Liberta toda a memória ocupada pela árvore.
void free_abin(ABin a) {
  if(a == NULL) { 
    return; 
  }

  free_abin(a->esq);
  free_abin(a->dir);
  free(a);
}

// Procurar na Árvore

// Pesquisa exaustiva; recursividade.
ABin procura(int x, ABin a) {
  ABin r;

  if(a == NULL) return NULL;
  if(a->valor == x) return a;

  r = procura(x, a->esq);
  if(r == NULL) return procura(x, a->dir);

  return r;
}

//Árvore Binária de Procura : recursividade.
ABin procuraBST(int x, ABin a) {
  if(a == NULL) return NULL;
  if(a->valor == x) return a;

  if(a->valor > x) return procuraBST(x, a->esq);
  else return procuraBST(x, a->dir);
}

//Árvore Binária de Procura : iterativa
ABin procuraBST_I(int x, ABin a) {

  while(a != NULL && a->valor != x) {
    if(a->valor > x) {
        a = a->esq;
    } else {
        a = a->dir;
    }
    return a;
    }
}

// Inserir
ABin insert(int x, ABin a) {
  ABin atual = a;
  ABin anterior = NULL;
  ABin nova;

  while(atual != NULL) {
    anterior = atual;
    if(atual->valor == x) return a; //Já esta na árvore.

    if(atual->valor > x)
      atual = atual->esq;
    else
      atual = atual->dir;
  }

  nova = malloc(sizeof(struct ABin_nodo)); 

  if(anterior == NULL) {
    a = nova; // prev. vazia (se ant é NULL então não entrou no ciclo)
  } else if(anterior->valor > x) {
    anterior->esq = nova;
  } else {
    anterior->dir = nova;
  }
  return a;
}

//Remoção em Árvores Binárias de Procura
// Casos:
// 1) nó folha
// 2) nó com um filho
// 3) nó com dois filhos
// no caso 3, substituímos pelo menor valor da subárvore direita

//Calcula o menor número - Auxiliar
int min_bst(ABin a) {
  while(a->esq != NULL) { 
    a = a->esq; 
  }

  return a->valor;
}

ABin remove_bst(int x, ABin a) {
  int m;
  ABin aux;

  if(a == NULL) { 
    return NULL; 
  }

  if(x < a->valor) {
    a->esq = remove_bst(x, a->esq);
    return a;
  }

  if(x > a->valor) {
    a->dir = remove_bst(x, a->dir);
    return a;
  }

  // chegámos ao nó a remover
  // caso 1: folha
  if(a->esq == NULL && a->dir == NULL) {
    free(a);
    return NULL;
  }

  // caso 2a: só tem filho à direita
  if(a->esq == NULL) {
    aux = a->dir;
    free(a);
    return aux;
  }

  // caso 2b: só tem filho à esquerda
  if(a->dir == NULL) {
    aux = a->esq;
    free(a);
    return aux;
  }
}
  // Ficha 9 e 10 de Árvores Binárias.

//1 a) - Calcula Altura
//Calcula a altura de uma  ́arvore.
int altura1(ABin a) {
    if(a == NULL) return 0;

    int altDir = altura1(a->dir);
    int altEsq = altura1(a->esq);

    if(altEsq > altDir) {
        return 1 + altEsq;
    } else {
        return 1 + altDir;
    }
}

//1 b) - Calcula o número de folhas (nodos cujas sub-́arvores são ambas vazias).
int nFolhas (ABin a) {
    if(a == NULL) return 0;

    if(a->esq == NULL && a->dir == NULL) return 1;

    return nFolhas(a->esq) + nFolhas(a->dir);
}

//1 c) - Calcula o nodo mais a esquerda.
ABin maisEsquerda (ABin a) {
  if(a == NULL) return NULL;

  while(a->esq != NULL) {
    a = a->esq;
  }
  return a;
}

//1 d) - escreve no ecran os elementos da  ́arvore que est ̃ao ao n ́ıvel l
void imprimeNivel (ABin a, int l) {
  if(a == NULL) return;

  if(l == 0) {
    printf("%d", a->valor);
    return;
  }
  imprimeNivel(a->esq,l-1);
  imprimeNivel(a->dir,l-1);
}

//1 e) testa se x esta na árvore
int procuraE (ABin a, int x) {
  if(a == NULL) return 0;

  if(a->valor == x) return 1;

  return(procuraE(a->esq, x) || procuraE(a->dir,x));
}

//2 f) procura um elemento numa  ́arvore. A fun ̧c ̃ao dever ́a retornar o endere ̧co da c ́elula onde o elemento ocorre ou NULL caso o ele-
//mento n ̃ao exista na  ́arvore.
struct nodo *procura (ABin a, int x) {

  while(a != NULL) {

    if(a->valor == x) return a;

    if(x < a->valor) {
      a = a->esq;
    } else {
      a = a->dir;
    }
  }
} 

//ou com recursividade
struct nodo *procura1 (ABin a, int x){
    if(a == NULL) return NULL;

    if(a->valor == x) return a;

    if(x < a->valor) {
        return procura1(a->esq, x);
    } else {
        return procura1(a->dir, x);
    }
}

//2 g) int nivel (ABin a, int x) que calcula o n ́ıvel a que o elemento ocorre na  ́arvore 
int nivel (ABin a, int x) {
    int count = 1; 

    while (a != NULL) {
        if (a->valor == x) return count;

        if (x < a->valor) {
            a = a->esq;
        } else {
            a = a->dir;
        }
        count++; 
    }
    return 0; 
}

//3 h) imprime no ecran, por ordem crescente, todos os elementos da  ́arvore que s ̃ao (estritamente) menores do que um dado valor.
void imprimeAte (ABin a, int x) {
    ABin atual = a;
    ABin pilha[100];
    int topo = 0;

    while (atual != NULL || topo > 0) {
    //Vai guardando todos os numeros até chegar ao menor.
    while(a != NULL || topo > 0) {
      pilha[topo] = atual;
      topo++;
      atual = atual->esq;
    }


    topo--; //Passa a apontar pro ultimo elemento.
    atual = pilha[topo]; //Coloca o elemento no atual.

    if(a->valor == x) {
      return; //Acaba
    }
    printf("%d ", atual->valor);

    atual = atual->dir;
  }
}

//ou usando recursividade
void imprimeAte (ABin a, int x){
    if(a == NULL) return; 

    imprimeAte(a->esq, x);
    
    if(a->valor < x) {
        printf("%d ", a->valor);
        imprimeAte(a->dir, x);
    }
}



//Árvores Binárias - Testes e Recursos

//Lista ligada auxiliar
typedef struct LInt_nodo {
    int valor;
    struct LInt_nodo *prox;
} *LInt;    

// [Recurso 2022] Apaga n nodos de uma árvore binária. Devolve o número de nós apagados.
int apaga (ABin a, int n) {
    int apagados = 0;

    if(a == NULL || n <= 0) return 0;

    apagados += apaga(a->esq, n-1);
    apagados += apaga(a->dir, n-1);

    if(apagados < n) {
        free(a);
        apagados++;
    }

    return apagados;
}

// [Teste 2022] dada uma árvore binária de procura a e um valor x, devolve uma lista com todos os
// valores desde a raiz até x
LInt caminho(ABin a, int x) {
    if(a == NULL) return NULL;

    LInt novo = malloc(sizeof(struct LInt_nodo));
    novo->valor = a->valor;

    if(a->valor == x) {
        novo->prox = NULL;
        return novo;
    }

    if(a->valor < x) {
        novo->prox = caminho(a->esq, x);
    } else {
        novo->prox = caminho(a->dir, x);
    }

    //Se devolveu NULL é porque não encontrou.
    if(novo->prox == NULL) {
        free(novo);
        return NULL;
    }

    return novo;
}

/*[Exame 2023] Dada uma string com uma string com uma travessia pré-order de uma árvore de dígitos,
onde os apontadores nulos aparecem marcados com um '*', reconstrói a árvore original. Por exemplo, se a string for "34**52**5*6**" deverá ser
devolvida a seguinte árvore.*/

ABin reconstroi(char s[]) {

    if(s[0] == '\0') {
        return NULL;
    }

    char c = s[0];

    int i = 0;
    
    while(s[i] != '\0') {
        // Vamos puxar todas as letras uma posição para a esquerda.
        s[i] = s[i+1];
        i++;
    }

    if(c == "*") return NULL;

    ABin nova = malloc(sizeof(struct ABin_nodo));
    nova->valor = c - '0'; //Transforma letra em número.
    nova->esq = reconstroi(s);
    nova->dir = reconstroi(s);

    return nova;
}

/*
[Teste 2023] Apresente uma definição da função int depth(ABin a, int x) que
devolve o menor nível a que um elemento x se encontra na árvore (ou -1
se x não se encontra na árvore). Considere a definição usual do tipo ABin.
Considere ainda que a raiz se encontra no nível 0
*/

int depth(ABin a, int x) {
    int count = 1;

    while(a != NULL) {

    if(x == a->valor) {
        return count;
    }

    if(x < a->valor) {
        a = a->esq;
    } else {
        a = a->dir;
    }
    count++;
    }

    return 0;
}

/*[Exame 2024] testa os valores no nível n de uma árvore são iguais (se não houver nenhum
nodo a esse nível a função deve retornar verdadeiro).
*/
int todosIguaisAux(ABin a, int n, int *primeiro_valor) {
    if (a == NULL) {
        return 1;
    }

    if (n == 0) {
        // Se for o PRIMEIRO nó que encontramos neste nível
        if (*primeiro_valor == -1) {
            *primeiro_valor = a->valor; // Guardamos o valor dele como padrão
            return 1;
        } 
        // Se já não for o primeiro, comparamos com o padrão
        else {
            return (a->valor == *primeiro_valor);
        }
    }

    // SE AINDA NÃO CHEGÁMOS AO NÍVEL N, continuamos a descer (n - 1)
    // Primeiro tentamos o lado esquerdo
    int esq_ok = todosIguaisAux(a->esq, n - 1, primeiro_valor);
    
    // Se a esquerda já falhou (devolveu 0), não vale a pena perder tempo na direita!
    if (!esq_ok) return 0;

    // Se a esquerda passou, vamos testar a direita
    return todosIguaisAux(a->dir, n - 1, primeiro_valor);
}

int todosIguais(ABin a, int n) {
    int referencia = -1; // -1 vai significar "ainda não encontrámos ninguém no nível n"
    return todosIguaisAux(a, n, &referencia);
}

/*
[Teste 24] Devolve a folha mais à esquerda de uma árvore (ou NULL se não tem nenhuma folha). 
Uma folha é um nodo em que ambas as sub-árvores são vazias.
*/
ABin folhaEsq(ABin a) {

    while(a->esq != NULL || a->dir != NULL) {
        if(a->esq != NULL) {
            a = a->esq;
        } else {
            a = a->dir;
        }
    }
    return a;
}

//[Exame 25] Dada uma árvore binária não vazia, calcula o endereço de uma das folhas que está no
//nível mais profundo.

ABin altura (ABin a) {
    if(a == NULL) return 0;

    int altEsq = altura(a->esq);
    int altDir = altura(a->dir);

    if(altEsq > altDir) {
        return 1 + altEsq;
    } else {
        return 1 + altDir;
    }
}

ABin folhaMaisProfunda (ABin a) {
    if(a == NULL) return 0;

    if(a->esq == NULL && a->dir == NULL) return a;

    if(altura(a->esq) > altura(a->dir)) {
        return folhaMaisProfunda(a->esq);
    } else {
        return folhaMaisProfunda(a->dir);
    }
}

//[Teste 25]
//Dada uma árvore binária de procura (sem números repetidos) e dois números
//que pertencem à árvore calcula o grau de parentesco entre eles (a distância
//entre eles na árvore).

//Auxiliar
int distancia(ABin a, int x) {
    int count = 0;

    while(a != NULL) {
        if(x < a->valor) {
            a = a->esq;
        } else {
            a = a->dir;
        }
        count++;
    }
    return count;
}

int parentesco(ABin a, int x, int y) {
    if(a == NULL) return NULL;
    
    while(a != NULL) {
        if(x < a->valor && y < a->valor) {
            a = a->esq;
        } else if (x > a->valor && y > a->valor) {
            a = a->dir;
        } else {
            break;
        }
    }
    return distancia(a,x) + distancia(a,y);
}

//[Teste 26] Testa se uma árvore é simétrica.
int espelha(ABin esq, ABin dir) {
    if(esq == NULL && dir == NULL) return 1;

    if(esq == NULL || dir == NULL) return 0;

    return (esq->valor == dir->valor) && espelha(esq->esq,dir->dir) && espelha(esq->dir,dir->esq);
}

int simetrica(ABin a) {
    if (a == NULL) return 1;

    return espelha(a->esq, a->dir);
}