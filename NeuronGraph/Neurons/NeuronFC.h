#pragma once
#include "Neuron.h"
#define FC_IN 0
#define FC_W 1
#define FC_B 2
class NeuronFC :
	public Neuron
{
	int nin, nout;
	double(*act)(double);
	double(*dact)(double);
public:
	NeuronFC(int _in,int _out,const char* activate);
	void run();
	void bp();
	void init();
	~NeuronFC();
};

