Algoritmo "consumo"
//Fazer um programa para ler a distância total (em km) percorrida por
//um carro, bem como o total de combustível gasto por este carro ao
//percorrer tal distância. Seu programa deve mostrar o consumo
//médio do carro, com três casas decimais.

//Exemplo 1:
//Distancia percorrida: 500
//Combustível gasto: 38.5
//Consumo medio = 12.987

//Exemplo 2:
//Distancia percorrida: 1108
//Combustível gasto: 71.4
//Consumo medio = 15.518

Var
   //Declarando as variaveis
   distancia  : inteiro
   combustivel, consMedio : real
   
Inicio
  //Saida de dados
  escreva("Distancia pecorrida: ")
  
  //Entrada de dados
  leia(distancia)
  
  escreva("Combustivel gasto: ")
  leia(combustivel)
  
  //Processamento de dados
  consMedio <- distancia / combustivel

  escreva("Consumo medio = ", consMedio:8:3)
  
Fimalgoritmo