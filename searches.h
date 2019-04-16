#include <bitset>
#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <time.h>
#include <fstream>

using namespace std;

int findMaxPos(vector<pair<double, int>> v);
void bestFitSearch(vector<pair<double, double>> param, double maxWeight) ;
pair<double, int> iterativeBlindSearch(vector<pair<double, double>> param, double maxWeight);
