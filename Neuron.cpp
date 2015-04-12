#include "Neuron.hpp"
#include <cmath>

Neuron::Neuron(const double weight){
	this->weight = weight;
	reset();
}

Neuron::~Neuron(){
}

void Neuron::reset(){
	this->currentSum = 0;
}

double Neuron::calcSignal() const{
	double x = currentSum + weight;
	return 2. / (1 + std::pow(M_E, -x)) - 1;
}

double Neuron::calcDerivativeSignal() const{
	return 0.5 * (1 - std::pow(this->calcSignal(), 2));
}

std::string Neuron::toString() const{
	return "| WHT = " + std::to_string(this->weight) + "; SUM = " + std::to_string(this->currentSum) + " |";
}
