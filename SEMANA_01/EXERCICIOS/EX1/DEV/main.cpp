#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1
// float converteSensor(int min, int max, int n)
// {
// 	// calcula o módulo da distância de n até min e max
// 	float proxMin, proxMax, nMaisProx, somaProx, prox;
// 	proxMin = n - min;
// 	proxMax = n - max;
// 	if (proxMin < 0)
// 	{
// 		proxMin = proxMin * (-1);
// 	}
// 	if (proxMax < 0)
// 	{
// 		proxMax = proxMax * (-1);
// 	}

// 	// calculo de porcentagem
// 	somaProx = proxMax + proxMin;

// 	// define que número está mais próximo
// 	if (proxMax < proxMin)
// 	{
// 		nMaisProx = proxMax;
// 		prox = (100 * nMaisProx) / somaProx;
// 		// cout << "'n' is " << 100 - prox << " percent closer to your maximum value" << endl;
// 		return 100 - prox;
// 	}
// 	else if (proxMin < proxMax)
// 	{
// 		nMaisProx = proxMin;
// 		prox = (100 * nMaisProx) / somaProx;
// 		// cout << "'n' is " << 100 - prox << " percent closer to your minimum value" << endl;
// 		return 100 - prox;
// 	}
// 	else if (proxMin == proxMax)
// 	{
// 		// cout << "Proximidade igual! 50%" << endl;
// 		return 50.0;
// 	}
// };
float converteSensor(int min, int max, int n)
{
	int range = 0;
	int resultado = 0;
	range = max - min;
	resultado = n * 100 / range;
	return resultado;
}

// 2
float Leitura()
{
	float sValue;
	cin >> sValue;
	// cout << typeid(sValue).name() << sValue << endl;
	return sValue;
}

// 3
int InsereVetor(int elemento, int valorMax, int lastPos, int *Vetor)
{
	// Escreva a função aqui
	if (lastPos < valorMax - 1)
	{
		Vetor[lastPos + 1] = elemento;
	}
	else
	{
		cout << "Erro: valorMax:" << valorMax << " lastPost + 1 (indice): " << lastPos + 1 << endl;
	}
	return lastPos + 1;
}

// 4
// int MaiorN(int d, int e, int f, int t)
void MaiorN(int *vetor, int maiorDirecao)
{
	string posicoes[4] = {"Right", "Left", "Front", "Back"};
	string maiorPosicao;
	int maior = *vetor;
	for (int i = 0; i < 4; i++)
	{
		if (vetor[i] > maiorDirecao)
		{
			maiorDirecao = vetor[i];
			maiorPosicao = posicoes[i];
		}
	}
	// printf("Movimentando para %s distancia = %i\n", maiorPosicao, maiorDirecao);
	cout << "Moving towards: " << maiorPosicao << endl
		 << "Distance: " << maiorDirecao << endl;
}

// 5
int leComando()
{
	bool condicao = true;
	cout << "Do you want to continue?" << endl;
	cin >> condicao;
	if (condicao == 0)
	{
		cout << "End of loop!" << endl;
	}
	return condicao;
}

int dirige(int *v, int maxv)
{
	int maxVetor = maxv;
	int *vetorMov = v;
	int posAtualVetor = 0;
	int dirigindo = 1;
	while (dirigindo)
	{
		cout << "Type right value: " << endl;
		int medida = Leitura();
		medida = converteSensor(0, 830, medida);
		posAtualVetor = InsereVetor(medida, maxVetor, posAtualVetor, vetorMov);
		// posAtualVetor++;

		cout << "Type left value: " << endl;
		medida = Leitura();
		medida = converteSensor(0, 830, medida);
		posAtualVetor = InsereVetor(medida, maxVetor, posAtualVetor, vetorMov);
		// posAtualVetor++;

		cout << "Type front  value: " << endl;
		medida = Leitura();
		medida = converteSensor(0, 830, medida);
		posAtualVetor = InsereVetor(medida, maxVetor, posAtualVetor, vetorMov);
		// posAtualVetor++;

		cout << "Type back value: " << endl;
		medida = Leitura();
		medida = converteSensor(0, 830, medida);
		posAtualVetor = InsereVetor(medida, maxVetor, posAtualVetor, vetorMov);
		// posAtualVetor++;

		dirigindo = leComando();
	}
	return posAtualVetor;
}

// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado
// na maior distância a cada movimento
void percorre(int *v, int tamPercorrido)
{
	int *vetorMov = v;
	int maiorDir = 0;

	for (int i = 0; i < tamPercorrido; i += 4)
	{
		MaiorN(&(vetorMov[i]), maiorDir);
	}
}

int main(int argc, char **argv)
{
	int maxVetor = 100;
	int vetorMov[400];
	int posAtualVet = 0;

	posAtualVet = dirige(vetorMov, maxVetor);
	percorre(vetorMov, posAtualVet);

	return 0;
}