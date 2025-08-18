#include <stdio.h>   // Biblioteca com comandos de entrada e sa�da (printf, scanf, etc.)
#include <string.h>  // Biblioteca com fun��es para manipula��o de strings (strlen, strcpy, strcat, strcmp, etc.)


int main()
{

    //Declarando as variaveis
    int idade;
    double salario, altura;
    char genero;
    char nome[50]; //Vetor de caracteres[]

    //Atribuindo valores as varaiaveis
    idade = 20;
    salario = 5800.5;
    altura = 1.63;
    genero = 'F';
    strcpy(nome, "Maria Silva"); //Fun��o "strcpy", por isso usamos <string.h>

    //Sa�da de dados
    printf("IDADE = %d\n", idade);
    printf("SALARIO = %.2lf\n", salario);
    printf("ALTURA = %.2lf\n", altura);
    printf("GENERO = %c\n", genero);
    printf("NOME = %s\n", nome);

    return 0;
}

