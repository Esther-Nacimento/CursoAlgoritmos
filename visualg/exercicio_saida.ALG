Algoritmo "loja"

Var
     produto1, produto2, genero : caractere
     preco1, preco2 : real
     idade, codigo : inteiro


Inicio
       //atribuição
       produto1 <- "Computador"
       produto2 <- "TV"
       preco1 <- 2100.5
       preco2 <- 1830.0
       idade <- 30
       codigo <- 5291
       genero <- "F"

       //saida de dados
      escreval("Produtos: ")  // imprime o titulo
      escreval("O produto ", produto1, " custa R$ ", preco1:8:2)
      escreval("O produto ", produto2, " custa R$ ", preco2:8:2)
      escreval   //pular linha
      escreval("Codigo = ", codigo)
      escreval
      escreval("Dados da pessoa: genero ", genero,  " e idade ", idade)

Fimalgoritmo