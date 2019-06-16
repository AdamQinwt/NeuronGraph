#pragma once
#include "Neuron.h"
class NeuronVariable :
	public Neuron
{
public:
	NeuronVariable(const int NeedAll,const int _dim,...);
	~NeuronVariable();
	void run();
	void bp();
	void init();
};

