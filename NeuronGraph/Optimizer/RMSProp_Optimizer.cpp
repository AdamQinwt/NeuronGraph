#include "RMSProp_Optimizer.h"

void RMSProp_Optimizer::run()
{
	int i;
	register Trainable* p;
	for (i = 0; i < g->trainableCnt; i++)
	{
		p = g->trainables[i];
		p->m[OPT_GRAD].mul(1 / (double)g->sequence[g->trainablesIndx[i]]->nbp);
		p->m[OPT_ACC_SQR_GRAD].kinc2(ro, 1 - ro, p->m[OPT_GRAD]);
		p->m[OPT_DELTA].divideAndSqrt2(-learningRate, _delta, p->m[OPT_ACC_SQR_GRAD], p->m[OPT_GRAD]);
		p->m[OPT_ORIG].inc(p->m[OPT_DELTA]);
		p->m[OPT_GRAD].Reset();
		g->sequence[g->trainablesIndx[i]]->nbp = 0;
	}
}

RMSProp_Optimizer::RMSProp_Optimizer(NeuronGraph* _g,double _learningRate, double _ro, double _del):learningRate(_learningRate),ro(_ro),_delta(_del)
{
	g = _g;
	trainableCount = 4;
	g->NeedTrainables = trainableCount;
}


RMSProp_Optimizer::~RMSProp_Optimizer()
{
}
