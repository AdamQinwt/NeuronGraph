#pragma once
#include "Optimizer.h"
#include"../Dataset.h"
class ConjGrad_Optimizer :
	public Optimizer
{
	const int SEARCH;
	const double step;
	const static int OPT_LAST_G = 3;
	const static int OPT_DIRECTION = 4;
	const static int OPT_BEST = 5;	//optimal arg
	Dataset* data;
public:
	void run();
	ConjGrad_Optimizer(NeuronGraph* _g,Dataset* _data,int search=50, double _step=0.1);
	~ConjGrad_Optimizer();
};

