#include "Neuron.hpp"
#include <cmath>

Neuron::Neuron(const long double weight){
	this->weight = weight;
	reset();
}

Neuron::~Neuron(){
}

void Neuron::reset(){
	this->currentSum = 0;
	this->errorSum = 0;
}

long double Neuron::getCurrentValue() const{
	return this->currentSum + this->weight;
}

long double Neuron::calcSignal(const long double value){
	return std::tanh(value);
	//return value;
}

long double Neuron::calcDerivativeSignal(const long double value){
	return (1 - std::pow(std::tanh(value), 2));
	//return 1;
}

long double Neuron::calcSignal() const{
	return this->calcSignal(this->getCurrentValue());
}

long double Neuron::calcDerivativeSignal() const{
	return this->calcDerivativeSignal(this->getCurrentValue());
}

std::string Neuron::toString() const{
	return "| VAL = " + std::to_string(this->getCurrentValue()) + "; FUNC = " + std::to_string(this->calcSignal()) + " |";
}
