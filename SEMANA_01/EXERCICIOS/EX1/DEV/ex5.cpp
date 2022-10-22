#include <iostream>
#include <string>

using namespace std;

int Continuar()
{
    bool condicao = true;
    while (condicao == 1)
    {
        cout << "Do you want to continue?" << endl;
        cin >> condicao;
        if (condicao == 0)
        {
            cout << "End of loop!";
            break;
        }
    }
}

int main()
{
    Continuar();
}