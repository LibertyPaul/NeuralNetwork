#include <iostream>
#include <vector>
#include "NeuralNetwork.hpp"

using namespace std;

int main(){
	vector<uint32_t> sizes = {
		3, 4, 5, 2, 4, 5
	};
	NeuralNetwork nn(sizes);
	/*

	nn.test();

	cout << "Test: OK" << endl;*/


	vector<double> initVec = {0.2, 0.5, 100500};
	vector<double> result = nn.run(initVec);
	cout << nn.toString() << endl;

	for(const auto v : result)
		cout << v << ' ';
	cout << endl;

	return 0;
}

