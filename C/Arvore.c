/*Exercício 3: Monte a árvore AVL para as inserções 10, 20, 30, 40, 35 (nesta ordem), indicando a cada passo:
a)Qual elemento foi inserido.
b)O fator de balanceamento de cada nó.
c)Qual rotação foi realizada, se necessária.

Esther Fernandes do Nascimento 
Matricula: 1240206904*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Função para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // Novo nó é inicialmente adicionado na folha
    return newNode;
}

// Função para obter a altura de um nó
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Função para obter o fator de balanceamento
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Função para realizar uma rotação à direita
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza as alturas
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x; // Retorna nova raiz
}

// Função para realizar uma rotação à esquerda
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza as alturas
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y; // Retorna nova raiz
}

// Função para inserir um novo valor na árvore AVL
Node* insert(Node* node, int data) {
    // 1. Realiza a inserção normal
    if (!node) {
        printf("Inserindo: %d\n", data); // a) Qual elemento foi inserido
        return createNode(data);
    }

    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        return node; // Duplicatas não são permitidas
    }

    // 2. Atualiza a altura do nó ancestral
    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));

    // 3. Obtém o fator de balanceamento
    int balance = getBalance(node);
    printf("Fator de balanceamento apos insercao de %d: %d\n", data, balance); // b) O fator de balanceamento de cada nó

    // Se o nó se tornar desbalanceado, existem 4 casos

    // Caso 1: Rotação à direita
    if (balance > 1 && data < node->left->data) {
        printf("Rotacao a direita em %d\n", node->data); // c) Qual rotação foi realizada, se necessária
        return rightRotate(node);
    }

    // Caso 2: Rotação à esquerda
    if (balance < -1 && data > node->right->data) {
        printf("Rotacao a esquerda em %d\n", node->data); // c) Qual rotação foi realizada, se necessária
        return leftRotate(node);
    }

    // Caso 3: Rotação à esquerda/direita
    if (balance > 1 && data > node->left->data) {
        printf("Rotacao a esquerda em %d\n", node->left->data); // c) Qual rotação foi realizada, se necessária
        node->left = leftRotate(node->left);
        printf("Rotacao a direita em %d\n", node->data); // c) Qual rotação foi realizada, se necessária
        return rightRotate(node);
    }

    // Caso 4: Rotação à direita/esquerda
    if (balance < -1 && data < node->right->data) {
        printf("Rotacao a direita em %d\n", node->right->data); // c) Qual rotação foi realizada, se necessária
        node->right = rightRotate(node->right);
        printf("Rotacao a esquerda em %d\n", node->data); // c) Qual rotação foi realizada, se necessária
        return leftRotate(node);
    }

    // Retorna o ponteiro do nó (não alterado)
    return node;
}

// Função para imprimir a árvore em ordem
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int values[] = {10, 20, 30, 40, 35};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
        printf("Arvore em ordem: ");
        inorder(root);
        printf("\n");
    }

    return 0;
}

