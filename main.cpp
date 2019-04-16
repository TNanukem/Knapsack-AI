/*
	Trabalho 1 de Inteligência Artificial
	Resolução do problema de uma mochila binária (knapsack)
	utilizando algoritmos de busca cega e busca heurística.

	Desenvolvido por:
	Augusto Ribeiro (https://github.com/GuttinRibeiro)
	Bruno Arantes (https://github.com/brunoaamello)
	Estevam Arantes (https://github.com/Es7evam)
	Henrique Andrews (https://github.com/AndrewsHPM)
	Henry Suzukawa (https://github.com/HSuzu)
	Osmar Chen (https://github.com/osmarchen)
	Tiago Toledo Jr (https://github.com/TNanukem)

	Este arquivo é o executavel da interface com o usuário, utilize-o para
	verificar o funcionamento do trabalho.

	Você pode utilizar algum dos casos de teste disponíveis na pasta tests.

*/
#include "searches.h"

int main(int argc, char *argv[]){

	// Declara um vetor de objetos e o (n)úmero de objetos

	vector <pair<double, double>> valueWeight;
	int n;
	double maxWeight;

	// Interface com arquivo
	fstream inFile;


	 /* Escaneia os n objetos e insere eles no vetor
	 * Os objetos são compostos pelo par valor e peso
	 */

	double tmp1, tmp2;
	if(argc < 2){
		cout << "Por favor insira o numero maximo de elementos e o peso maximo da mochila" << endl;
		cin >> n >> maxWeight;
		cout << "Por favor, insira os pares valor peso dos itens a serem colocados na mochila" << endl;
	}else{
		inFile.open(argv[1], ios::in);
		if(!inFile.is_open()){
			cout << "Erro ao abrir o arquivo!" << endl;
			exit(1);
		}
		inFile >> n >> maxWeight;
	}
	if(argc < 2){
		for(int i=0;i<n;i++){
			cin >> tmp1 >> tmp2;
			valueWeight.push_back(make_pair(tmp1, tmp2));
		}
	}else{
		for(int i=0;i<n;i++){
			inFile >> tmp1 >> tmp2;
			valueWeight.push_back(make_pair(tmp1, tmp2));
		}
	}

	// Execução da Busca Cega
	clock_t start = clock();
	iterativeBlindSearch(valueWeight, maxWeight);
	clock_t end = clock();

	cout << "[TEMPO DE EXECUCAO] Blind search: " << 1000*(float)(end-start)/CLOCKS_PER_SEC  << " ms \n\n";

	// Execução do algoritmo Best-Fit
	start = clock();
	bestFitSearch(valueWeight, maxWeight);
	end = clock();

	cout << "[TEMPO DE EXECUCAO] Best fit: " << 1000*(float)(end-start)/CLOCKS_PER_SEC  << " ms \n\n";

	return 0;
}
