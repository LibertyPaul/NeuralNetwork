#include <iostream>
#include <ostream>
#include <vector>
#include <utility>
#include <random>
#include <chrono>
#include <fstream>
#include "NeuralNetwork.hpp"
#include "ExampleGenerator.hpp"
#include "CircularAverageCalculator.hpp"
using namespace std;



int main(){
	const size_t exampleSize = 1;
	vector<uint32_t> sizes = {
		exampleSize, 1000, exampleSize
	};
	NeuralNetwork nn(sizes);
	ExampleGenerator eg(exampleSize, 1);
	CircularAverageCalculator cac(100);

	ofstream dst("/home/libertypaul/programming/JS/2dgraph/result.js", ios_base::trunc);
	ofstream log("log.txt", ios_base::trunc);
	log << nn.toString() << endl;

	dst << "var origin = [";

	const size_t iterations = 3000;
	for(size_t i = 0; i < iterations; ++i){
		pair<vector<long double>, vector<long double>> src = eg.getExample();
		long double mse = nn.teach(src.first, src.second);
		dst << "[" << i << "," << mse << "]";

		log << "---------------| " << i << " |---------------" << endl;
		for(const auto val : src.first)
			log << val << " ";
		log << "  ->  ";
		for(const auto val : src.second)
			log << val << " ";
		log << endl;
		log << nn.toString() << endl;
		log << "MSE = " << mse << endl << endl;

		/*cac.pushValue(mse);
		if(cac.isFull() && cac.calcAverage() < eg.calcAcceptableMSE())
			break;
		*/
		if(i != iterations - 1)
			dst << ",";
	}
	dst << "];";

	/*for(size_t i = 0; i < 10; ++i){
		pair<vector<long double>, vector<long double>> src = eg.getExample();
		long double mse = nn.teach(src.first, src.second);
		cout << i << endl << nn.toString() << mse << endl << endl;
	}*/
	return 0;
}
