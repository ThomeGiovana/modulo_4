#include <iostream>

using namespace std;

int main()
{
    // declaração de variáveis
    string nome = "";
    char caracter = 'j';
    int n = 9, idade;
    // número real
    float altura = 0.0f;
    // número real sem o "f"
    double peso = 0.0;

    // output
    cout << "Type your name: " << endl;
    // input
    cin >> nome;
    cout << "Type your age: " << endl;
    cin >> idade;
    cout << "Type your weight: " << endl;
    cin >> peso;
    cout << "Type your height: " << endl;
    cin >> altura;

    cout << "Your name: " << nome << endl << "Your age:" << idade << endl << "Your weight and height: " << peso + altura << endl;
}