#pragma once
#include "Optimizer.h"
class RMSProp_Optimizer :
	public Optimizer
{
	double learningRate;
	double ro;
	const double _delta;
	const static int OPT_ACC_SQR_GRAD = 3;
public:
	void run();
	RMSProp_Optimizer(NeuronGraph* _g,double _learningRate=0.3, double _ro=0.99,double _del=1e-6);
	~RMSProp_Optimizer();
};

