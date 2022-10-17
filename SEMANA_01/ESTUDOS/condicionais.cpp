// biblioteca que permite leitura e escrita de informações
#include <iostream>
// namespace standart direciona você a um bloco de bibliotecas padrões
using namespace std;

int main()
{
    int n = 0;
    cout << "Type a number: ";
    cin >> n;
    if (n == 10)
    {
        cout << "Match!" << endl;
    }
    else
    {
        cout << "Not a match, try again!" << endl;
    }
}