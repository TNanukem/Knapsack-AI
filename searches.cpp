#include "searches.h"

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
	cout << "\nEXECUTANDO A BEST-FIT SEARCH" << "\n";
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
	//cout << "Carga total: " << currWeight << "\n";
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
	cout << "\nEXECUTANDO A BLIND SEARCH ITERATIVA" << "\n";

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
	//cerr << endl << "Resposta binaria: " << answ << endl;

	//cout << "Valor maximo: " << maxValue << endl;

	cout << "Numero de Passos:" << count << "\n";

	cout << "Itens: " << "\n";
	for(int i = 0; i < (int)answ.size(); i++){
		if(answ[i] == 1)
			cout << "id: " << i << " | valor: " << param[i].first << " | peso: " << param[i].second << "\n";
	}

	// Retorna o par maxValue, maxPoss para que a resposta possa ser reescrita
	return make_pair(maxValue, maxPoss);
}

// Retorna o valor máximo
double recursiveBlindSearch(vector<pair<double, double>> param, double maxWeight, int curIdx, double curWeight, double curValue, int *count){
	*count = *count + 1;
	if(curIdx >= param.size()){
		return 0;
	}
	if(curWeight > maxWeight){
		return -0x3f3f3f3f;
	}
	double valcoloca = recursiveBlindSearch(param, maxWeight, curIdx+1, curWeight + param[curIdx].second, curValue + param[curIdx].first, count);
	double valncoloca = recursiveBlindSearch(param, maxWeight, curIdx+1, curWeight, curValue, count);
	return max(valcoloca, valncoloca);
}
