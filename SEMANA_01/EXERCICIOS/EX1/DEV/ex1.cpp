#include <iostream>
#include <string>

using namespace std;

void Result(int min, int max, int n)
{
    // calcula o módulo da distância de n até min e max
    float proxMin, proxMax, nMaisProx, somaProx, prox;
    proxMin = n - min;
    proxMax = n - max;
    if (proxMin < 0)
    {
        proxMin = proxMin * (-1);
    }
    if (proxMax < 0)
    {
        proxMax = proxMax * (-1);
    }

    // calculo de porcentagem
    somaProx = proxMax + proxMin;

    // define que número está mais próximo
    if (proxMax < proxMin)
    {
        nMaisProx = proxMax;
        prox = (100 * nMaisProx) / somaProx;
        cout << "'n' is " << 100 - prox << " percent closer to your maximum value" << endl;
    }
    else if (proxMin < proxMax)
    {
        nMaisProx = proxMin;
        prox = (100 * nMaisProx) / somaProx;
        cout << "'n' is " << 100 - prox << " percent closer to your minimum value" << endl;
    }
    else if (proxMin == proxMax)
    {
        cout << "Proximidade igual! 50%" << endl;
    }
};

int main()
{
    float min, max, n = 0;
    cout << "Type a minimum value: " << endl;
    cin >> min;
    cout << "Type a maximum value: " << endl;
    cin >> max;
    cout << "Type a number in between: " << endl;
    cin >> n;
    Result(min, max, n);
}