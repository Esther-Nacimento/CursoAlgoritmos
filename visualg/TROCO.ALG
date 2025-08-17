Algoritmo "troco"

//Fazer um programa para calcular o troco no processo de pagamento de um produto de uma mercearia.
//O programa deve ler o preço unitário do produto, a quantidade de unidades compradas deste produto,
//e o valor em dinheiro dado pelo cliente (suponha que haja dinheiro suficiente). Seu programa deve
//mostrar o valor do troco a ser devolvido ao cliente.

//Preço unitário do produto: 8.00
//Quantidade comprada: 2
//Dinheiro recebido: 20.00
//TROCO = 4.00

Var
   // Declarando variaveis e tipos
   precoUni, valorPg, precoTotal, troco : real
   quantComp  : inteiro


Inicio
  // Saida de dados
  escreva("Preço unitário do produto: ")
  // Entrada de dados
  leia(precoUni)
  
  escreva("Quantidade comprada: ")
  leia(quantComp)
  
  escreva("Dinheiro recebido: ")
  leia(valorPg)
  
  // Atribuição
  precoTotal <- precoUni * quantComp //Processamento de dados
  troco <- valorPg - precoTotal
  
  escreva("TROCO = ", troco:2:2)


Fimalgoritmo