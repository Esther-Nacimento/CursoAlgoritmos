Algoritmo "terreno"

//Fazer um programa para ler as medidas da largura e comprimento de um terreno retangular com uma
//casa decimal, bem como o valor do metro quadrado do terreno com duas casas decimais. Em seguida,
//o programa deve mostrar o valor da área do terreno, bem como o valor do preço do terreno, ambos com
//duas casas decimais, conforme exemplo.

//Digite a largura do terreno: 10.0
//Digite o comprimento do terreno: 30.0
//Digite o valor do metro quadrado: 200.00
//Area do terreno = 300.00
//Preco do terreno = 60000.00

Var
   largura, compri, metroQuad, area, preco : real //Variaveis e tipos


Inicio
    //Saída de dados
    escreva("Digite a largura do terreno: ")
    //Entrada de dados
    leia(largura)

    escreva("Digite o comprimento do terreno: ")
    leia(compri)
    
    escreva("Digite o valor do metro quadrado: ")
    leia(metroQuad)
    
    //atribuição de valores
    area <- largura * compri    //Processamento de dados
    preco <- area * metroQuad

    //saida de dados
    escreval("Area do terreno = ", area:8:2)
    escreval("Preco do terreno = ", preco:8:2)
    

Fimalgoritmo