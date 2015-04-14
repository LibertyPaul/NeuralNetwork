#include "InputNeuron.hpp"
#include "Axon.hpp"

InputNeuron::InputNeuron(const double weight):
	Neuron(weight), axon(new Axon(std::shared_ptr<InputNeuron>(this))){
}

void InputNeuron::initialize(const double value){
	this->currentSum = value;
}

void InputNeuron::sendSignal(){
	double signal = this->calcSignal();
	this->axon->sendSignal(signal);
}

void InputNeuron::getOffsetCorrection(const double offsetCorrection){
	this->errorSum += offsetCorrection;
}
