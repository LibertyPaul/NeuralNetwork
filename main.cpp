#include <iostream>
#include <vector>
#include "NeuralNetwork.hpp"

using namespace std;

int main(){
	vector<uint32_t> sizes = {
		3, 4, 5, 2, 4, 5, 10, 1
	};
	NeuralNetwork nn(sizes);
	cout << nn.toString() << endl;

	nn.test();

	cout << "OK" << endl;

	return 0;
}

