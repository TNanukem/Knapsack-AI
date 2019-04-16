#include "searches.h"

void printResult(vector<pair<double,double>> weights, clock_t start, clock_t end, vector<int> ids, int count){
	cout << "Numero de passos: " << count << "\n";
	cout << "Itens: " << "\n";
	int valueSum = 0;
	int weight = 0;

	for(int i = 0; i < ids.size(); i++){
		cout << "id: " << ids[i] << " | valor: " << weights[ids[i]].first << " | peso: " << weights[ids[i]].second << "\n";
		valueSum +=  weights[ids[i]].first;
		weight   += weights[ids[i]].second;
	}
	cout << "Valor Total: " << valueSum << ", Peso Total: " << weight << "\n";
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


/* Branch and Bound */
/* Função de comparação de pesos proporcionais
 * true é retornado se o primeiro argumento deve ser posicionado antes do que o segundo */
bool weightsCmp(pair<double, int> &w1, pair<double, int> &w2) {
	return w1.first > w2.first;
}

/* Implementação que busca solução relaxada do problema
 * de mochila binária (ou seja, solução do problema de
 * mochila inteira)
 * Retorno: true se o problema é factível */
bool relaxedKsnapsack (vector<pair<double, double> > &param, double maxWeight, vector<double> &qtd, vector<bool> fixedValues, int *count, double *finalWeight) {
	if(maxWeight < 0) {
		return false;
	}

	/* Vetor que guarda o valor proporcial (valor/peso) e a id do objeto */
	vector<pair<double, int>> proportionalValue;
	proportionalValue.reserve(param.size());

	for(int i = 0; i < param.size(); i++) {
//		*count++;
		double pweight;
		if(fixedValues[i] == false) { // se o item não foi selecionado previamente
			pweight  = param[i].first/param[i].second;
		} else { // se o item já foi selecionado preciamente, ele será desconsiderado.
			pweight  = 0;
		}
		proportionalValue.push_back(make_pair(pweight, i));
	}

	sort(proportionalValue.begin(), proportionalValue.end(), weightsCmp);

	if(proportionalValue[0].first == 0) {
		return false;
	}

	float bag_weight = 0;
	int bag_full = 1;
	for(int i = 0; i < proportionalValue.size(); i++) {
		*count++;
		int idx = proportionalValue[i].second;
		if(fixedValues[idx] == false) {
			if(bag_full) {
				int weight = param[idx].second;
				if(weight < maxWeight) {
					maxWeight -= weight;
					bag_weight += weight;
					qtd[idx] = 1;
				} else {
					qtd[idx] = maxWeight/weight;
					bag_weight += maxWeight;
					maxWeight = 0;
					bag_full = 0;
				}
			} else {
				qtd[idx] = 0;
			}
		}
	}

	*finalWeight = bag_weight;

	return true;
}

void branchAndBound_recursive(vector<pair<double, double>> &param, double maxWeight, vector<double> &qtd, vector<bool> &fixedValues, int *count, double *currMax, vector<int> &currSolution) {
	double weight = 0;

	bool isPossible = relaxedKsnapsack(param, maxWeight, qtd, fixedValues, count, &weight);

	/* Teste de sondagem.. Se o problema for infactível ou a solução é pior do que
	 * uma solução já existente, a solução não é desenvolvida */
	if(isPossible == false || weight < *currMax) {
		return;
	}

	bool allInteger = true;
	vector<pair<double, int>> dist; // vetor de distancia de 0.5 até qtd
	dist.reserve(qtd.size());
	for(int i = 0; i < qtd.size(); i++) {
		if(qtd[i] == 0 || qtd[i] == 1) {
			dist.push_back(make_pair(0.5, i));
		} else {
			allInteger = false;
			dist.push_back(make_pair(abs(0.5 - qtd[i]), i));
		}
	}

	if(allInteger) { // se todos são inteiros, achamos uma solução para o problema
		if(weight > *currMax) { // se a solução é melhor do que já temos, guardamos essa solução
			currSolution.clear();
			*currMax = weight;
			for(int i = 0; i < qtd.size(); i++) {
				if(qtd[i] == 1) {
					currSolution.push_back(i);
				}
			}
		}
	} else { // se a solução tem um valor não inteiro ..
		// selecionamos o item mais fracionado (mais perto de 0.5) ..
		sort(dist.begin(), dist.end(), weightsCmp);
		int idx = dist.back().second;
		fixedValues[idx] = true;

		// e rodamos o algorítmo novamente setando a quantidade desse item
		qtd[idx] = 0;
		branchAndBound_recursive(param, maxWeight, qtd, fixedValues, count, currMax, currSolution);

		qtd[idx] = 1;
		double newMaxWeight = maxWeight - param[idx].second;
		branchAndBound_recursive(param, newMaxWeight, qtd, fixedValues, count, currMax, currSolution);

		fixedValues[idx] = false;
	}
}

void branchAndBound(vector<pair<double, double>> param, double maxWeight, vector<int> &idx, int *count) {
	double currMax = 0;
	vector<int> bestSolution;
	// bestSolution.reserve(param.size());

	vector<bool> fixedValues;
	fixedValues.reserve(param.size());

	vector<double> qtd;
	qtd.reserve(param.size());

	for(int i = 0; i < param.size(); i++) {
		fixedValues.push_back(false);
		qtd.push_back(0);
	}

	branchAndBound_recursive(param, maxWeight, qtd, fixedValues, count, &currMax, bestSolution);

	idx = bestSolution;
}
