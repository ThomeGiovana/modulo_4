#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

float Leitura(float sValue)
{
    // cin >> sValue;
    // cout << typeid(sValue).name() << sValue << endl;
    return sValue;
}

int main()
{
    int sValue;
    cout << "Type a sensor value: " << endl;
    cin >> sValue;
    Leitura(sValue);
}