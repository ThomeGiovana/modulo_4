#include <iostream>

int main()
{
    int n = 0;
    // o bloco só é executado se a condição for verdadeira
    while (n < 10)
    {
        printf("Menor que 10\n");
        n = n + 1;
    }
    // o bloco é executado no mínimo uma vez, independentemente se a condição é verdadeira ou não
    do
    {
        printf("Menor que 10\n");
        n = n + 1;
    } while (n < 10);

    const int c = 10;
    int i;
    for (i = 0; i < c; i++)
    {
        printf("Round: %d\n", i);
    }
}