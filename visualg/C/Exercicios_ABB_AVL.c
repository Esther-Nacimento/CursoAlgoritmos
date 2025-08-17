/*Exercício 1: crie um programa em C/C++ que lê números inteiros e os insere em uma ABB até que o usuário digite 0 (zero). 
Ao final, imprima os números da árvore em ordem crescente.

Exercício 2: altere o programa anterior para, ao final da inclusão, solicitar que número deve ser excluído, até que o usuário digite 0 (zero).
 Após cada exclusão, imprima os números da ABB em ordem crescente, informando também qual o valor da raiz.
 
 Esther Fernandes do Nascimento 
Matricula: 1240206904*/


#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Função para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um novo valor na ABB
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    
    return root;
}

// Função para encontrar o nó com o valor mínimo
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Função para excluir um valor da ABB
Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        return root; // Retorna se a árvore estiver vazia
    }

    // Se o valor a ser excluído for menor que o valor da raiz
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } 
    // Se o valor a ser excluído for maior que o valor da raiz
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } 
    // Se o valor for igual ao valor da raiz, este é o nó a ser excluído
    else {
        // Nó com apenas um filho ou nenhum
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Nó com dois filhos: pega o menor valor do subárvore da direita
        Node* temp = findMin(root->right);
        root->data = temp->data; // Copia o valor do nó mínimo
        root->right = deleteNode(root->right, temp->data); // Exclui o nó mínimo
    }
    return root;
}

// Função para imprimir a árvore em ordem crescente
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int number;

    printf("Digite numeros inteiros (0 para sair):\n");
    while (1) {
        scanf("%d", &number);
        if (number == 0) {
            break;
        }
        root = insert(root, number);
    }

    printf("Numeros em ordem crescente:\n");
    inorder(root);
    printf("\n");

    // Exclusão de nós
    while (1) {
        printf("Digite um numero para excluir (0 para sair):\n");
        scanf("%d", &number);
        if (number == 0) {
            break;
        }
        root = deleteNode(root, number); // Exclui o número da árvore
        printf("Numeros em ordem crescente apos exclusao:\n");
        inorder(root);
        printf("\n");
        if (root != NULL) {
            printf("Valor da raiz: %d\n", root->data);
        } else {
            printf("A arvore esta vazia.\n");
        }
    }

    return 0;
}
