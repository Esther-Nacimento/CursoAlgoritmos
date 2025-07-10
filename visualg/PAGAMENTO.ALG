Algoritmo "pagamento"
//Fazer um programa para ler o nome de um(a) funcionário(a),
//o valor que ele(a) recebe por hora, e a
//quantidade de horas trabalhadas por ele(a).
//Ao final, mostrar o valor do pagamento do funcionário com
//uma mensagem explicativa, conforme exemplo.

//Exemplo 1:
//Nome: Joao Silva
//Valor por hora: 50.00
//Horas trabalhadas: 60
//O pagamento para Joao Silva deve ser 3000.00

//Exemplo 2:
//Nome: Maria Dias
//Valor por hora: 60.00
//Horas trabalhadas: 100
//O pagamento para Maria Dias deve ser 6000.00
Var
   // Declarando as variaveis
   nome : caracter
   valorHora, pagamento : real
   horasTrabalhadas : inteiro


Inicio

   // Saida de dados
   escreva("Nome: ")
   // Entrada de dados
   leia(nome)
   
   escreva("Valor por hora: ")
   leia(valorHora)
   
   escreva("Horas trabalhdas: ")
   leia(horasTrabalhadas)
   
   // Processamento de dados - atribuição
   pagamento <- valorHora * horasTrabalhadas
   
   escreva("O pagamento para ", nome, " deve ser R$", pagamento:8:2)
   


Fimalgoritmo