#ifndef NEURALNETWORK
#define NEURALNETWORK

#include <vector>
#include <memory>
#include <random>
#include <string>
#include <utility>

class InputNeuron;
class OutputNeuron;
class SuperNeuron;


typedef std::pair<std::vector<std::shared_ptr<InputNeuron>>,
				  std::vector<std::shared_ptr<OutputNeuron>>> IOLayersPair;//пара соседних слоев сети

class NeuralNetwork{
private:
	mutable std::default_random_engine generator;
	mutable std::uniform_real_distribution<double> weightDistribution, multiplierDistribution;
protected:
	std::vector<std::shared_ptr<InputNeuron>> inputLayer;
	std::vector<std::vector<std::shared_ptr<SuperNeuron>>> hiddenNeurons;
	std::vector<std::shared_ptr<OutputNeuron>> outputLayer;

	void connectLayers(const IOLayersPair &layersPair) const;

	double getDendriteMultiplier() const;
	double getNeuronWeight() const;


	bool checkConnectivity(std::shared_ptr<InputNeuron> inputNeuron,
						   std::shared_ptr<OutputNeuron> outputNeuron) const;

	std::vector<std::shared_ptr<InputNeuron>> getInputLayer(const size_t index) const;
	std::vector<std::shared_ptr<OutputNeuron>> getOutputLayer(const size_t index) const;

	IOLayersPair getLayersPair(const size_t previousLayerIndex) const;
	void initialize(const std::vector<double> &values);
	void reset();

	double calcMSE(const std::vector<double> &output, const std::vector<double> &model) const;//MSE - mean squared error

public:
	NeuralNetwork(const std::vector<uint32_t> &layerSizes);

	std::vector<double> run(const std::vector<double> &values);
	double teach(const std::vector<double> &input, const std::vector<double> &model);


	size_t getLayerCount() const;

	std::string toString() const;
	void test() const;

};

std::vector<std::shared_ptr<InputNeuron>> superVector2InputVector(const std::vector<std::shared_ptr<SuperNeuron>> &superNeurons);
std::vector<std::shared_ptr<OutputNeuron>> superVector2OutputVector(const std::vector<std::shared_ptr<SuperNeuron>> &superNeurons);

#endif // NEURALNETWORK

