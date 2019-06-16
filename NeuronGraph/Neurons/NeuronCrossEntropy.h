#pragma once
#include "Neuron.h"
//cross entropy
//note that output has to be connected before answer
class NeuronCrossEntropy :
	public Neuron
{
	//outputs one double only
public:
	NeuronCrossEntropy();
	void run();
	void bp();
	void init();
	~NeuronCrossEntropy();
};

