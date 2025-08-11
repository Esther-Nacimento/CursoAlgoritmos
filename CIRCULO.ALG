Algoritmo "circulo"
//Fazer um programa para ler o valor "r" do raio de um círculo,
// e depois mostrar o valor da área do
//círculo com três casas decimais. A fórmula da área do círculo
//é a seguinte: area = pi * r2
//. Você pode usar o valor de pi fornecido pela biblioteca da
//sua linguagem de programação, ou então, se preferir, use
//diretamente o valor 3.14159.

//Exemplo 1:
//Digite o valor do raio do circulo: 2.0
//AREA = 12.566

//Exemplo 2:
//Digite o valor do raio do circulo: 13.2
//AREA = 547.391


Var
   // Variaveis e tipos
   area, r : real


Inicio

   // Saída de dados
   escreva("Digite o valor do raio do circulo: ")
   // Entrada de dados
   leia(r)

   // Atribuição
   area <- Pi * Exp(r, 2.0) // Processamento

   escreva("AREA = ", area:8:3)

Fimalgoritmo