#pragma once
#include "Neuron.h"
class NeuronConst :
	public Neuron
{
public:
	NeuronConst(const int _dim,...);
	~NeuronConst();
	void run();
	void bp();
	void init();
};

