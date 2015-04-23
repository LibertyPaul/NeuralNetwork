#include <cmath>
#include "InputNeuron.hpp"
#include "Axon.hpp"

InputNeuron::InputNeuron(const long double weight):
	Neuron(weight), axon(new Axon(std::shared_ptr<InputNeuron>(this))){
}

void InputNeuron::initialize(const long double value){
	this->currentSum = value;
}

void InputNeuron::sendSignal(){
	long double signal = this->calcSignal();
	this->axon->sendSignal(signal);
}

void InputNeuron::sendRawSignal(){
	this->axon->sendSignal(this->currentSum);
}

void InputNeuron::getOffsetCorrection(const long double offsetCorrection){
	this->errorSum += offsetCorrection;
}
