#pragma once
#include"Neuron.h"
#include"Optimizer.h"
class NeuronGraph
{
	//biasic info
	Neuron* in;
	Neuron* out;
	Neuron* ans;
	Neuron* loss;
	Optimizer* opt;
public:
	void run();
	void bp();
	void optimize();
	NeuronGraph();
	~NeuronGraph();
};

