#pragma once
#include "Optimizer.h"
class SGD_Optimizer :
	public Optimizer
{
	double learningRate;
	double momentum;
public:
	void run();
	SGD_Optimizer(NeuronGraph* _g,double _learningRate, double _momentum=0);
	~SGD_Optimizer();
};

