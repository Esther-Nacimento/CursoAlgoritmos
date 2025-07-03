#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Para usar 'true' e 'false'
#include <locale.h>  // Adicione esta biblioteca para setlocale()

typedef struct {
    int valor;
    bool ocupado; 
} Elemento;

// Estrutura principal da Tabela Hash
typedef struct {
    int tamanho;   
    int quantidade; 
    Elemento *vetor; 
} TabelaHash;

TabelaHash* cria_tabela(int tamanho) {
    TabelaHash* tabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    if (tabela == NULL) {
        perror("Erro ao alocar TabelaHash");
        return NULL;
    }
    tabela->tamanho = tamanho;
    tabela->quantidade = 0; 

    tabela->vetor = (Elemento*) malloc(tamanho * sizeof(Elemento));
    if (tabela->vetor == NULL) {
        perror("Erro ao alocar vetor da TabelaHash");
        free(tabela); // Libera a tabela se o vetor falhar
        return NULL;
    }

    for (int i = 0; i < tamanho; i++) {
        tabela->vetor[i].ocupado = false;
    }

    return tabela;
}

void libera_tabela(TabelaHash* tabela) {
    if (tabela == NULL) return; // Evita liberar ponteiro nulo
    free(tabela->vetor); 
    free(tabela);     
}

int funcao_hash(int valor, int tamanho) {
    // Garante que o resultado seja não-negativo, importante para % com números negativos
    return abs(valor) % tamanho; 
}

void insere(TabelaHash* tabela, int valor) {
    if (tabela == NULL) return; // Proteção contra tabela nula

    // Não insere se a tabela estiver cheia
    // Esta condição é para endereçamento aberto com sondagem linear.
    // Se a tabela estiver cheia, não há mais espaço.
    if (tabela->quantidade >= tabela->tamanho) {
        printf("Aviso: Tabela Hash está cheia! Não foi possível inserir %d\n", valor);
        return;
    }

    int indice = funcao_hash(valor, tabela->tamanho);
    int indice_original = indice; // Guarda o índice inicial para evitar loop infinito

    // Loop para encontrar uma posição vazia ou o valor já existente
    while (tabela->vetor[indice].ocupado) {
        // Se o valor já existe na posição atual, não faz nada (já está inserido)
        if (tabela->vetor[indice].valor == valor) {
            return;
        }
        // Anda para a próxima posição (sondagem linear)
        indice = (indice + 1) % tabela->tamanho;

        // Se voltamos ao índice original, significa que a tabela está cheia
        // ou que não há mais posições vazias acessíveis (problema de clustering)
        if (indice == indice_original) {
            printf("Aviso: Tabela Hash cheia ou sem espaço para %d (clustering).\n", valor);
            return;
        }
    }

    // Encontrou uma posição vazia
    tabela->vetor[indice].valor = valor;
    tabela->vetor[indice].ocupado = true;
    tabela->quantidade++;
}

bool recupera(TabelaHash* tabela, int valor) {
    if (tabela == NULL) return false; // Proteção contra tabela nula

    // 1. Calcula o índice inicial
    int indice = funcao_hash(valor, tabela->tamanho);
    int tentativas = 0;
    int indice_original = indice; // Guarda o índice inicial para evitar loop infinito

    // Loop para procurar o valor
    // Continua enquanto a posição estiver ocupada E não tivermos percorrido toda a tabela
    while (tabela->vetor[indice].ocupado && tentativas < tabela->tamanho) {
        // Se o valor na posição atual é o que estamos procurando
        if (tabela->vetor[indice].valor == valor) {
            return true; // Encontrado!
        }
        // Anda para a próxima posição (sondagem linear)
        indice = (indice + 1) % tabela->tamanho;
        tentativas++;

        // Se voltamos ao índice original e não encontramos, significa que o valor não está na tabela
        // ou que a tabela está cheia e o valor nunca foi inserido.
        if (indice == indice_original) {
            break; // Sai do loop para evitar loop infinito em tabelas cheias
        }
    }

    return false; // Valor não encontrado
}

bool eh_subconjunto(int S[], int m, int T[], int n) {
    // Se m > n, S não pode ser um subconjunto de T
    if (m > n) {
        return false;
    }
    
    // Cria a tabela hash para armazenar os elementos de T
    // O tamanho da tabela é crucial para o desempenho.
    // Usar n * 2 é uma heurística comum para reduzir colisões em endereçamento aberto.
    // Garante um tamanho mínimo de 10 se n for 0.
    TabelaHash* tabela_t = cria_tabela(n > 0 ? n * 2 : 10); 
    if (tabela_t == NULL) {
        fprintf(stderr, "Erro: Falha ao criar tabela hash para eh_subconjunto.\n");
        return false;
    }

    // Insere todos os elementos de T na tabela hash
    for (int i = 0; i < n; i++) {
        insere(tabela_t, T[i]);
    }

    // Verifica se todos os elementos de S estão na tabela hash
    for (int i = 0; i < m; i++) {
        if (!recupera(tabela_t, S[i])) {
            libera_tabela(tabela_t); 
            return false; // Encontrou um elemento de S que não está em T
        }
    }

    // Se chegou até aqui, todos os elementos de S foram encontrados em T
    libera_tabela(tabela_t); // Limpa a memória
    return true;
}

int main() {
    // Define a localidade para o idioma padrão do sistema
    // Isso é crucial para que caracteres acentuados sejam exibidos corretamente
    setlocale(LC_ALL, ""); 
  
    int S1[] = {11, 7, 21};
    int T1[] = {37, 7, 14, 11, 21, 16};
    int m1 = sizeof(S1) / sizeof(S1[0]);
    int n1 = sizeof(T1) / sizeof(T1[0]);

    if (eh_subconjunto(S1, m1, T1, n1)) {
        printf("Cenario 1: S1 e um subconjunto de T1.\n");
    } else {
        printf("Cenario 1: S1 NAO e um subconjunto de T1.\n");
    }

    int S2[] = {11, 7, 99}; // 99 não está em T2
    int T2[] = {37, 7, 14, 11, 21, 16};
    int m2 = sizeof(S2) / sizeof(S2[0]);
    int n2 = sizeof(T2) / sizeof(T2[0]);

    if (eh_subconjunto(S2, m2, T2, n2)) {
        printf("Cenario 2: S2 e um subconjunto de T2.\n");
    } else {
        printf("Cenario 2: S2 NAO e um subconjunto de T2.\n");
    }

    // Teste com S vazio
    int S3[] = {};
    int T3[] = {1, 2, 3};
    int m3 = sizeof(S3) / sizeof(S3[0]);
    int n3 = sizeof(T3) / sizeof(T3[0]);

    if (eh_subconjunto(S3, m3, T3, n3)) {
        printf("Cenario 3: S3 (vazio) e um subconjunto de T3.\n"); // Esperado: Sim
    } else {
        printf("Cenario 3: S3 (vazio) NAO e um subconjunto de T3.\n");
    }

    // Teste com T vazio
    int S4[] = {1};
    int T4[] = {};
    int m4 = sizeof(S4) / sizeof(S4[0]);
    int n4 = sizeof(T4) / sizeof(T4[0]);

    if (eh_subconjunto(S4, m4, T4, n4)) {
        printf("Cenario 4: S4 e um subconjunto de T4 (vazio).\n");
    } else {
        printf("Cenario 4: S4 NAO e um subconjunto de T4 (vazio).\n"); // Esperado: Não
    }

    // Teste com ambos vazios
    int S5[] = {};
    int T5[] = {};
    int m5 = sizeof(S5) / sizeof(S5[0]);
    int n5 = sizeof(T5) / sizeof(T5[0]);

    if (eh_subconjunto(S5, m5, T5, n5)) {
        printf("Cenario 5: S5 (vazio) e um subconjunto de T5 (vazio).\n"); // Esperado: Sim
    } else {
        printf("Cenario 5: S5 (vazio) NAO é um subconjunto de T5 (vazio).\n");
    }


    return 0;
}
