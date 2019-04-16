#include "searches.h"

void printResult(vector<pair<double,double>> weights, clock_t start, clock_t end, vector<int> ids, int count){
	cout << "Numero de passos: " << count << "\n";
	cout << "Itens: " << "\n";
	for(int i = 0; i < ids.size(); i++){
		cout << "id: " << ids[i] << " | valor: " << weights[ids[i]].first << " | peso: " << weights[ids[i]].second << "\n";
	}
	cout << "[TEMPO DE EXECUCAO]: " << 1000*(float)(end-start)/CLOCKS_PER_SEC  << " ms \n\n";
}

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

void bestFitSearch(vector<pair<double, double>> param, double maxWeight, vector<int> &ids, int *count) {
	// param: pares da forma valor - peso
	vector<pair<double, int>> costPerWeight;
	// Monta um vetor com valor/peso para realizar uma heurística gulosa
	for(int i = 0; i < (int)param.size(); i++) {
		costPerWeight.push_back(make_pair(param[i].first/param[i].second, 0));
		// cout << "cost/weight: " << costPerWeight[i].first << "\n";
	}

	double currWeight = 0.0;
	int loop_control = 1;
	int number = 0;
	int neighbor = findMaxPos(costPerWeight);
	vector<int> selected;

	while(loop_control) {

		number++;

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

	*count = number;

	for(int i = 0; i < (int)selected.size(); i++) {
		ids.push_back(selected[i]);
	}
}


/* Implementação de uma busca cega para a resolução do problema. Recebe como argumentos
	de entrada a lista de objetos e o tamanho máximo da mochila. Então, itera sobre todas
	as possibilidades de inserção até encontrar a solução ótima.
*/
pair<double, int> iterativeBlindSearch(vector<pair<double, double>> param, double maxWeight, vector<int> &ids, int *count){

	// Calcula o número de possibilidades
	int maxNum = 1 << param.size();
	// Itera sobre todas as possibilidades
	int maxPoss = 0;
	int number = 0;
	double maxValue = -1;
	for(int curr=0;curr<maxNum;curr++){
		double currWeight = 0, currValue = 0;

		// Itera sobre cada bit do número atual
		for(int bit=0;bit<(int)param.size();bit++){
			number++;
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
	//cerr << endl << "Resposta binaria: " << answ << endl;

	//cout << "Valor maximo: " << maxValue << endl;

	for(int i = 0; i < (int)answ.size(); i++){
		if(answ[i] == 1){
			ids.push_back(i);
		}
	}
	*count = number;
	// Retorna o par maxValue, maxPoss para que a resposta possa ser reescrita
	return make_pair(maxValue, maxPoss);
}
