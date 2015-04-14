#include <iostream>
#include <ostream>
#include <vector>
#include <utility>
#include <random>
#include <chrono>
#include "NeuralNetwork.hpp"
#include "ExampleGenerator.hpp"
using namespace std;



int main(){
	const size_t exampleSize = 3;
	vector<uint32_t> sizes = {
		exampleSize, 3, exampleSize
	};
	NeuralNetwork nn(sizes);
	ExampleGenerator eg(exampleSize);

	for(size_t i = 0; i < 100000; ++i){
		pair<vector<double>, vector<double>> src = eg.getExample();
		cout << nn.teach(src.first, src.second) << endl;
	}

	for(size_t i = 0; i < 10; ++i){
		pair<vector<double>, vector<double>> src = eg.getExample();
		double mse = nn.teach(src.first, src.second);
		cout << i << endl << nn.toString() << mse << endl << endl;
	}
	return 0;
}
