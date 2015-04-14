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
	this->errorSum = 0;
}

double Neuron::calcSignal(const double value){
	return 1. / (1 + std::pow(M_E, -value));
}

double Neuron::calcSignal() const{
	return this->calcSignal(currentSum + weight);
}

double Neuron::calcDerivativeSignal() const{
	double t = this->calcSignal();
	return t * (1 - t);
}

std::string Neuron::toString() const{
	return "| WHT = " + std::to_string(this->weight) + "; SUM = " + std::to_string(this->currentSum) + "; FUNC = " + std::to_string(this->calcSignal()) + " |";
}
