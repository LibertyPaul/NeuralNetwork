#ifndef SUPERNEURON_HPP
#define SUPERNEURON_HPP

#include "InputNeuron.hpp"
#include "OutputNeuron.hpp"
#include "NeuralNetwork.hpp"


class SuperNeuron : public InputNeuron, public OutputNeuron{
public:
	SuperNeuron(const double weight);

	friend class NeuralNetwork;
};


#endif // SUPERNEURON_HPP
