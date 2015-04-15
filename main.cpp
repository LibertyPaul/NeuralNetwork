#include <iostream>
#include <ostream>
#include <vector>
#include <utility>
#include <random>
#include <chrono>
#include <fstream>
#include "NeuralNetwork.hpp"
#include "ExampleGenerator.hpp"
using namespace std;



int main(){
	const size_t exampleSize = 2;
	vector<uint32_t> sizes = {
		exampleSize, 3, 1
	};
	NeuralNetwork nn(sizes);
	ExampleGenerator eg(exampleSize, 1);

	ofstream dst("/home/libertypaul/programming/JS/2dgraph/result.js", ios_base::trunc);
	ofstream log("log.txt", ios_base::trunc);
	log << nn.toString() << endl;

	dst << "var origin = [";

	const size_t iterations = 50000;
	for(size_t i = 0; i < iterations; ++i){
		pair<vector<double>, vector<double>> src = eg.getExample();
		double mse = nn.teach(src.first, src.second);
		dst << "[" << i << "," << mse << "]";
		log << "---------------| " << i << " |---------------" << endl;
		log << nn.toString() << endl;
		log << "MSE = " << mse << endl << endl;

		if(i != iterations - 1)
			dst << ",";
	}
	dst << "]";

	/*for(size_t i = 0; i < 10; ++i){
		pair<vector<double>, vector<double>> src = eg.getExample();
		double mse = nn.teach(src.first, src.second);
		cout << i << endl << nn.toString() << mse << endl << endl;
	}*/
	return 0;
}
