#include <iostream>
#include <vector>
#include "NeuralNetwork.hpp"

using namespace std;

int main(){
	vector<uint32_t> sizes = {
		3, 4, 3
	};
	NeuralNetwork nn(sizes);
	/*

	nn.test();

	cout << "Test: OK" << endl;*/


	vector<double> input = {0.2, 0.5, 1};
	vector<double> output = {0.4, 1.0, 2};
	double mse = nn.teach(input, output);

	cout << nn.toString() << endl;

	cout << "MSE = " << mse << endl;



	return 0;
}

