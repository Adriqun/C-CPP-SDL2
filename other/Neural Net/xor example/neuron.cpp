#include <cmath>
#include <cstdlib>
#include "neuron.h"

double Neural::Neuron::eta = 0.15;	// overall net learning rate
double Neural::Neuron::alpha = 0.5; // momentum, multiplier of last deltaWeight, [0.0...n]

Neural::Neuron::Neuron(unsigned numOutputs, unsigned index)
{
	free();

	for (unsigned c = 0; c < numOutputs; ++c)
	{
		outputWeights.push_back(Connection());
		outputWeights.back().weight = randWeight();
	}

	this->index = index;
}

Neural::Neuron::~Neuron()
{
	free();
}

void Neural::Neuron::free()
{
	index = 0;
	gradient = 0;
	outputValue = 0;

	if (!outputWeights.empty())
		outputWeights.clear();
}

double Neural::Neuron::getOutputValue() const
{
	return outputValue;
}

void Neural::Neuron::setOutputValue(double value)
{
	outputValue = value;
}

void Neural::Neuron::calculateOutputGradients(double target)
{
	double delta = target - outputValue;
	gradient = delta * Neuron::transferDerivative(outputValue);
}

void Neural::Neuron::calculateHiddenGradients(const Layer &nextLayer)
{
	double dow = sumDOW(nextLayer);
	gradient = dow * Neuron::transferDerivative(outputValue);
}

void Neural::Neuron::feedForward(const Layer &prevLayer)
{
	double sum = 0.0;

	// Sum the previous layer's outputs (which are our inputs)
	// Include the bias node from the previous layer.

	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		sum += prevLayer[n].getOutputValue() * prevLayer[n].outputWeights[index].weight;
	}

	outputValue = Neuron::transfer(sum);
}

void Neural::Neuron::updateInputWeights(Layer &prevLayer)
{
	// The weights to be updated are in the Connection container
	// in the nuerons in the preceding layer

	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		Neuron& neuron = prevLayer[n];
		double oldDeltaWeight = neuron.outputWeights[index].deltaWeight;

		// Individual input, magnified by the gradient and train rate
		// Also add momentum, a fraction of the previous delta weight
		double newDeltaWeight = eta * neuron.getOutputValue() * gradient + alpha * oldDeltaWeight;

		neuron.outputWeights[index].weight += newDeltaWeight;
		neuron.outputWeights[index].deltaWeight = newDeltaWeight;
	}
}



double Neural::Neuron::randWeight()
{
	return rand() / double(RAND_MAX);
}

double Neural::Neuron::transfer(double x)
{
	// tanh - output range [-1.0..1.0]
	return tanh(x);
}

double Neural::Neuron::transferDerivative(double x)
{
	// tanh derivative
	return 1.0 - x * x;
}

double Neural::Neuron::sumDOW(const Layer &nextLayer) const
{
	double sum = 0.0;

	// Sum our contributions of the errors at the nodes we feed
	for (unsigned n = 0; n < nextLayer.size() - 1; ++n)
	{
		sum += outputWeights[n].weight * nextLayer[n].gradient;
	}

	return sum;
}