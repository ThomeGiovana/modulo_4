#include <iostream>

using namespace std;
int vectorName[10] = {0,1,2,3,4,5,6,7,8,9};

int *retorna_vetor(){
    int *meuPonteiro = &vectorName[0];
    return meuPonteiro;
}


int main(){
    cout << retorna_vetor();

}

