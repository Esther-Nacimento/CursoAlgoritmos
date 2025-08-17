Algoritmo "dados_pessoais"

Var
    idade : inteiro // variaveis e tipo
    salario1, salario2 : real
    nome : caractere

Inicio

     escreva("Digite seu nome: ")  //saida de dados
     leia(nome) // entrada de dados
     escreva("Digite sua idade: ")
     leia(idade)
     escreval("Digite quanto voce ganhou nos dois ultimos meses: ")
     leia(salario1)
     leia(salario2)
     
     escreval //pular linha
     
     escreval("DADOS DIGITADOS: ")
     escreval("NOME = ", nome)
     escreval("IDADE = ", idade)
     escreval("SALARIO 1: R$ ", salario1:8:2)
     escreval("SALARIO 2: R$ ", salario2:8:2)
     


Fimalgoritmo