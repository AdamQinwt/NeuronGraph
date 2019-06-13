#pragma once
#include "Optimizer.h"
class ConjGrad_Optimizer :
	public Optimizer
{
	const int SEARCH;
	const double step;
	const static int OPT_LAST_G = 3;
	const static int OPT_DIRECTION = 4;
	const static int OPT_BEST = 5;	//optimal arg
	const static int OPT_CURRENT = 6;	//current arg
public:
	void run();
	ConjGrad_Optimizer(NeuronGraph* _g,int search=5, double _step=0.1);
	~ConjGrad_Optimizer();
};

