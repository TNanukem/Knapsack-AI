/*
	Artificial Intelligence - Assignment 1
	Solving a knapsack problem using blind search and 
	heuristic search algorithms.

	Desenvolvido por:
	Augusto Ribeiro (https://github.com/GuttinRibeiro)
	Bruno Arantes (https://github.com/brunoaamello)
	Estevam Arantes (https://github.com/Es7evam)
	Henrique Andrews (https://github.com/AndrewsHPM)
	Henry Suzukawa (https://github.com/HSuzu)
	Osmar Chen (https://github.com/osmarchen)
	Tiago Toledo Jr (https://github.com/TNanukem)

	This archive generates a .csv to be analyzed.

*/
#include "searches.h"

int main(int argc, char *argv[]){

	vector <pair<double, double>> valueWeight;
	int n;
	double maxWeight;

	vector <int> ids;
	long long int count = 0;

	fstream inFile;

	double tmp1, tmp2;
	if(argc < 2){
		cin >> n >> maxWeight;
	}else{
		inFile.open(argv[1], ios::in);
		if(!inFile.is_open()){

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


	// Blind Search
	clock_t start = clock();
	iterativeBlindSearch(valueWeight, maxWeight, ids, &count);
	clock_t end = clock();

	cout << argv[1] << ","<< n << ",Blind Search," << count << "," << 1000*(float)(end-start)/CLOCKS_PER_SEC << ",";
	for(int i = 0; i < ids.size(); i++){
		cout << ids[i] << " ";
	}
	cout << ",";

	vector<int> right_answer = ids;
	for(int i = 0; i < right_answer.size(); i++){
		cout << right_answer[i] << " ";
	}
	cout << "\n";

	ids.clear();

	// Best-First
	start = clock();
	bestFitSearch(valueWeight, maxWeight, ids, &count);
	end = clock();

	cout << argv[1] <<"," << n << ",Best-Fit Search," << count << "," << 1000*(float)(end-start)/CLOCKS_PER_SEC << ",";
	for(int i = 0; i < ids.size(); i++){
		cout << ids[i] << " ";
	}
	cout << ",";
	for(int i = 0; i < right_answer.size(); i++){
		cout << right_answer[i] << " ";
	}
	cout << "\n";

	ids.clear();

	// Branch and Bound Depth First
	start = clock();
	branchAndBoundDepthFirst(valueWeight, maxWeight, ids, &count);
	end = clock();

	cout << argv[1] <<"," << n << ",B&B DFS," << count << "," << 1000*(float)(end-start)/CLOCKS_PER_SEC << ",";
	for(int i = 0; i < ids.size(); i++){
		cout << ids[i] << " ";
	}
	cout << ",";
	for(int i = 0; i < right_answer.size(); i++){
		cout << right_answer[i] << " ";
	}
	cout << "\n";

	ids.clear();

	// Branch and Bound Breadth First
	start = clock();
	branchAndBoundBreadthFirst(valueWeight, maxWeight, ids, &count);
	end = clock();

	cout << argv[1] <<"," << n << ",B&B BFS," << count << "," << 1000*(float)(end-start)/CLOCKS_PER_SEC << ",";
	for(int i = 0; i < ids.size(); i++){
		cout << ids[i] << " ";
	}
	cout << ",";
	for(int i = 0; i < right_answer.size(); i++){
		cout << right_answer[i] << " ";
	}
	cout << "\n";

	ids.clear();

	return 0;
}
