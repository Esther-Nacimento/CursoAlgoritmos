Algoritmo "idades"

//Fazer um programa para ler o nome e idade de duas pessoas. Ao final mostrar uma mensagem com os
//nomes e a idade média entre essas pessoas, com uma casa decimal, conforme exemplo.

Var
   // Tipos e variaveis
   nome1, nome2 : caractere
   idade1, idade2 : inteiro
   mediaIdades : real
   


Inicio

      //   Saida de dados
      escreval("Dados da primeira pessoa:")
      escreva("Nome: ")
      // Entrada de dados
      leia(nome1)
      
      escreva("Idade: ")
      leia(idade1)
      
      //   Saida de dados
      escreval("Dados da segunda pessoa:")
      escreva("Nome: ")
      // Entrada de dados
      leia(nome2)

      escreva("Idade: ")
      leia(idade2)
      
      //   Atribuição
      mediaIdades <- (idade1 + idade2) / 2 // Processamento de dados
      
      //    Saida de dados
      escreval("A idade media de ", nome1, " e ", nome2, " é de ", mediaIdades:2:1, " anos.")

      


Fimalgoritmo