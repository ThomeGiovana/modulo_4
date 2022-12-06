#include <iostream>

int main(){
    // vetores (unidimensionais):
    // <tipo> nomeDoVetor[tamanho];
    int vectorName[10] = {0,1,2,3,4,5,6,7,8,9};
    char sentence[] = "Hello, world!";
    printf(sentence);
    
    //matrizes (bidimensionais):
    // <tipo> nomeDaMatriz[tamanhoLinhas][tamanhoColunas];
    int A[2][2];
    // armazenando na posição 1x2
    A[1][2] = 10;
    // inicialização na declaração
    int B[2][3] = {{1,2,3}, 
                   {4,5,6}};

}