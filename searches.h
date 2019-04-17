#include <bitset>
#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

typedef struct _branch_and_bound_queue_elem {
  double maxWeight;
  vector<double> qtd;
  vector<bool> fixedValues;
  double initValue;
} BBFuncArgs;

void printResult(vector<pair<double,double>> weights, clock_t start, clock_t end, vector<int> ids, int count);
int findMaxPos(vector<pair<double, int>> v);
void bestFitSearch(vector<pair<double, double>> param, double maxWeight, vector<int> &ids, int *count) ;
pair<double, int> iterativeBlindSearch(vector<pair<double, double>> param, double maxWeight, vector<int> &ids, int *count);
void branchAndBoundDepthFirst(vector<pair<double, double>> param, double maxWeight, vector<int> &idx, int *count);
void branchAndBoundBreadthFirst(vector<pair<double, double>> param, double maxWeight, vector<int> &idx, int *count);
