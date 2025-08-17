Algoritmo "area"

Var
   b1, b2, h, area : real // variaveis e tipos
   

Inicio
   //atribuição de valore as variaveis
   b1 <- 6.0
   b2 <- 8.0
   h <- 5.0
   area <- (b1 + b2) / 2.0 * h  //processamento de dados

   // Quando acontecer de uma divisão tiver resto, usar o operador de divisão inteira \
   // não podemos atribuir um valor real em uma variavel do tipo inteiro, nesses casos usar a função int(), usamos ela para não perder informação
   
   //saida de dados
   escreval(area)
   


Fimalgoritmo