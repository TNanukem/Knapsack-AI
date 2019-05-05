/*
	Artificial Intelligence - Assignment 1
	Solving a knapsack problem using blind search and 
	heuristic search algorithms.

	Developed por:
	Augusto Ribeiro (https://github.com/GuttinRibeiro)
	Bruno Arantes (https://github.com/brunoaamello)
	Estevam Arantes (https://github.com/Es7evam)
	Henrique Andrews (https://github.com/AndrewsHPM)
	Henry Suzukawa (https://github.com/HSuzu)
	Osmar Chen (https://github.com/osmarchen)
	Tiago Toledo Jr (https://github.com/TNanukem)

	This archive runs the assignment with user interface to be tested.
*/
#include "searches.h"

int main(int argc, char *argv[]){

	// Declares a vector of objects and the (n)umber of objects

	vector <pair<double, double>> valueWeight;
	int n;
	double maxWeight;

	vector <int> ids;
	long long int count = 0;

	// Archive interface
	fstream inFile;


	 /* Scans the n objects defined by the pair (value, weigth)
	 */

	double tmp1, tmp2;
	if(argc < 2){
		cout << "Please insert the max number of ekements and the maximum weight of the knapsack" << endl;
		cin >> n >> maxWeight;
		cout << "Please insert the pair of value and weight of the itens to be inserted" << endl;
	}else{
		inFile.open(argv[1], ios::in);
		if(!inFile.is_open()){
			cout << "Error when opening the archive!" << endl;
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


	cout << "\nBLIND SEARCH" << "\n";
	clock_t start = clock();
	iterativeBlindSearch(valueWeight, maxWeight, ids, &count);
	clock_t end = clock();
	printResult(valueWeight, start, end, ids, count);
	ids.clear();

	cout << "\n BEST-FIT SEARCH" << "\n";
	start = clock();
	bestFitSearch(valueWeight, maxWeight, ids, &count);
	end = clock();

	printResult(valueWeight, start, end, ids, count);
	ids.clear();

	cout << "\n BRANCH AND BOUND DEPTH FIRST" << "\n";
	start = clock();
	branchAndBoundDepthFirst(valueWeight, maxWeight, ids, &count);
	end = clock();

	printResult(valueWeight, start, end, ids, count);
	ids.clear();

	cout << "\n BRANCH AND BOUND BREADTH FIRST" << "\n";
	start = clock();
	branchAndBoundBreadthFirst(valueWeight, maxWeight, ids, &count);
	end = clock();

	printResult(valueWeight, start, end, ids, count);
	ids.clear();
	return 0;
}
