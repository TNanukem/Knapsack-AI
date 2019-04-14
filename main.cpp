#include <bitset>
#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <time.h>

using namespace std;




pair<double, int> iterativeBlindSearch(vector<pair<double, double>> param, double maxWeight){
	// Calculates the number of possibilities
	int maxNum = 1 << param.size();

	// Iterate through all of the possibilities
	int maxPoss = 0;
	double maxValue = -1;
	for(int curr=0;curr<maxNum;curr++){
		double currWeight = 0, currValue = 0;

		// Iterate through each bit of the current number
		for(int bit=0;bit<param.size();bit++){
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
		if(currWeight < maxWeight && currValue > maxValue){
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

	/*
	 * Scans the n objects and pushes it into the vector
	 * The objects are composed by it's value and weight
	 */
	double tmp1, tmp2;
	cout << "Please insert the number of elements and the max supported weight by the knapsack" << endl;
	cin >> n >> maxWeight;

	cout << "Please insert the pair of value weight at the knapsack" << endl;
	for(int i=0;i<n;i++){
		cin >> tmp1 >> tmp2;
		valueWeight.push_back(make_pair(tmp1, tmp2));
	}

	clock_t start = clock();
	iterativeBlindSearch(valueWeight, maxWeight);
	clock_t end = clock();

	cout << "[EXECUTION TIME] " << 1000*(float)(end-start)/CLOCKS_PER_SEC  << " ms \n";

	return 0;
}
