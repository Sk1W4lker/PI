#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//
// Listas ligadas são estruturas de dados formadas por células
// "encadeadas" por apontadores, em que cada célula guarda 
// "alguma informação" e uma referência/apontador para a célula
// seguinte.
//
// Vamos estudar alguns conceitos básicos utilizando listas "simples"
// de inteiros. Concretamente:
//
// - o que é uma célula
// - como representar uma lista ligada vazia
// - como percorrer uma lista ligada
// - como inserir no início de uma lista ligada
// - como inserir no fim de uma lista ligada
// - como libertar a memória associada a uma lista ligada
//

// Cada célula (definida como 'struct') guarda:
// - um valor inteiro
// - um apontador para a célula seguinte
//
// O tipo 'Lista' representa um apontador para uma célula (por vezes, 
// também é utilizado o nome nó para denotar o mesmo conceito).
//
// Exemplo "gráfico" (simplificado) de uma lista ligada para construir 
// alguma intuição sobre o assunto em estudo:
//
//   +-------+-------+    +-------+-------+
//   | valor | prox  | -> | valor | prox  | -> NULL
//   +-------+-------+    +-------+-------+
//
//
typedef struct celula {
  int valor;
  struct celula *prox;
} *Lista;



// A função seguinte cria uma nova célula (malloc) inicializada com 
// 'valor' (argumento da função).
// - nota: esta nova célula será inicializada com 'prox = NULL', ou seja,
//   inicialmente, não terá "nenhum próximo".
//
// Retorna:
// - o endereço da nova célula, em caso de sucesso
// - NULL, em caso de erro na alocação de memória (malloc)
// - nota: Lista é um apontador (o tipo foi declarado como *Lista)

Lista criar_celula(int valor) {
  Lista nova;

  // pergunta: porque é utilizada a expressão "sizeof(struct celula)"?
  nova = malloc(sizeof(struct celula));

  // é importante verificar o valor de retorno de malloc: caso 
  // não seja possível alocar a memória pedida
  if(nova == NULL) {
    return NULL;
  }

  nova->valor = valor;
  nova->prox = NULL;

  return nova;
}


// A seguinte função insere um elemento no início da lista
//
// Intuição:
// - cria-se uma nova célula
// - a nova célula passa a apontar para a lista antiga
// - a nova célula passa a ser a nova cabeça da lista
//
Lista inserir_inicio(Lista l, int valor) {
  Lista nova;

  nova = criar_celula(valor);

  if(nova == NULL) {
    return NULL;
  }

  nova->prox = l;
  return nova;
}


// A seguinte função imprime todos os elementos da lista.
void imprimir_lista(Lista l) {
  // pergunta: a variável aux é estritamente necessária neste contexto? 
  //   - de outra forma: pode-se substituir 'aux' por 'l' no código
  //     seguinte sem afectar a funcionalidade da função? 
  //   - resposta: Sim. Sugestão: realize essa alteração, teste, e procure
  //     entender bem porquê. Notas 'Lista l' é um apontador; como 'l' é uma 
  //     variável local, alterar o valor de l (não os valores apontados por l
  //     mas sim 'l') não tem repercusões/efeito no local da chamada a esta função
  //     neste caso a função 'main', definida mais à frente. 
  Lista aux = l;

  printf("Lista: ");

  while(aux != NULL) {
    printf("%d ", aux->valor);
    aux = aux->prox;
  }

  printf("\n");
}

// a seguinte função liberta (free) as células de uma lista
Lista libertar_lista(Lista l) {
  Lista temp;

  while(l != NULL) {
    temp = l->prox;
    free(l);
    l = temp;
  }

  return NULL;
}

// a seguinte função calcula o comprimento de uma lista
size_t comprimento_lista(Lista l) {
  size_t n = 0;

  while(l != NULL) {
    n++;
    l = l->prox;
  }

  return n;
}

// a seguinte função retorna a última célula da lista (percorre a lista enquanto
// houver "próximos")
Lista ultima_celula(Lista l){
  if(l == NULL) { 
    return NULL; 
  }

  while(l->prox != NULL) {
    l = l->prox; 
  }

  return l;
}

// A seguinte função insere no fim da lista. No exemplo apresentado:
//  - recebe a lista actual (que pode ser NULL se estiver vazia) e o valor para colocar na nova célula
//
// E o que deve retornar a função? Vamos analizar caso a caso para tentarmos perceber melhor o contexto 
// do problema a resolver.
//
//  1. se 'l' for NULL, então a lista encontra-se vazia. Como tal, devemos retornar o apontador da nova
//     célula (utilizando a função criar célula).
//
//  2. se 'l' é diferente de NULL, então a lista tem pelo menos um elemento. Neste caso podemos utilizar
//     a função anterior (ultima_celula) para identificar a última célula, que podemos chamar de 'ult', 
//     e assim indicar que 'ult->prox' deverá agora conter o endereço da nova célula criada. E o que
//     devemos retornar? Bem, considerando o ponto 1), em que decidimos que a função retorna Lista, então
//     neste caso podemos/devemos retornar 'l' (a lista original) para sermos consistentes no tipo de retorno.
//
//  3. falta ainda considerar um outro caso: e se a chamada à função malloc (que ocorre na função criar_celula)
//     falhar e retornar NULL (porque, por exemplo, não havia memória disponível)? Para tratar este caso,
//     podemos seguir o padrão implementado pela função realloc (ver ficheiro t8/realloc.c e consultar o manual
//     com, por exemplo, man 3 realloc). Resumidamente, a função realloc pode: retornar o mesmo apontador caso 
//     a reallocação seja possível de realizar no "mesmo espaço de memória"; retornar um novo apontador caso
//     seja preciso "mover" para outro lado; NULL caso "corra mal". Como tal, podemos adoptar a mesma convenção
//     e retornar também NULL. Depois (e de forma semelhante à utilização da função realloc) não devemos reescrever
//     o apontador antigo de imediato (por exemplo, evitar 'l = inserir_fim(l, 10)') pois caso a criação da célula
//     falhe (e a função inserir_fim retornar NULL) perdemos o 'l' antigo (e como tal não podemos "fazer free" para
//     libertar a memória)
//
// Note que a situação descrita em 3. também ocorre no contexto de inserir_inicio. 

Lista inserir_fim(Lista l, int valor) {
  Lista nova;
  Lista ult;

  // começamos por criar uma célula com o valor correspondente
  nova = criar_celula(valor);

  // note que se a alocação de memória falhar, a função criar_celula retorna NULL
  // - de acordo com a discussão anterior, retornamos NULL para assinalar este facto
  if(nova == NULL) { 
    return NULL; 
  }

  // neste ponto de execução sabemos que 'nova' é diferente de NULL. Se a lista 'l'
  // dada como argumento for vazia, então 'nova' é o único elemento e pode ser retornado
  if(l == NULL) { 
    return nova; 
  }

  // se chegamos a este ponto de execução da função, então sabemos que a alocação de 'nova'
  // teve sucesso e a lista tem pelo menos um elemento. Como tal, identificamos a última célula,
  // e definimos o próximo da última célula como a nova.
  ult = ultima_celula(l);
  ult->prox = nova;

  return l;
}

// ============================================================
//
// Numa lista simplesmente ligada, cada célula guarda:
//
// - a informação
// - um apontador para a célula seguinte
//
// Isso permite percorrer a lista da esquerda para a direita,
// mas nao permite recuar diretamente.
//
// Numa lista duplamente ligada, cada célula guarda:
//
// - a informação
// - um apontador para a célula seguinte
// - um apontador para a célula anterior
//
// Assim, cada célula "conhece" os seus dois vizinhos.
//
// Vantagens:
//
// - podemos percorrer a lista nos dois sentidos
// - algumas remoções e inserções tornam-se mais naturais
// - se tivermos apontador para a última célula, é fácil
//   percorrer a lista de trás para a frente
//
// Custo:
//
// - cada célula passa a ocupar mais memória
// - temos mais apontadores para manter consistentes
//
// Neste ficheiro usamos também uma struct 'Lista' para guardar
// meta-informação:
//
// - nelems: número de elementos
// - first: primeira célula
// - last: última célula
//
// Invariante pretendida:
//
// - se nelems == 0, então first == NULL e last == NULL
// - se nelems > 0, então first != NULL e last != NULL
// ============================================================


// Cada célula guarda:
//
// - valor
// - apontador para a célula anterior
// - apontador para a célula seguinte
//
// Diagrama:
//
//   NULL <- [10] <-> [20] <-> [30] -> NULL
typedef struct celula
{
  int valor;
  struct celula *ant;
  struct celula *prox;
} Celula;


// A lista guarda informação global sobre a estrutura.
typedef struct
{
  size_t nelems;
  Celula *first;
  Celula *last;
} Lista;



// Inicializa uma lista vazia.
void lista_init(Lista *l)
{
  assert(l != NULL);

  l->nelems = 0;
  l->first = NULL;
  l->last = NULL;
}



// Cria uma nova célula isolada.
//
// A nova célula começa com:
//
// - ant = NULL
// - prox = NULL
//
// Isto significa que, neste momento, ainda nao está ligada
// a nenhuma lista.
Celula *criar_celula(int valor)
{
  Celula *nova;

  nova = malloc(sizeof(Celula));

  if(nova == NULL)
  {
    return NULL;
  }

  nova->valor = valor;
  nova->ant = NULL;
  nova->prox = NULL;

  return nova;
}



// Insere um novo valor no início da lista.
//
// Casos:
//
// 1. lista vazia
// 2. lista com um ou mais elementos
//
// Exemplo. Antes:
//
//   first -> [10] <-> [20] <-> [30]
//
// Depois de inserir 5 no início:
//
//   first -> [ 5] <-> [10] <-> [20] <-> [30]
//
// Ideia importante:
//
// - a nova célula passa a apontar para a antiga primeira
// - a antiga primeira passa a apontar para a nova
//
int inserir_inicio(Lista *l, int valor) {
  Celula *nova;

  assert(l != NULL);

  nova = criar_celula(valor);

  if(nova == NULL) { 
    return 0; 
  }

  nova->prox = l->first;

  if(l->first != NULL) {
    l->first->ant = nova;
  } else {
    // Se a lista estava vazia, a nova célula é também a última.
    l->last = nova;
  }

  l->first = nova;
  l->nelems++;

  return 1;
}



// Insere um novo valor no fim da lista.
//
// Exemplo. Antes:
//
//   last -> [10] <-> [20] <-> [30]
//
// Depois de inserir 40 no fim:
//
//   last -> [10] <-> [20] <-> [30] <-> [40]
//
// Ideia importante:
//
// - a nova célula passa a apontar para a antiga última
//   através de 'ant'
// - a antiga última passa a apontar para a nova através
//   de 'prox'
int inserir_fim(Lista *l, int valor) {
  Celula *nova;

  assert(l != NULL);

  nova = criar_celula(valor);

  if(nova == NULL) { 
    return 0; 
  }

  nova->ant = l->last;

  if(l->last != NULL) {
    l->last->prox = nova;
  } else {
    // Se a lista estava vazia, a nova célula é também a primeira.
    l->first = nova;
  }

  l->last = nova;
  l->nelems++;

  return 1;
}



// Imprime a lista.
//
// Padrão:
//
// - começamos em first
// - seguimos os apontadores 'prox'
void imprimir_frente(const Lista *l) {
  Celula *atual;

  assert(l != NULL);

  printf("Frente: ");

  atual = l->first;

  while(atual != NULL) {
    printf("%d ", atual->valor);
    atual = atual->prox;
  }

  printf("\n");
}



// Imprime a lista da direita para a esquerda.
//
// Este é um dos aspetos mais característicos de uma lista
// duplamente ligada:
//
// - começamos em last
// - seguimos os apontadores 'ant'
void imprimir_tras(const Lista *l) {
  Celula *atual;

  assert(l != NULL);

  printf("Tras:   ");

  atual = l->last;

  while(atual != NULL) {
    printf("%d ", atual->valor);
    atual = atual->ant;
  }

  printf("\n");
}



// Remove o primeiro elemento da lista.
//
// Casos:
//
// 1. lista vazia
// 2. lista com um elemento
// 3. lista com dois ou mais elementos
//
// Este exemplo é útil para mostrar como atualizar:
//
// - first
// - eventualmente last
// - o apontador 'ant' da nova primeira célula
int remover_inicio(Lista *l) {
  Celula *temp;

  assert(l != NULL);

  if(l->first == NULL) { 
    return 0; 
  }

  temp = l->first;
  l->first = temp->prox;

  if(l->first != NULL) {
    l->first->ant = NULL;
  } else {
    // A lista ficou vazia.
    l->last = NULL;
  }

  free(temp);
  l->nelems--;

  return 1;
}



// Remove o último elemento da lista.
//
// Este exemplo mostra a simetria com remover_inicio:
//
// - atualizamos last
// - eventualmente first
// - o apontador 'prox' da nova última célula
int remover_fim(Lista *l) {
  Celula *temp;

  assert(l != NULL);

  if(l->last == NULL) {
    return 0;
  }

  temp = l->last;
  l->last = temp->ant;

  if(l->last != NULL) {
    l->last->prox = NULL;
  } else {
    // A lista ficou vazia.
    l->first = NULL;
  }

  free(temp);
  l->nelems--;

  return 1;
}



// Liberta toda a memória ocupada pela lista.
//
// Tal como numa lista simplesmente ligada, percorremos célula
// a célula e libertamos uma de cada vez.
//
// Aqui usamos os apontadores 'prox' para percorrer.
void lista_destroy(Lista *l)
{
  Celula *atual;
  Celula *temp;

  assert(l != NULL);

  atual = l->first;

  while(atual != NULL)
  {
    temp = atual->prox;
    free(atual);
    atual = temp;
  }

  lista_init(l);
}



// Verifica algumas invariantes simples da lista.
//
// Esta função é útil apenas para reforçar a ideia de que,
// quando manipulamos muitos apontadores, convém confirmar
// que a estrutura continua coerente.
void verificar_invariantes(const Lista *l)
{
  assert(l != NULL);

  if(l->nelems == 0)
  {
    assert(l->first == NULL);
    assert(l->last == NULL);
  }
  else
  {
    assert(l->first != NULL);
    assert(l->last != NULL);
    assert(l->first->ant == NULL);
    assert(l->last->prox == NULL);
  }
}


void verificar_invariantes_ordenada(const Lista *l)
{
  Celula *atual;

  assert(l != NULL);

  if(l->nelems == 0)
  {
    assert(l->first == NULL);
    assert(l->last == NULL);
    return;
  }

  assert(l->first != NULL);
  assert(l->last != NULL);
  assert(l->first->ant == NULL);
  assert(l->last->prox == NULL);

  atual = l->first;

  while(atual->prox != NULL)
  {
    // verifica que a ligação para a frente e para trás
    // está consistente
    assert(atual->prox->ant == atual);

    // verifica que a lista está ordenada por ordem crescente
    assert(atual->valor <= atual->prox->valor);

    atual = atual->prox;
  }

  // no fim do ciclo, 'atual' deve estar na última célula
  assert(atual == l->last);
}

// Insere um novo valor na lista, mantendo a ordenação crescente.
//
// Casos a tratar:
//
// 1. lista vazia
// 2. inserção no início
// 3. inserção no meio
// 4. inserção no fim
//
// Estratégia:
//
// - percorremos a lista enquanto os valores atuais forem
//   menores do que o valor a inserir
//
// - no fim do ciclo, 'atual' aponta para:
//
//   - a primeira célula com valor >= valor, ou
//   - NULL, se chegámos ao fim da lista
//
// A função devolve:
//
// - 1 em caso de sucesso
// - 0 em caso de erro de alocação
int inserir_ordenado(Lista *l, int valor)
{
  Celula *nova;
  Celula *atual;
  Celula *anterior;

  nova = criar_celula(valor);

  if(nova == NULL)
  {
    return 0;
  }

  atual = l->first;
  anterior = NULL;

  while(atual != NULL && atual->valor < valor)
  {
    anterior = atual;
    atual = atual->prox;
  }

  // Caso 1:
  // inserção no início da lista
  if(anterior == NULL)
  {
    nova->prox = l->first;

    if(l->first != NULL)
    {
      l->first->ant = nova;
    }
    else
    {
      // A lista estava vazia; a nova célula é também a última.
      l->last = nova;
    }

    l->first = nova;
    l->nelems++;

    return 1;
  }

  // Caso 2 e 3:
  // inserção depois de 'anterior'
  nova->ant = anterior;
  nova->prox = atual;
  anterior->prox = nova;

  if(atual != NULL)
  {
    // Inserção no meio.
    atual->ant = nova;
  }
  else
  {
    // Inserção no fim.
    l->last = nova;
  }

  l->nelems++;

  return 1;
}



void minSort(int v[], int N) {
        int m;

        if(n>1) {
        M = minInd(v,n);
        swap(v,0,m);

        minSort(v+1,n-1);
        }
}

 void minSort(int v[], int N) {
        int m;

        if(n>1) {
        m = minInd(v,n);
        swap(v,m,N-1);
        N--;
        }
}

void minSort(int v[], int N) {
  int i, m;

  for(i=0;i<N-1;i++) {
    m = minInd(v+i,n-i);
    swap(v,i,m+i);
  }
}