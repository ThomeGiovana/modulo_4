#include <iostream>
#include <string>
#include <vector>

using namespace std;

int MaiorN(int d, int e, int t, int f)
{
    vector<int> valores;
    valores.push_back(d);
    valores.push_back(e);
    valores.push_back(t);
    valores.push_back(f);
    int m = valores.capacity();
    int i, maiorValor;
    maiorValor = valores[0];
    for (i = 0; i < m; i++)
    {
        if (valores[i] > maiorValor)
        {
            maiorValor = valores[i];
        }
    }
    return maiorValor;
}

char MaiorLado(int d, int e, int t, int f)
{
    vector<int> valores;
    valores.push_back(d);
    valores.push_back(e);
    valores.push_back(t);
    valores.push_back(f);
    int m = valores.capacity();
    int i, maiorValor;
    maiorValor = valores[0];
    for (i = 0; i < m; i++)
    {
        if (valores[i] > maiorValor)
        {
            maiorValor = valores[i];
        }
    }

    if (maiorValor == valores[0])
    {
        return 'd';
    }
    else if (maiorValor == valores[1])
    {
        return 'e';
    }
    else if (maiorValor == valores[2])
    {
        return 't';
    }
    else if (maiorValor == valores[3])
    {
        return 'f';
    }
}

int main()
{
    cout << MaiorN(1, 17, 3, 16) << endl;
    cout << MaiorLado(1, 17, 3, 16);
}