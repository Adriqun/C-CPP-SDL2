#pragma once
#include <vector>
#include "connection.h"

namespace Neural
{
	class Neuron;
	typedef std::vector<Neuron> Layer;

	class Neuron
	{
		unsigned index;
		double gradient;
		double outputValue;
		static double eta;		// [0.0...1.0] overall net training rate
		static double alpha;	// [0.0...n] multiplier of last weight change (momentum)
		std::vector<Connection> outputWeights;
	public:
		Neuron(unsigned numOutputs, unsigned index);
		~Neuron();
		void free();
		double getOutputValue() const;
		void setOutputValue(double value);
		void calculateOutputGradients(double target);
		void calculateHiddenGradients(const Layer &nextLayer);
		void feedForward(const Layer &prevLayer);
		void updateInputWeights(Layer &prevLayer);
	private:
		static double randWeight();
		static double transfer(double x);
		static double transferDerivative(double x);
		double sumDOW(const Layer &nextLayer) const;
	};
}