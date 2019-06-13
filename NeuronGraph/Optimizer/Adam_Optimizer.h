#pragma once
#include "Optimizer.h"
class Adam_Optimizer :
	public Optimizer
{
	const double _step;
	const double _delta;
	const double _ro1,_ro2;
	double ro1, ro2;
	const static int OPT_G1 = 3;
	const static int OPT_G2 = 4;
public:
	void run();
	Adam_Optimizer(NeuronGraph* _g,double __step=0.001, double __delta=1e-8,double r1=0.9,double r2=0.999);
	~Adam_Optimizer();
};

