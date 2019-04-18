#include <bits/stdc++.h>
using namespace std;

int main(void){
	int n;
	double sz;
	vector<pair<double, double>> v;
	srand(time(NULL));
	string filename;
	for(int i=8;i<=800;i++){
		filename = to_string(i) + "-test.txt";
		freopen(filename.c_str(), "w", stdout);

		// Gerar tamanho da nro de itens e tamanho da mochila
		n = (rand()%20)+8;
		sz = (double)(rand()%100000)/10.0;
	
		// Gerar cada item
		double value, weight;
		cout << n << " " << sz << endl;
		for(int j=0;j<n;j++){
			value = (double)(rand()%100000)/10.0;
			weight = (double)(rand()%23000)/10.0;
			weight += 700;
			cout << value << " " << weight << endl;
		}
	}
}
