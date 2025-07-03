#include <stdio.h>
#include <stdlib.h> // Necessário para funções de alocação de memória (malloc, free, realloc)
#include <string.h> // Necessário para funções de manipulação de strings (strcpy)

// Definição do tipo de Heap: Mínimo (MIN_HEAP) ou Máximo (MAX_HEAP).
// Para a cantina, queremos MIN_HEAP, pois o menor valor de prioridade indica maior urgência.
typedef enum TipoHeap {
    MIN_HEAP,
    MAX_HEAP
} TipoHeap;

// Estrutura que representa um nó individual no Heap, ou seja, um "pedido".
// Cada pedido tem uma prioridade, um identificador e agora um nome.
typedef struct no_heap {
    int prioridade; // Valor numérico que define a prioridade (ex: 1 para café, 5 para prato feito).
                    // Quanto menor o número, maior a urgência de preparo.
    int valor;      // Identificador único do pedido (ex: número do pedido).
    char nome[50];  // Nome do pedido (ex: "Cafe Expresso", "Prato Feito"). Tamanho fixo de 50 caracteres.
} NoHeap;

// Estrutura principal que define o Heap, funcionando como o "gerenciador de pedidos".
typedef struct heap {
    int tam;        // Número atual de elementos (pedidos) no Heap.
    int max;        // Capacidade máxima de elementos que o Heap pode armazenar.
    int bloco;      // Quantidade de elementos a serem alocados caso o Heap precise expandir.
    TipoHeap tipo;  // Indica se o Heap é MIN_HEAP ou MAX_HEAP.
    NoHeap *vet;    // Ponteiro para o vetor que armazena os nós (pedidos) do Heap.
} Heap;

// Função para criar e inicializar um novo Heap.
// Recebe a capacidade máxima, o tipo (MIN_HEAP/MAX_HEAP) e o tamanho do bloco de expansão.
Heap *cria(int max, TipoHeap tipo, int bloco) {
    Heap *novoHeap = (Heap *)malloc(sizeof(Heap)); // Aloca memória para a estrutura do Heap.
    if (novoHeap == NULL) {
        printf("Erro: Nao foi possivel alocar memoria para o Heap.\n");
        exit(1); // Encerra o programa em caso de falha na alocação.
    }

    novoHeap->tam = 0; // Inicializa o tamanho atual do Heap como zero.
    novoHeap->max = max; // Define a capacidade máxima.
    novoHeap->bloco = bloco; // Define o tamanho do bloco de expansão.
    novoHeap->tipo = tipo; // Define o tipo do Heap.

    // Aloca memória para o vetor de nós. A posição 0 do vetor não será utilizada
    // para simplificar os cálculos de índices de pai e filhos (base 1).
    novoHeap->vet = (NoHeap *)malloc((max + 1) * sizeof(NoHeap));
    if (novoHeap->vet == NULL) {
        printf("Erro: Nao foi possivel alocar memoria para o vetor do Heap.\n");
        free(novoHeap); // Libera a memória já alocada para a estrutura do Heap.
        exit(1);
    }
    printf("Sistema de pedidos da cantina criado! Capacidade inicial: %d elementos.\n", max);
    return novoHeap; // Retorna o ponteiro para o Heap recém-criado.
}

// Função auxiliar para ajustar a posição de um nó após uma inserção.
// O nó "sobe" no Heap até que sua prioridade esteja correta em relação ao seu pai.
// Pense nisso como um pedido de alta prioridade "subindo" na fila para ser atendido mais rápido.
void subirNoHeap(Heap *heap, int ind) {
    int pai = ind / 2; // Calcula o índice do nó pai (usando a propriedade i/2).

    // O loop continua enquanto o nó não for a raiz (ind > 1)
    // e a propriedade do Heap for violada (prioridade do filho vs. pai).
    while (ind > 1) {
        if (heap->tipo == MIN_HEAP) { // Se o Heap é do tipo Mínimo (menor prioridade no topo)
            if (heap->vet[pai].prioridade > heap->vet[ind].prioridade) {
                // Se a prioridade do pai é MAIOR que a do filho, eles precisam trocar de lugar.
                NoHeap temp = heap->vet[ind]; // Armazena o filho temporariamente.
                heap->vet[ind] = heap->vet[pai]; // O pai desce para a posição do filho.
                heap->vet[pai] = temp; // O filho sobe para a posição do pai.
                ind = pai; // Atualiza o índice do nó para continuar subindo a árvore.
                pai = ind / 2; // Recalcula o novo pai.
            } else {
                break; // A propriedade do Heap é mantida, o nó está na posição correta.
            }
        } else { // Se o Heap é do tipo Máximo (maior prioridade no topo)
            if (heap->vet[pai].prioridade < heap->vet[ind].prioridade) {
                // Se a prioridade do pai é MENOR que a do filho, eles precisam trocar de lugar.
                NoHeap temp = heap->vet[ind];
                heap->vet[ind] = heap->vet[pai];
                heap->vet[pai] = temp;
                ind = pai;
                pai = ind / 2;
            } else {
                break;
            }
        }
    }
}

// Função para inserir um novo elemento (pedido) no Heap.
// Agora recebe também o nome do pedido.
void insere(Heap *heap, int valor, int prioridade, const char *nome) {
    // Verifica se o Heap atingiu sua capacidade máxima.
    if (heap->tam == heap->max) {
        // Se a fila de pedidos "lotou", realoca memória para expandir a capacidade do Heap.
        printf("A fila de pedidos lotou! Expandindo capacidade...\n");
        heap->max += heap->bloco; // Aumenta a capacidade máxima.
        // realloc tenta redimensionar o bloco de memória, mantendo o conteúdo existente.
        heap->vet = (NoHeap *)realloc(heap->vet, (heap->max + 1) * sizeof(NoHeap));
        if (heap->vet == NULL) {
            printf("Erro: Nao foi possivel realocar memoria para o Heap.\n");
            exit(1);
        }
        printf("Heap expandido! Nova capacidade: %d elementos.\n", heap->max);
    }

    heap->tam++; // Incrementa o contador de elementos no Heap.
    int ind = heap->tam; // O novo elemento é inserido na última posição disponível.

    // Atribui a prioridade, o valor e o nome ao novo nó.
    heap->vet[ind].prioridade = prioridade;
    heap->vet[ind].valor = valor;
    strncpy(heap->vet[ind].nome, nome, sizeof(heap->vet[ind].nome) - 1); // Copia o nome com segurança
    heap->vet[ind].nome[sizeof(heap->vet[ind].nome) - 1] = '\0'; // Garante terminação nula

    // Chama a função auxiliar para ajustar a posição do novo nó no Heap.
    subirNoHeap(heap, ind);

    printf("Pedido #%d (%s, Prioridade: %d) inserido com sucesso.\n", valor, nome, prioridade);
}

// Função auxiliar para ajustar a posição de um nó após uma remoção.
// O nó "desce" no Heap até que sua prioridade esteja correta em relação aos seus filhos.
// Isso simula o rearranjo da fila após um pedido ser atendido.
void descerNoHeap(Heap *heap, int ind) {
    int filhoEsquerdo = 2 * ind; // Calcula o índice do filho esquerdo.
    int filhoDireito = 2 * ind + 1; // Calcula o índice do filho direito.
    int indiceMelhorPrioridade = ind; // Assume que o nó atual tem a melhor prioridade inicialmente.

    // Encontra o filho com a "melhor" prioridade (menor para MIN_HEAP, maior para MAX_HEAP).
    if (heap->tipo == MIN_HEAP) { // Se o Heap é do tipo Mínimo
        // Se o filho esquerdo existe e tem prioridade MENOR que o nó atual, ele é o "melhor".
        if (filhoEsquerdo <= heap->tam && heap->vet[filhoEsquerdo].prioridade < heap->vet[indiceMelhorPrioridade].prioridade) {
            indiceMelhorPrioridade = filhoEsquerdo;
        }
        // Se o filho direito existe e tem prioridade MENOR que o "melhor" encontrado até agora, ele é o "melhor".
        if (filhoDireito <= heap->tam && heap->vet[filhoDireito].prioridade < heap->vet[indiceMelhorPrioridade].prioridade) {
            indiceMelhorPrioridade = filhoDireito;
        }
    } else { // Se o Heap é do tipo Máximo
        // Se o filho esquerdo existe e tem prioridade MAIOR que o nó atual, ele é o "melhor".
        if (filhoEsquerdo <= heap->tam && heap->vet[filhoEsquerdo].prioridade > heap->vet[indiceMelhorPrioridade].prioridade) {
            indiceMelhorPrioridade = filhoEsquerdo;
        }
        // Se o filho direito existe e tem prioridade MAIOR que o "melhor" encontrado até agora, ele é o "melhor".
        if (filhoDireito <= heap->tam && heap->vet[filhoDireito].prioridade > heap->vet[indiceMelhorPrioridade].prioridade) {
            indiceMelhorPrioridade = filhoDireito;
        }
    }

    // Se o nó com a melhor prioridade não for o nó atual, realiza a troca.
    if (indiceMelhorPrioridade != ind) {
        NoHeap temp = heap->vet[ind];
        heap->vet[ind] = heap->vet[indiceMelhorPrioridade];
        heap->vet[indiceMelhorPrioridade] = temp;
        // Chama recursivamente para continuar o ajuste do nó que desceu.
        descerNoHeap(heap, indiceMelhorPrioridade);
    }
}

// Função para remover o elemento de maior prioridade (a raiz do Heap).
// No nosso caso (MIN_HEAP), remove o pedido mais rápido de ser preparado.
// Agora retorna o nome do pedido removido.
char *removeHeap(Heap *heap) {
    if (heap->tam == 0) {
        printf("Erro: Heap vazio. Nao ha elementos para remover.\n");
        return NULL; // Retorna NULL para indicar que a remoção não foi possível.
    }

    // Armazena o nome do pedido a ser removido (o da raiz).
    // É importante copiar a string, pois a memória da raiz será sobrescrita.
    static char nomeRemovido[50]; // Usamos static para que a string persista após a função.
    strncpy(nomeRemovido, heap->vet[1].nome, sizeof(nomeRemovido) - 1);
    nomeRemovido[sizeof(nomeRemovido) - 1] = '\0';

    // Move o último elemento do Heap para a posição da raiz.
    heap->vet[1] = heap->vet[heap->tam];
    heap->tam--; // Decrementa o contador de elementos.

    // Chama a função auxiliar para ajustar a posição do novo elemento na raiz.
    descerNoHeap(heap, 1);

    printf("Pedido '%s' removido do Heap.\n", nomeRemovido);
    return nomeRemovido; // Retorna o nome do pedido que foi removido.
}

// Função para exibir os elementos atualmente no Heap.
// Agora exibe também o nome do pedido.
void apresentaHeap(Heap *heap) {
    if (heap->tam == 0) {
        printf("Heap vazio.\n");
        return;
    }
    printf("Elementos no Heap (Prioridade, ID, Nome):\n");
    for (int i = 1; i <= heap->tam; i++) {
        printf("(%d, #%d, '%s') ", heap->vet[i].prioridade, heap->vet[i].valor, heap->vet[i].nome);
    }
    printf("\n"); // Adiciona uma quebra de linha após listar todos os elementos.
}

// Função para liberar toda a memória alocada para o Heap.
void liberaHeap(Heap *heap) {
    if (heap != NULL) {
        free(heap->vet); // Libera a memória do vetor de nós.
        free(heap);      // Libera a memória da estrutura do Heap.
        printf("Heap liberado com sucesso.\n");
    }
}

int main() {
    // Cria um Heap para gerenciar os pedidos da cantina.
    // Capacidade inicial de 5 elementos, do tipo MIN_HEAP, com bloco de expansão de 2.
    Heap *filaCantina = cria(5, MIN_HEAP, 2);

    printf("\n--- Inserindo pedidos ---\n");
    insere(filaCantina, 101, 3, "Suco de Laranja"); // Pedido #101: Prioridade 3
    insere(filaCantina, 102, 1, "Cafe Expresso");   // Pedido #102: Prioridade 1 - Este deve ir para a raiz!
    insere(filaCantina, 103, 5, "Prato Feito");     // Pedido #103: Prioridade 5
    insere(filaCantina, 104, 2, "Salgado Assado");  // Pedido #104: Prioridade 2
    insere(filaCantina, 105, 4, "Sanduiche Natural"); // Pedido #105: Prioridade 4

    printf("\n--- Estado atual do Heap ---\n");
    apresentaHeap(filaCantina);

    // Testa a expansão do Heap inserindo um novo elemento que excede a capacidade inicial.
    printf("\n--- Inserindo um novo pedido (testando expansao) ---\n");
    insere(filaCantina, 106, 1, "Cha Gelado"); // Pedido #106: Prioridade 1 - Também deve ir para a raiz!

    printf("\n--- Estado do Heap apos expansao e nova insercao ---\n");
    apresentaHeap(filaCantina);

    // Remove elementos do Heap, simulando o atendimento dos pedidos.
    printf("\n--- Removendo pedidos (do mais prioritario para o menos prioritario) ---\n");
    char *nomePedidoAtendido;

    nomePedidoAtendido = removeHeap(filaCantina); // Deve remover um dos Cafés (Prioridade 1)
    if (nomePedidoAtendido) printf("Pedido '%s' foi atendido!\n\n", nomePedidoAtendido); // Adiciona \n\n
    apresentaHeap(filaCantina);

    nomePedidoAtendido = removeHeap(filaCantina); // Deve remover o outro de Prioridade 1
    if (nomePedidoAtendido) printf("Pedido '%s' foi atendido!\n\n", nomePedidoAtendido); // Adiciona \n\n
    apresentaHeap(filaCantina);

    nomePedidoAtendido = removeHeap(filaCantina); // Deve remover "Salgado Assado" (Prioridade 2)
    if (nomePedidoAtendido) printf("Pedido '%s' foi atendido!\n\n", nomePedidoAtendido); // Adiciona \n\n
    apresentaHeap(filaCantina);

    // Libera a memória alocada para o Heap ao final do programa.
    printf("\n--- Liberando memoria do Heap ---\n");
    liberaHeap(filaCantina);

    return 0;
}
