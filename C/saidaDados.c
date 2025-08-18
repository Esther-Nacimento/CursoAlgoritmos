#include <stdio.h>

int main()
{

    //Declarando as variaveis
    int idade;
    double salario;
    char nome[50];
    char sexo;

    //Atribuindo valores
    idade = 32;
    salario = 4560.9;
    strcpy(nome, "Maria Silva");
    sexo = 'F';

    //Saidade de dados. Uso de placeholder
    printf("A funcionaria %s, sexo %c, ganha %.2lf e tem %d anos\n", nome, sexo, salario, idade);


    return 0;

}
