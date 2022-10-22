#include <iostream>
#include <string>
#include <vector>

using namespace std;

void InsereVetor(int elemento, int valorMax, int lastPos, int* Vetor){
    // Escreva a função aqui
    if(lastPos < valorMax -1){
        Vetor[lastPos+1] = elemento;
    } else {
        cout<< "Erro: valorMax:" << valorMax <<" lastPost + 1 (indice): "<< lastPos + 1 << endl;
    }
}

int main(){
  int valorMax = 10;
  int lastPos = -1;
  int Numbers[valorMax];
  
  InsereVetor(9, valorMax, lastPos, Numbers);
  lastPos = lastPos + 1;

  InsereVetor(8, valorMax, lastPos, Numbers);
  lastPos = lastPos + 1;

  InsereVetor(7, valorMax, lastPos, Numbers);
  lastPos = lastPos + 1;

  InsereVetor(6, valorMax, lastPos, Numbers);
  lastPos = lastPos + 1;

  InsereVetor(5, valorMax, lastPos, Numbers);
  lastPos = lastPos + 1;

  InsereVetor(4, valorMax, lastPos, Numbers);
  lastPos = lastPos + 1;

  InsereVetor(3, valorMax, lastPos, Numbers);
  lastPos = lastPos + 1;
  
  InsereVetor(2, valorMax, lastPos, Numbers);
  lastPos = lastPos + 1;

  InsereVetor(1, valorMax, lastPos, Numbers);
  lastPos = lastPos + 1;

  InsereVetor(0, valorMax, lastPos, Numbers);
  lastPos = lastPos + 1;

  InsereVetor(100, valorMax, lastPos, Numbers);
  // valor esperado: mensagem de erro "Erro: valorMax: 10, lastPos + 1 (indice): 10"
  
  cout << Numbers[0] << endl; // valor esperado: 9
  cout << Numbers[1] << endl; // valor esperado: 8
  cout << Numbers[2] << endl; // valor esperado: 7
  cout << Numbers[3] << endl; // valor esperado: 6
  cout << Numbers[4] << endl; // valor esperado: 5
  cout << Numbers[5] << endl; // valor esperado: 4
  cout << Numbers[6] << endl; // valor esperado: 3
  cout << Numbers[7] << endl; // valor esperado: 2
  cout << Numbers[8] << endl; // valor esperado: 1
  cout << Numbers[9] << endl; // valor esperado: 0
};