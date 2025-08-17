#include <stdio.h>
#include <stdlib.h>

// Definimos a estrutura do nó da árvore AVL usando typedef
typedef struct NoAVL {
    int valor;               // Valor armazenado no nó
    int altura;              // Altura do nó (necessária para o balanceamento)
    struct NoAVL *esq;       // Ponteiro para o filho à esquerda
    struct NoAVL *dir;       // Ponteiro para o filho à direita
} NoAVL;

// Retorna a altura de um nó (0 se for nulo)
int altura(NoAVL *n) {
    if (n == NULL) return 0;
    return n->altura;
}

// Retorna o maior entre dois valores inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calcula o fator de balanceamento de um nó
int fatorBalanceamento(NoAVL *n) {
    if (n == NULL) return 0;
    return altura(n->esq) - altura(n->dir);
}

// Rotação simples à direita (caso Esquerda-Esquerda)
NoAVL* rotacaoDireita(NoAVL *y) {
    NoAVL *x = y->esq;
    NoAVL *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

// Rotação simples à esquerda (caso Direita-Direita)
NoAVL* rotacaoEsquerda(NoAVL *x) {
    NoAVL *y = x->dir;
    NoAVL *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

// Insere um novo valor na árvore AVL com balanceamento
NoAVL* inserir(NoAVL *no, int valor) {
    if (no == NULL) {
        NoAVL* novo = (NoAVL*)malloc(sizeof(NoAVL));
        novo->valor = valor;
        novo->esq = novo->dir = NULL;
        novo->altura = 1;
        return novo;
    }

    if (valor < no->valor)
        no->esq = inserir(no->esq, valor);
    else if (valor > no->valor)
        no->dir = inserir(no->dir, valor);
    else
        return no; // Não insere duplicatas

    no->altura = 1 + max(altura(no->esq), altura(no->dir));
    int fb = fatorBalanceamento(no);

    // Casos de desbalanceamento
    if (fb > 1 && valor < no->esq->valor)
        return rotacaoDireita(no);

    if (fb < -1 && valor > no->dir->valor)
        return rotacaoEsquerda(no);

    if (fb > 1 && valor > no->esq->valor) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }

    if (fb < -1 && valor < no->dir->valor) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

// Função para imprimir os valores da árvore em ordem (crescente)
void imprimirEmOrdem(NoAVL *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        imprimirEmOrdem(raiz->dir);
    }
}

int main() {
    // Declara a variável da raiz da árvore AVL
    NoAVL *Raiz = NULL;

    // Valores da questão 2
    int valores[] = {50, 25, 80, 71, 94, 87, 102, 13, 92, 8, 18, 82};
    int n = sizeof(valores) / sizeof(valores[0]);

    // Insere todos os valores na árvore AVL
    for (int i = 0; i < n; i++) {
        Raiz = inserir(Raiz, valores[i]);
    }

    // Impressão da árvore em ordem
    printf("Arvore AVL em ordem: ");
    imprimirEmOrdem(Raiz);
    printf("\n");

    return 0;
}
