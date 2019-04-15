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

void bestFitSearch(vector<pair<double, double>> param, double maxWeight) {
	// param: pares da forma valor - peso
	vector<pair<double, int>> costPerWeight;
	for(int i = 0; i < (int)param.size(); i++) {
		costPerWeight.push_back(make_pair(param[i].first/param[i].second, 0));
		// cout << "cost/weight: " << costPerWeight[i].first << "\n";
	}

	double currWeight = 0.0;
	int loop_control = 1;
	int neighbor = findMaxPos(costPerWeight);
	vector<int> selected;

	while(loop_control) {

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

	cout << "Carga total: " << currWeight << "\n";
	cout << "Itens: " << "\n";

	for(int i = 0; i < (int)selected.size(); i++) {
		cout << "id: " << selected[i] << " | valor: " << param[selected[i]].first << " | peso: " << param[selected[i]].second << "\n";
	}
}


pair<double, int> iterativeBlindSearch(vector<pair<double, double>> param, double maxWeight){
	// Calculates the number of possibilities
	int maxNum = 1 << param.size();

	// Iterate through all of the possibilities
	int maxPoss = 0;
	double maxValue = -1;
	for(int curr=0;curr<maxNum;curr++){
		double currWeight = 0, currValue = 0;

		// Iterate through each bit of the current number
		for(int bit=0;bit<(int)param.size();bit++){
			// If the I'th term of the array is in this possibility, put it in the knapsack
			if(((curr >> bit) & 1) == 1){
				currWeight += param[bit].second;
				currValue += param[bit].first;
			}
		}

		/*
		 * Tests if this possibility is a valid one.
		 *  If it is and the value is the biggest until now:
		 * 	Store the current value as the maximum
		 * 	Store the current possibility as the best
		 */
		if(currWeight <= maxWeight && currValue > maxValue){
			cerr << "Change maxValue = " << currValue << endl;
			maxPoss = curr;
			maxValue = currValue;
		}
	}

	/* Testing if the answer is ok */
	bitset<8>answ(maxPoss);
	cerr << endl << "Answer " << answ << endl;

	cout << "Max Value: " << maxValue << endl;
	// Returns the pair maxValue, maxPoss so the answer can be rebuilt
	return make_pair(maxValue, maxPoss);
}


int main(int argc, char *argv[]){
	/*
	 * Declares vector of objects and the (n)umber of objects
	 */
	vector <pair<double, double>> valueWeight;
	int n;
	double maxWeight;

	// Interface com arquivo
	fstream inFile;


	/*
	 * Scans the n objects and pushes it into the vector
	 * The objects are composed by it's value and weight
	 */
	double tmp1, tmp2;
	if(argc < 2){
		cout << "Please insert the number of elements and the max supported weight by the knapsack" << endl;
		cin >> n >> maxWeight;
		cout << "Please insert the pair of value weight at the knapsack" << endl;
	}else{
		inFile.open(argv[1], ios::in);
		if(!inFile.is_open()){
			cout << "Error openning file!" << endl;
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

	clock_t start = clock();
	iterativeBlindSearch(valueWeight, maxWeight);
	clock_t end = clock();

	cout << "[EXECUTION TIME] Blind search: " << 1000*(float)(end-start)/CLOCKS_PER_SEC  << " ms \n\n";

	start = clock();
	bestFitSearch(valueWeight, maxWeight);
	end = clock();

	cout << "[EXECUTION TIME] Best fit: " << 1000*(float)(end-start)/CLOCKS_PER_SEC  << " ms \n\n";

	return 0;
}
