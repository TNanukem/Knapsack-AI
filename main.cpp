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

*/
#include <bitset>
#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <time.h>
#include <fstream>

using namespace std;

int findMaxPos(vector<pair<double, int>> v) {
	// Formato de v: valor - validade. Validade = 0 => valor válido

	if(v.size() < 1) {
		return -1;
	}

	// Procura o primeiro valor válido no vetor repassado:
	int pos_max = 0;
	while (v[pos_max].second == 1 && pos_max < (int)v.size()) {
		pos_max++;
	}

	// Se todos os valores são inválidos:
	if(pos_max == (int)v.size()) {
		return -1;
	}

	// Acha a posição do maior valor dentre os valores válidos:
	for(int i = pos_max+1; i < (int)v.size(); i++) {
		if(v[i].second == 0 && v[i].first > v[pos_max].first) {
			pos_max = i;
		}
	}

	return pos_max;
}

/* Função que realiza a busca por meio do algoritmo Best-Fit levando em consideração
	a heurística de maximizar o quociente valor/peso. Recebe como argumentos de entrada
	o vetor de objetos e o tamanho máximo da mochila.
*/

void bestFitSearch(vector<pair<double, double>> param, double maxWeight) {
	cout << "\nEXECUTANDO A BEST-FIT SEARCH" << "\n\n";
	// param: pares da forma valor - peso
	vector<pair<double, int>> costPerWeight;

	// Monta um vetor com valor/peso para realizar uma heurística gulosa
	for(int i = 0; i < (int)param.size(); i++) {
		costPerWeight.push_back(make_pair(param[i].first/param[i].second, 0));
		// cout << "cost/weight: " << costPerWeight[i].first << "\n";
	}

	double currWeight = 0.0;
	int loop_control = 1;
	int neighbor = findMaxPos(costPerWeight);
	vector<int> selected;
	int count = 0;

	while(loop_control) {

		count++;

		//Marca como escolhido
		costPerWeight[neighbor].second = 1;

		//Checa se o escolhido pode ser adiconado
		if(currWeight + param[neighbor].second <= maxWeight) {
			currWeight += param[neighbor].second;
			selected.push_back(neighbor);
		}

		//Escolhe novo vizinho
		neighbor = findMaxPos(costPerWeight);

		//Condição de parada: não haver mais vizinhos possíveis
		if(neighbor == -1) {
			loop_control = 0;
		}
	}

	// Fazendo a impressão da resposta em tela
	cout << "Numero de Passos:" << count << "\n";
	cout << "Carga total: " << currWeight << "\n";
	cout << "Itens: " << "\n";

	for(int i = 0; i < (int)selected.size(); i++) {
		cout << "id: " << selected[i] << " | valor: " << param[selected[i]].first << " | peso: " << param[selected[i]].second << "\n";
	}
}


/* Implementação de uma busca cega para a resolução do problema. Recebe como argumentos
	de entrada a lista de objetos e o tamanho máximo da mochila. Então, itera sobre todas
	as possibilidades de inserção até encontrar a solução ótima.
*/
pair<double, int> iterativeBlindSearch(vector<pair<double, double>> param, double maxWeight){
	cout << "\nEXECUTANDO A BLIND SEARCH" << "\n";

	// Calcula o número de possibilidades
	int maxNum = 1 << param.size();
	int count = 0;

	// Itera sobre todas as possibilidades
	int maxPoss = 0;
	double maxValue = -1;
	for(int curr=0;curr<maxNum;curr++){
		double currWeight = 0, currValue = 0;

		// Itera sobre cada bit do número atual
		for(int bit=0;bit<(int)param.size();bit++){
			count++;
			// Se o I-ésimo termo do vetor está na possibilidade, coloque na mochila
			if(((curr >> bit) & 1) == 1){
				currWeight += param[bit].second;
				currValue += param[bit].first;
			}
		}

		  /* Testa se a possibilidade é válida.
		  *  Se ela for e o valor é o maior até agora:
		  * 	Armazena o valor atual como máximo
		  * 	Armazena a possibilidade atual como a melhor.
		  */

		if(currWeight <= maxWeight && currValue > maxValue){
			//cerr << "Change maxValue = " << currValue << endl;
			maxPoss = curr;
			maxValue = currValue;
		}
	}

	// Testando se a solução é válida
	bitset<8>answ(maxPoss);

	// Fazendo a impressão da resposta em tela
	cerr << endl << "Resposta binaria: " << answ << endl;

	cout << "Valor maximo: " << maxValue << endl;

	cout << "Numero de Passos:" << count << "\n";

	cout << "Itens: " << "\n";
	for(int i = 0; i < (int)answ.size(); i++){
		if(answ[i] == 1)
			cout << "id: " << i << " | valor: " << param[i].first << " | peso: " << param[i].second << "\n";
	}

	// Retorna o par maxValue, maxPoss para que a resposta possa ser reescrita
	return make_pair(maxValue, maxPoss);
}


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
