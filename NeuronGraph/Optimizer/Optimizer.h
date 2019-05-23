#pragma once
#include"../NeuronGraph.h"
#define OPT_ORIG 0
#define OPT_GRAD 1
#define OPT_DELTA 2
class Optimizer
{
protected:
	int trainableCount;	//额外需要的数据
public:
	NeuronGraph* g;
	virtual void run() = 0;
	Optimizer();
	virtual ~Optimizer() {};
};

