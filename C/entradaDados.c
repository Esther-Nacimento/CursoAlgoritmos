#include <stdio.h>
#include <string.h>

int main()
{

    //Declarando as variaveis
    int idade;
    double salario, altura;
    char genero;
    char nome[50];

    //Entrada de dados
    printf("Digite o valor da idade: ");
    scanf("%d", &idade);

    printf("Digite o valor do salario: ");
    scanf("%lf", &salario);

    printf("Digite o valor da altura: ");
    scanf("%lf", &altura);

    printf("Digite o nome: ");
    scanf("%s", &nome);

    //Saidade de dados. Uso de placeholder
    printf("IDADE = %d\n", idade);
    printf("SALARIO = %.2lf\n", salario);
    printf("ALTURA = %.2lf\n", altura);
    printf("NOME = %s\n", nome);

    return 0;

}
