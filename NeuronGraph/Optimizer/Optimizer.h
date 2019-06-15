#pragma once
#include"../NeuronGraph.h"
class Optimizer
{
protected:
	int trainableCount;	//额外需要的数据
public:
	const static int OPT_ORIG = 0;
	const static int OPT_GRAD = 1;
	const static int OPT_DELTA = 2;
	NeuronGraph* g;
	virtual void run() = 0;
	Optimizer();
	virtual ~Optimizer() {};
};

