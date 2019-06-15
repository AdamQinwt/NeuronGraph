#include "AdaGrad_Optimizer.h"

void AdaGrad_Optimizer::run()
{
	int i;
	register Trainable* p;
	for (i = 0; i < g->trainableCnt; i++)
	{
		p = g->trainables[i];
		p->m[OPT_GRAD].mul(1 / (double)g->sequence[g->trainablesIndx[i]]->nbp);
		p->m[OPT_ADAGRAD_ACC_SQR_GRAD].incSqr(p->m[OPT_GRAD]);
		p->m[OPT_DELTA].divideAndSqrt(-_epsilon, _delta, p->m[OPT_ADAGRAD_ACC_SQR_GRAD], p->m[OPT_GRAD]);
		p->m[OPT_ORIG].inc(p->m[OPT_DELTA]);
		p->m[OPT_GRAD].Reset();
		g->sequence[g->trainablesIndx[i]]->nbp = 0;
	}
}

AdaGrad_Optimizer::AdaGrad_Optimizer(NeuronGraph* _g, double _eps, double _del):_epsilon(_eps),_delta(_del)
{
	g = _g;
	trainableCount = 4;
	g->SetTrainables(trainableCount);
}


AdaGrad_Optimizer::~AdaGrad_Optimizer()
{
}
